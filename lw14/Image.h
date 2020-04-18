#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Pixel.h"

class Image {
  public:
    Image();
    Image(std::string filename);
    Image(unsigned int width, unsigned int height);

    // "big three"
    Image(const Image& srcImage);  // copy constructor
    ~Image();  // destructor
    Image operator=(const Image& srcImage);  // copy assignment operator
    
    Pixel*& operator[](unsigned int column);
    const Pixel* operator[](unsigned int column) const;
    unsigned int getWidth();
    unsigned int getHeight();
    
    void makeGreyscale();
    void makeSepia();
    void addColor(Pixel p);
    
    void output(std::string filename);
    
  private:
    Pixel** image;
    unsigned int width;  // columns
    unsigned int height;  // rows
    std::string filename;

    void load(std::string filename);
    void allocateImage(unsigned int width, unsigned int height);
    void clear();
};

#endif