LW: Revisiting Image Manipulation
Objectives
Use the rule of three
See how prior labwork/homework structure changes when implemented with classes
Overview
After learning all about classes, your friend went back and updated labwork 6 to utilize classes. They created an image class and converted the pixel struct into a proper class. Now you don’t have to type in the width and height, it gets those values from the file and saves them in the image class. Also, the memory is better used since your friend dynamically allocates the image array on the heap.
As you run and play with the program you notice some peculiarities.
First you load this image of reveille.

Then you convert it to grayscale..
Then you add the Color (225, 5, 5).
This seems pretty cool. You exit the program and decide to play with it some more. So you load the image of Reveille again. You decide to replicate the colored image you had before, so you add the Color (255, 5, 5) again.
You notice that there is evidence of other colors besides red whereas last time it was all shades of red. You suspect something may be wrong with the program. You realize that your friend put the image on the heap, so maybe shallow copy is the culprit. 
On top of all that, you find out that there are memory leaks in the program. You see a clear() function that could be called from a destructor, but you suspect that there is a problem with it that needs to be fixed.
Requirements
Download the starting code along with some ppm images you can use.
manip.cpp
You do not need to edit this file.
functions.h
You do not need to edit this file.
functions.cpp
You do not need to edit this file.
Image.h
You may need to edit this file.
Image.cpp
You may need to edit this file.
Pixel.h
You do not need to edit this file.
Pixel.cpp
You do not need to edit this file.
Update the image class to implement the rule of three and update any functions used by the rule of three that might be broken.
Supporting Information
Feel free to look back at the prior labwork on Image Manipulation if needed.
Viewing PPM files
You’ll need to view your PPM files to see the results of your program. Unfortunately, PPM is not supported by many image viewers.
Some options for viewing your files include:
Drag files onto this website (http://paulcuth.me.uk/netpbm-viewer/)
You don’t have to download any programs!
The GIMP is an open source version of Photoshop. 
Warning: This is a very large program.
