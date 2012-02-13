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
	
// Display image dimensions to user
	cout << "Image Dimensions: Rows: " << M << "; Columns: " << N << endl;
	
// Instantiate memory for M by N image
	Image image(M,N,Q);

// Test for functionality
		
	
// Read the specified image
	readImage(argv[1], image);

	return (1);
}