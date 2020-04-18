#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Image.h"
#include "Pixel.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


// default constructors
Image::Image() : image(nullptr), width(0), height(0) {}

Image::Image(std::string filename) : image(nullptr), width(0), height(0) {
  load(filename);
}

Image::Image(unsigned int width, unsigned int height) : image(nullptr), width(0), height(0) {
  allocateImage(width, height);
}


// the "big three"
// copy constructor
Image::Image(const Image& srcImage) : image(nullptr), width(0), height(0) {
  allocateImage(srcImage.width, srcImage.height);
  // copy values
  for (unsigned int col = 0; col < width; col++) {
    for (unsigned int row = 0; row < height; row++) {
      image[col][row] = srcImage[col][row];
    }
  }
}

// destructor
Image::~Image() {
  clear();
}

// copy assignment operator
Image& Image::operator=(const Image& srcImage) {
  if (this != &srcImage) {  // 1. don't self assign
    clear();  // 2. delete old data object
    allocateImage(srcImage.width, srcImage.height);   // 3. allocate new data object
    for (unsigned int col = 0; col < width; ++col) {
      for (unsigned int row = 0; row < height; ++row) {
        image[col][row] = srcImage[col][row];   // 4. copy data object
      }
    }
  }
  return *this;
}


void Image::allocateImage(unsigned int width, unsigned int height) {
  if (width > 0 && height > 0) {
    this->width = width;
    this->height = height;
    image = new Pixel*[width];
    for (unsigned int col = 0; col < width; ++col) {
      image[col] = new Pixel[height];
    }
  }
}

void Image::clear() {
  for (unsigned int i = 0; i < width; ++i) {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  width = 0;
  height = 0;
}

Pixel*& Image::operator[](unsigned int column) { return image[column]; }

const Pixel* Image::operator[](unsigned int column) const { return image[column]; }

unsigned int Image::getWidth() { return width; }

unsigned int Image::getHeight() { return height; }

// if any errors are encountered the width and height will be 0
void Image::load(string filename) {
  // avoid memory leaks by deleting whatever is already there
  clear();
  
  cout << "Loading image..." << endl;
  ifstream ifs(filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file " << filename << endl;
    return;
  }
  
  // get type from preamble
  string type;
  ifs >> type; // should be P3
  if ((toupper(type.at(0)) != 'P') || (type.at(1) != '3')) { // check that type is correct
    cout << "Error: type is " << type << "instead of P3" << endl;
    return;
  }
  
  // get width (w) and height (h) from preamble
  int w = 0;
  int h = 0;
  ifs >> w >> h;
  if (w < 1 || h < 1) {
    return;
  }
  
  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (colorMax != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return;
  }

  // create image on the heap
  allocateImage(w, h);
  
  if (width > 0 && height > 0) { // successfully created the image
    // get RGB pixel values
    for (unsigned int row = 0; row < height; ++row) {
      for (unsigned int col = 0; col < width; ++col) {
        int r, g, b;
        ifs >> r >> g >> b;
        image[col][row].setRed(r);
        image[col][row].setGreen(g);
        image[col][row].setBlue(b);
        //cout << "Set image[" << col << "][" << row << "] " << image[col][row] << endl;
      }
    }
  }
}

void Image::output(string filename) {
  cout << "Outputting image..." << endl;
  // declare/define and open output file stream
  ofstream ofs (filename);
  
  // check if output stream opened successfully
  if (!ofs.is_open()) {
    cout << "Error: failed to open output file " << filename << endl;
    return;
  }
  
  // output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  
  // output pixels
  for (unsigned int row = 0; row < height; ++row) {
    for (unsigned int col = 0; col < width; ++col) {
      ofs << image[col][row].getRed() << " ";
      ofs << image[col][row].getGreen() << " ";
      ofs << image[col][row].getBlue() << " ";
    }
    ofs << endl;
  }
}

void Image::makeGreyscale() {
  cout << "Making grayscale image... " << endl;
  // iterate through 2d image of Pixels and convert them to grayscale
  for (unsigned int row = 0; row < height; ++row) {
    for (unsigned int col = 0; col < width; ++col) {
      int greyColor = round((image[col][row].getRed() + image[col][row].getGreen() + image[col][row].getBlue()) / 3.0);
      //cout << "image[" << col << "][" << row << "] " << image[col][row] << endl;
      
      image[col][row] = Pixel(greyColor, greyColor, greyColor);
      //cout << "image[" << col << "][" << row << "] " << image[col][row] << endl;
    }
  }  
}

void Image::makeSepia() {
  cout << "Making sepia image... " << endl;
  // iterate through 2d image of Pixels and convert them to sepia
  for (unsigned int row = 0; row < height; ++row) {
    for (unsigned int col = 0; col < width; ++col) {
      int newRed = round(0.393*image[col][row].getRed() + 0.769*image[col][row].getGreen() + 0.189*image[col][row].getBlue());
      if (newRed > 255) newRed = 255;
      int newGreen = round((0.349*image[col][row].getRed() + 0.686*image[col][row].getGreen() + 0.168*image[col][row].getBlue()));
      if (newGreen > 255) newGreen = 255;
      int newBlue = round((0.272*image[col][row].getRed() + 0.534*image[col][row].getGreen() + 0.131*image[col][row].getBlue()));
      if (newBlue > 255) newBlue = 255;
      
      image[col][row] = Pixel(newRed, newGreen, newBlue);
    }
  }  
}

void Image::addColor(Pixel p) {
  // iterate through 2d image of Pixels and add color to each Pixel
  for (unsigned int row = 0; row < height; ++row) {
    for (unsigned int col = 0; col < width; ++col) {
      image[col][row] = image[col][row] + p;
    }
  }  
}