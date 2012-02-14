#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

    int pixelV;
	float size;
  	cout << "Enter multiplier \n";
	cin >> size;
	// allocate memory for the image array
	int MM=int(ceil(M*size));
	int NN=int(ceil(N*size));
	ImageType imageScaled(NN, MM, Q);
	
	// enlarge image 
	for(int i=0; i<N; i++)
    {
		for(int j=0; j<M; j++) 
        {
			image.getPixelVal(i, j, pixelV);
			imageScaled.setPixelVal(int(floor(i*size)), int(floor(j*size)), pixelV);

		}
    }
    
 // write image
    writeImage(argv[2], imageScaled);

 return (1);
}
