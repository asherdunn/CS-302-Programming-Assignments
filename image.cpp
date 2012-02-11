#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#include "image.h"

//**********************************************
//Function name:Image default constructor
//Purpose:	Paramater less constructor for
//		when an Image class is created
//		without any default values.
//		Sets all variables equal to
//		their null values.
//*********************************************
Image::Image()
{
	N = 0;
	M = 0;
	Q = 0;
	pixelVal = NULL;
}
//**********************************************
//Function name:Image constructor
//Purpose:	Constructor for the Image class.
//		Initializes all variables in 
//		the class and allocates an 
//		appropriate amount of memory
//		to be used by the class for
//		image storage.
//*********************************************
Image::Image(int rows, int cols, int grays)
{
	N = rows;
	M = cols;
	Q = grays;
	pixelVal = new int *[N];
	for(int i = 0; i < M; i++)
	{
		pixelVal[i] = new int[m];
	}
}
//**********************************************
//Function name:Image copy constructor
//Purpose:	Copies all the values in the 
//		passed image file. Allocates
//		an appropriate amount of memory
//		for the image itself to be
//		stored.
//*********************************************
Image::Image(const Image &copyImage)
{
	N = copyImage.N;
	M = copyImage.M;
	Q = copyImage.Q;
	pixelVal = new int *[N];
	for(int rowCount = 0; rowCount < N; rowCount++)
	{
		pixelVal[rowCount] = new int[M];
		for(int colCount = 0; colCount < M; colCount++)
		{
			pixelVal[rowCount][colCount] = copyImage.pixelVal[rowCount][colCount];
		}
	}
}
//*************************************************
//Function name:Image Deconstructor
//Purpose:	Deallocate all dynamically allocated
//		memory. Deallocates the 2D array used
//		by the Image class.
//**************************************************	
Image::~Image()
{
	for(int delRow = 0; delRow < N; delRow++)
	{
		delete [] pixelVal[delRow];
	}
	delete [] pixelVal;
}
//**********************************************
//Function name:getImageInfo
//Return Type:	Void
//Purpose:	Return the number of columns, 
//		rows, and pixel count in the
//		image array. Uses pass-by-
//		reference to assign those 
//		values to the variables passed.	
//*********************************************		
void Image::getImageInfo(int &rows, int &cols, int &max)
{
	rows = N;
	cols = M;
	max = Q;
}
//**********************************************
//Function name:getPixelVal
//Return Type:	int
//Purpose:	Return the value of the pixel
//		at the specified coordinates.
//		Throws an OUT-OF-BOUNDS
//		exception if the coordinates
//		fall outside the image.	
//*********************************************
int Image::getPixelVal(int rowNum, int colNum)
{
	if(rowNum > N || colNum > M)
	{
		//************************************
		//If the coordinates are outside the
		//image, this error will occur. This 
		//function, when called, needs to be
		//placed in a try/catch block in 
		//order to output the error to the
		//screen.
		//************************************
		throw "ERROR: OUT-OF-BOUNDS";
	}
	else
	{
		return pixelVal[rowNum][colNum];
	}
}
//**********************************************
//Function name:setPixelVal
//Return Type:	Void
//Purpose:	Sets the value of the pixel at
//		the specified coordinates to
//		the desired value. Throws an 
//		OUT-OF-BOUNDS exception if the
//		coordinates fall outside the image.
//*********************************************
void Image::setPixelVal(int rowSpec, int colSpec, int value)
{
	if(rowSpec > N || colSpec > M)
	{
		//************************************
		//If the coordinates are outside the
		//image, this error will occur. This 
		//function, when called, needs to be
		//placed in a try/catch block in 
		//order to output the error to the
		//screen.
		//************************************
		throw "ERROR: OUT-OF-BOUNDS";
	}
	else
	{
		pixelVal[rowSpec][colSpec] = value;
	}
}
//**********************************************
//Function name:getSubImage
//Return Type:	Void
//Purpose:	Crops a rectangular area within
//		the image, as specified by the
//		coordinates of the upper left
//		corner of the area to be cropped
//		and the coordinates of the 
//		lower right corner of the
//		area to be cropped. An OUT-OF-
//		BOUNDS exception is thrown if
//		the coordinates falls outside
//		the range of the image.
//*********************************************
void Image::getSubImage(ULrows, ULcols, LRrows, LRcols, oldImage)
{
	if(ULrows > N || ULcols > M || LRrows > N || LRcols > M)
	{
		throw "ERROR: OUT-OF-BOUNDS";
	}
	else
	{
		
void Image::writeImage(char *fname, Image &image)
{
 int i, j;
 int N, M, Q;
 unsigned char *charImage;
 ofstream ofp;

 image.getImageInfo(N, M, Q);

 charImage = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

 int val;

 for(i=0; i<N; i++)
   for(j=0; j<M; j++) {
     image.getPixelVal(i, j, val);
     charImage[i*M+j]=(unsigned char)val;
   }

 ofp.open(fname, ios::out | ios::binary);

 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P5" << endl;
 ofp << M << " " << N << endl;
 ofp << Q << endl;

 ofp.write( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();

 delete [] charImage;

}

void Image::readImage(char *fname, Image &image)
{
 int i, j;
 int N, M, Q;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 ifp.getline(header,100,'\n');
 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=53) ) {   /* '5' */
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
 }
