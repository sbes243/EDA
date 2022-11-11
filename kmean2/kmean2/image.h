#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <string>
#include <vector>

class Pixel
{
public:
    Pixel(int red, int green, int blue);
    Pixel(Pixel* pixel);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    std::string getRGB() const;
    void setRGB(int red, int green, int blue);

private:
    int m_red;
    int m_green;
    int m_blue;
};

class Image
{
public:
    Image(int width, int height);
    Image(std::string name);
    ~Image();

    void saveImage(std::string savePath) const;
    Pixel* getRandPixel() const;
    std::vector<Pixel*> getPixels() const;
    Pixel* getPixel(int index) const;
    int getLength() const;

private:
    int m_width;
    int m_height;
    int m_depth;
    std::vector<Pixel*> m_pixels;
};

class Cluster
{
public:
    Cluster(Image* image);
    ~Cluster();

    double adjustCentroid();
    double getDistanceTo(Pixel* pixel) const;
    double getDistanceTo(int red, int green, int blue) const;
    void addPixel(Pixel* pixel);
    void clearPixels();
    void changeAll();

private:
    Image* m_image;
    Pixel* m_centroid;
    std::vector<Pixel*> m_pixels;
};

#endif