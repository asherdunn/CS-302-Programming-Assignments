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
	int rows, cols, grayMax; // Parameters of image
	bool type;
	
// Read the header of specified image
	readImageHeader(argv[1], cols, rows, grayMax, type);
	
// Display image dimensions to user
	cout << "Image Dimensions: Rows: " << rows << "; Columns: " << cols << endl;
	
// Instantiate memory for rows by cols image
	Image image(rows,cols,grayMax);

// Test for functionality
		
	
// Read the specified image
	readImage(argv[1], image);

	return (1);
}