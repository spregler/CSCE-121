#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}


void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* seam = new int[length];

  for (int i = 0; i < length; i++) {
    seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
  delete seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream fin(filename); // create ifstream object

  // ------------------------------Error: failed to open input file - <filename>------------
  if(!fin.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;    
  }

  // -------------------------------Error: type is <type> instead of P3---------------------
  char type[3];
  fin >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  // ------Error: input <valuename>(<inputVal>) does not match value in file (<fileVal>)----
  int w = 0, h = 0;
  fin >> w >> h;

  if (fin.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  else if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width" << " (" << width << ")" << " does not match value in file "
    << "(" << w << ")" << endl;
    return false;
  }
  else if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height" << " (" << height << ")" << " does not match value in file "
    << "(" << h << ")" << endl;
    return false;
  }  

  int maxColorVal;
  fin >> maxColorVal;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      fin >> image[j][i].r;
      if (fin.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      fin >> image[j][i].g;
      if (fin.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      fin >> image[j][i].b;
      if (fin.fail()) {
          cout << "Error: read non-integer value" << endl;
          return false;
      }

      if (!fin.eof()) {
        if (image[j][i].r < 0 || image[j][i].r > 255) {
          cout << "Error: invalid color value " << image[j][i].r;
          return false;
        }
        if (image[j][i].g < 0 || image[j][i].g > 255) {
          cout << "Error: invalid color value " << image[j][i].g;
          return false;
        }
        if (image[j][i].b < 0 || image[j][i].b > 255) {
          cout << "Error: invalid color value " << image[j][i].b;
          return false;
        }
      }
      else if (fin.eof()) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
    }
  }

  int temp = 0;
  fin >> temp;

  if (fin.good()) {
    cout << "Error: too many color values";
    return false;
  }
  else {
    return true;
  }
}


bool outputImage(string filename, Pixel** image, int width, int height) {
  ofstream ofs(filename);

   if (!ofs.is_open()) {
    cout << "Error: failed to open output file " << filename << endl;
  }

  ofs << "P3" << endl;
  ofs << width << height << endl;
  ofs << 255 << endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      ofs << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << " ";
    }
  }
  ofs << endl;
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 

  int Rx, Gx, Bx, Ry, Gy, By, changeX, changeY, totEnergy = 0;

  if (x == 0){
    Rx = abs(image[1][y].r - image[width-1][y].r);
    Gx = abs(image[1][y].g - image[width-1][y].g);
    Bx = abs(image[1][y].b - image[width-1][y].b);
  } else if(x == (width - 1)){
    Rx = abs(image[width-2][y].r - image[0][y].r);
    Gx = abs(image[width-2][y].g - image[0][y].g);
    Bx = abs(image[width-2][y].b - image[0][y].b);
  } else{
    Rx = abs(image[x+1][y].r - image[x-1][y].r);
    Gx = abs(image[x+1][y].g - image[x-1][y].g);
    Bx = abs(image[x+1][y].b - image[x-1][y].b);
  } 
  
  if (y == 0){
    Ry = abs(image[x][1].r - image[x][height-1].r);
    Gy = abs(image[x][1].g - image[x][height-1].g);
    By = abs(image[x][1].b - image[x][height-1].b);
  } else if (y == (height - 1)){
    Ry = abs(image[x][height-2].r - image[x][0].r);
    Gy = abs(image[x][height-2].g - image[x][0].g);
    By = abs(image[x][height-2].b - image[x][0].b);
  } else{
    Ry = abs(image[x][y+1].r - image[x][y-1].r);
    Gy = abs(image[x][y+1].g - image[x][y-1].g);
    By = abs(image[x][y+1].b - image[x][y-1].b);
  }

  changeX = pow(Rx,2) + pow(Gx,2) + pow(Bx,2);
  changeY = pow(Ry,2) + pow(Gy,2) + pow(By,2);
  totEnergy = changeX + changeY;

  return totEnergy;

}


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  
  int totEnergy = energy(image, start_col, 0, width, height);
 
  int col = start_col;
  int forward;
  int left;
  int right;

  seam[0] = start_col;
  for (int i = 1; i < height; i++) {
  	if (col == 0) {
  		forward = energy(image, col, i, width, height);
  		left = energy(image, col + 1, i, width, height);

  		if (forward == left) {
  			totEnergy += forward;
  			seam[i] = col;
  		}
  		else {
  			if (forward < left) {
  				totEnergy += forward;
  				seam[i] = col;
  			}
  			else if (forward > left) {
  				totEnergy += left;
  				seam[i] = col + 1;
  				col += 1;
  			}
  		}
  	} if (col == width-1) {
  		forward = energy(image, col, i, width, height);
  		right = energy(image, col - 1, i, width, height);

  		if (forward == right) {
  			totEnergy += forward;
  			seam[i] = col;
  		}
  		else {
  			if (forward < right) {
  				totEnergy += forward;
  				seam[i] = col;
  			}
  			else if (forward > right) {
  				totEnergy += right;
  				seam[i] = col - 1;
  				col -= 1;
  			}
  		}
  	} else {
	  	forward = energy(image, col, i, width, height);
	  	left = energy(image, col + 1, i, width, height);
	  	right = energy(image, col - 1, i, width, height);

	  	if ((forward <= right) && (forward <= left)) {
	  		totEnergy += forward;
	  		seam[i] = col;
	  	}
	  	else if ((left <= right) && (left <= forward)) {
	  		totEnergy += left;
	 		seam[i] = col + 1;
	 		col += 1;
	  	}
	  	else if ((right <= forward) && (right <= left)) {
	  		totEnergy += right;
	  		seam[i] = col - 1;
	  		col -= 1;
	  	}
  	}
  }
  return totEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	int* minSeam = new int[height];
	int minEnergy = loadVerticalSeam(image, 0, width, height, minSeam);

  for (int i = 1; i < width; i++) {
  	int* seam = new int[height];
  	int energy = loadVerticalSeam(image, i, width, height, seam);

  	if (energy < minEnergy) {
  		minEnergy = energy;
  		for (int j = 0; j < height; j++) {
  			minSeam[j] = seam[j];
  		}
  	}
  	delete[] seam;
  }
  return minSeam;
  delete[] minSeam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {

	for (int i = 0; i < height; i++) {
		int col = verticalSeam[i];
		for (int j = col; j < width - 1; j++) {
			image[j][i] = image[j + 1][i];
		}
	}
	width -= 1;

}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int totEnergy = energy(image, 0, start_row, width, height);
 
  int row = start_row;
  int forward;
  int left;
  int right;

  seam[0] = start_row;
  for (int i = 1; i < width; i++) {
    if (row == 0) {
      forward = energy(image, i, row, width, height);
      right = energy(image, i, row + 1, width, height);

      if (forward == right) {
        totEnergy += forward;
        seam[i] = row;
      }
      else {
        if (forward < right) {
          totEnergy += forward;
          seam[i] = row;
        }
        else if (forward > right) {
          totEnergy += right;
          seam[i] = row + 1;
          row += 1;
        }
      }
    } if (row == height-1) {
      forward = energy(image, i, row, width, height);
      left = energy(image, i, row - 1, width, height);

      if (forward == left) {
        totEnergy += forward;
        seam[i] = row;
      }
      else {
        if (forward < left) {
          totEnergy += forward;
          seam[i] = row;
        }
        else if (forward > left) {
          totEnergy += left;
          seam[i] = row - 1;
          row -= 1;
        }
      }
    } else {
      forward = energy(image, i, row, width, height);
      left = energy(image, i, row - 1, width, height);
      right = energy(image, i, row + 1, width, height);

      if ((forward <= right) && (forward <= left)) {
        totEnergy += forward;
        seam[i] = row;
      }
      else if ((left <= right) && (left <= forward)) {
        totEnergy += left;
        seam[i] = row - 1;
        row -= 1;
      }
      else if ((right <= forward) && (right <= left)) {
        totEnergy += right;
        seam[i] = row + 1;
        row += 1;
      }
    }
  }
  return totEnergy;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int* minSeam = new int[width];
  int minEnergy = loadHorizontalSeam(image, 0, width, height, minSeam);

  for (int i = 1; i < height; i++) {
    int* seam = new int[width];
    int energy = loadHorizontalSeam(image, i, width, height, seam);

    if (energy < minEnergy) {
      minEnergy = energy;
      for (int j = 0; j < width; j++) {
        minSeam[j] = seam[j];
      }
    }
    delete[] seam;
  }
  return minSeam;
  delete[] minSeam;
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for (int i = 0; i < width; i++) {
    int row = horizontalSeam[i];
    for (int j = row; j < height - 1; j++) {
      image[j][i] = image[j][i+1];
    }
  }
  height -= 1;
}