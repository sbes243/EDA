#include "image.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>


using namespace std;

Pixel::Pixel(int red, int green, int blue) : m_red(red), m_green(green), m_blue(blue) {}

Pixel::Pixel(Pixel* pixel) : m_red(pixel->m_red), m_green(pixel->m_green), m_blue(pixel->m_blue) {}

int Pixel::getRed() const
{
    return m_red;
}

int Pixel::getGreen() const
{
    return m_green;
}

int Pixel::getBlue() const
{
    return m_blue;
}

string Pixel::getRGB() const
{
    return to_string(m_red) + " " + to_string(m_green) + " " + to_string(m_blue);
}

void Pixel::setRGB(int red, int green, int blue)
{
    m_red = red;
    m_green = green;
    m_blue = blue;
}

Image::Image(int width, int height) : m_width(width), m_height(height)
{
    for (int i(0); i < m_width * m_height; i++)
    {
        m_pixels.push_back(new Pixel(0, 0, 0));
    }
}

Image::Image(string imageDir)
{
    ifstream image(imageDir);
    if (image)
    {
        string type;
        image >> type;
        if (type == "P3" or "ppm")
        {
            int red;
            int green;
            int blue;
            image >> m_width;
            image >> m_height;
            image >> m_depth;
            for (int i(0); i < m_width * m_height; i++)
            {
                image >> red;
                image >> green;
                image >> blue;
                m_pixels.push_back(new Pixel(red, green, blue));
            }
        }
        else {
            cout << imageDir << " is in the wrong format (should be P3)" << endl;
        }
    }
    else {
        cout << imageDir << " could not be opened!" << endl;
    }
}

Image::~Image()
{
    for (int i(0); i < m_width * m_height; i++)
    {
        delete m_pixels[i];
    }
}

void Image::saveImage(string name) const
{
    ofstream image(name);
    if (image)
    {
        image << "P3" << endl;
        image << m_width << " " << m_height << endl;
        image << m_depth << endl;
        for (int y(0); y < m_width; y++)
        {
            for (int x(0); x < m_height; x++)
            {
                Pixel* pixel = m_pixels[m_height * y + x];
                image << pixel->getRGB() << " ";
            }
            image << endl;
        }
    }
    else {
        cout << name << ".ppm could not be opened" << endl;
    }
}

Pixel* Image::getRandPixel() const
{
    return m_pixels[rand() % m_width * m_height];
}

vector<Pixel*> Image::getPixels() const
{
    return m_pixels;
}

Pixel* Image::getPixel(int index) const
{
    return m_pixels[index];
}

int Image::getLength() const
{
    return m_width * m_height;
}

Cluster::Cluster(Image* image) : m_image(image), m_centroid(new Pixel(image->getRandPixel()))
{
}

Cluster::~Cluster()
{
    delete m_centroid;
}

double Cluster::adjustCentroid()
{
    float red(0);
    float green(0);
    float blue(0);

    for (int i(0); i < m_pixels.size(); i++)
    {
        red += m_pixels[i]->getRed();
        green += m_pixels[i]->getGreen();
        blue += m_pixels[i]->getBlue();
    }

    int denominator(m_pixels.size());
    if (m_pixels.size() < 1)
    {
        denominator = 1;
    }

    red /= denominator;
    green /= denominator;
    blue /= denominator;

    double change(this->getDistanceTo(red, green, blue));

    m_centroid->setRGB(red, green, blue);

    return change;
}

double Cluster::getDistanceTo(Pixel* pixel) const
{
    int diffRed(pixel->getRed() - m_centroid->getRed());
    int diffGreen(pixel->getGreen() - m_centroid->getGreen());
    int diffBlue(pixel->getBlue() - m_centroid->getBlue());

    return sqrt(pow(diffRed, 2) + pow(diffGreen, 2) + pow(diffBlue, 2));
}

double Cluster::getDistanceTo(int red, int green, int blue) const
{
    int diffRed(red - m_centroid->getRed());
    int diffGreen(green - m_centroid->getGreen());
    int diffBlue(blue - m_centroid->getBlue());

    return sqrt(pow(diffRed, 2) + pow(diffGreen, 2) + pow(diffBlue, 2));
}

void Cluster::addPixel(Pixel* pixel)
{
    m_pixels.push_back(pixel);
}

void Cluster::clearPixels()
{
    m_pixels = {};
}

void Cluster::changeAll()
{
    for (int i(0); i < m_pixels.size(); i++)
    {
        m_pixels[i]->setRGB(m_centroid->getRed(), m_centroid->getGreen(), m_centroid->getBlue());
    }
}