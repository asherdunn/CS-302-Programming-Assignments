#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "image.h"

int main(int argc, char *argv[])
{ 
    int M, N, Q;
    bool type;

 // read image header
    readImageHeader(argv[1], N, M, Q, type);

 // allocate memory for the image array

    ImageType image(N, M, Q);

 // read image
    readImage(argv[1], image);

    image.Threshold(image);
    
 // write image
    writeImage(argv[2], image);

 return (1);
}
