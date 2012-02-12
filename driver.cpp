#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
#include "image.h"
//**********************************************
//Function name: main
//Purpose:	Implements member functions defined
//in Image class
//*********************************************
int main(int argc, char *argv[])
{
	int M, N, Q; // Parameters of image
	bool type;
	
	// Read the header of specified image
	readImageHeader(argv[1], N, M, Q, type);
		
	// Instantiate memory for M by N image
	Image image(M,N,Q);
	
	// Read the specified image
	readImage(argv[1], image);
	
	
	
	writeImage(argv[2], );

	return (1);
}