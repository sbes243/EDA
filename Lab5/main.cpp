#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>       /* round() */

typedef struct bmpFileHeader
{
	uint32_t size;
	uint16_t resv1;
	uint16_t resv2;
	uint32_t offset;
} bmpFileHeader;

typedef struct bmpInfoHeader
{
	uint32_t headersize;      /* DIB header size */
	uint32_t width;
	uint32_t height;
	uint16_t planes;         /* color planes */
	uint16_t bpp;            /* bits per pixel */
	uint32_t compress;
	uint32_t imgsize;    
	uint32_t bpmx;        /* X bits per meter */
	uint32_t bpmy;        /* Y bits per meter */
	uint32_t colors;      /* colors used */
	uint32_t imxtcolors;      /* important colors */
} bmpInfoHeader;

void SaveBMP(char *filename, bmpInfoHeader *info, unsigned char *imgdata);
unsigned char calculaColorMedio(unsigned char *pixel);
unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader);
bmpInfoHeader *createInfoHeader(unsigned w, unsigned h, unsigned ppp);
void DisplayInfo(bmpInfoHeader *info);
void TextDisplay(bmpInfoHeader *info, unsigned char *img);
int main()
{
	bmpInfoHeader info;  
	unsigned char *img;
	unsigned char color[3];
	unsigned char media;
	int i, j;
	img=LoadBMP((char*)"image.bmp", &info);
	DisplayInfo(&info);
	TextDisplay(&info, img);
	for (i=0; i<info.height; i++)
	{
		for (j=0; j<info.width; j++)
		{
			media=calculaColorMedio(&img[3*(j+i*info.width)]);
			img[3*(j+i*info.width)]=media;
			img[3*(j+i*info.width)+1]=media;
			img[3*(j+i*info.width)+2]=media;
			
		}
	}
	SaveBMP((char*)"image.bmp", &info, img);
	DisplayInfo(&info);
	TextDisplay(&info, img);
	free(img);
	
}

unsigned char calculaColorMedio(unsigned char *pixel)
{
	unsigned media = (*pixel + *(pixel+1) + *(pixel+2)) / 3;
	
	return (unsigned char) media;
}

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader)
{
	
	FILE *f;
	bmpFileHeader header;     /* cabecera */
	unsigned char *imgdata;   /* datos de imagen */
	uint16_t type;        /* 2 bytes identificativos */
	
	f=fopen (filename, "r");
	if (!f)
		return NULL;        /* Si no podemos leer, no hay imagen*/
	
	/* Leemos los dos primeros bytes */
	fread(&type, sizeof(uint16_t), 1, f);
	if (type !=0x4D42)        /* Comprobamos el formato */
	{
		fclose(f);
		return NULL;
	}
	
	/* Leemos la cabecera de fichero completa */
	fread(&header, sizeof(bmpFileHeader), 1, f);
	
	/* Leemos la cabecera de información completa */
	fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);
	
	/* Reservamos memoria para la imagen, ¿cuánta?
	Tanto como indique imgsize */
	imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);
	
	/* Nos situamos en el sitio donde empiezan los datos de imagen,
	nos lo indica el offset de la cabecera de fichero*/
	fseek(f, header.offset, SEEK_SET);
	
	/* Leemos los datos de imagen, tantos bytes como imgsize */
	fread(imgdata, bInfoHeader->imgsize,1, f);
	
	/* Cerramos */
	fclose(f);
	
	/* Devolvemos la imagen */
	return imgdata;
}

bmpInfoHeader *createInfoHeader(unsigned w, unsigned h, unsigned ppp)
{
	bmpInfoHeader *ih = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	
	ih->headersize=sizeof(bmpInfoHeader);
	ih->width=w;
	ih->height=h;
	ih->planes=1;
	ih->bpp=24;
	ih->compress=0;
	ih->imgsize=w*h*3;        /* 3 bytes por pixel w*h pixels */
	ih->bpmx=(unsigned)round((double)ppp*100/2.54);
	ih->bpmy=ih->bpmx;        /* Misma resolución vertical y horiontal */
	ih->colors=0;
	ih->imxtcolors=0;
	
	return ih;
}

void SaveBMP(char *filename, bmpInfoHeader *info, unsigned char *imgdata)
{
	bmpFileHeader header;
	FILE *f;
	uint16_t type;
	
	f=fopen(filename, "w+");
	header.size=info->imgsize+sizeof(bmpFileHeader)+sizeof(bmpInfoHeader);
	/* header.resv1=0; */
	/* header.resv2=1; */
	/* El offset será el tamaño de las dos cabeceras + 2 (información de fichero)*/
	header.offset=sizeof(bmpFileHeader)+sizeof(bmpInfoHeader)+2;
	/* Escribimos la identificación del archivo */
	type=0x4D42;
	fwrite(&type, sizeof(type),1,f);
	/* Escribimos la cabecera de fichero */
	fwrite(&header, sizeof(bmpFileHeader),1,f);
	/* Escribimos la información básica de la imagen */
	fwrite(info, sizeof(bmpInfoHeader),1,f);
	/* Escribimos la imagen */
	fwrite(imgdata, info->imgsize, 1, f);
	fclose(f);
}
void DisplayInfo(bmpInfoHeader *info)
{
	printf("Tamaño de la cabecera: %u\n", info->headersize);
	printf("Anchura: %d\n", info->width);
	printf("Altura: %d\n", info->height);
	printf("Planos (1): %d\n", info->planes);
	printf("Bits por pixel: %d\n", info->bpp);
	printf("Compresión: %d\n", info->compress);
	printf("Tamaño de datos de imagen: %u\n", info->imgsize);
	printf("Resolucón horizontal: %u\n", info->bpmx);
	printf("Resolucón vertical: %u\n", info->bpmy);
	printf("Colores en paleta: %d\n", info->colors);
	printf("Colores importantes: %d\n", info->imxtcolors);
}
void TextDisplay(bmpInfoHeader *info, unsigned char *img)
{
	int x, y;
	/* Reducimos la resolución vertical y horizontal para que la imagen entre en pantalla */
	static const int reduccionX=6, reduccionY=4;
	/* Si la componente supera el umbral, el color se marcará como 1. */
	static const int umbral=90;
	/* Asignamos caracteres a los colores en pantalla */
	static unsigned char colores[9]=" bgfrRGB";
	int r,g,b;
	
	/* Dibujamos la imagen */
	for (y=info->height; y>0; y-=reduccionY)
	{
		for (x=0; x<info->width; x+=reduccionX)
		{
			b=(img[3*(x+y*info->width)]>umbral);
			g=(img[3*(x+y*info->width)+1]>umbral);
			r=(img[3*(x+y*info->width)+2]>umbral);
			
			printf("%c", colores[b+g*2+r*4]);
		}
		printf("\n");
	}
}
