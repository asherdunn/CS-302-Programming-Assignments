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
	cols = 0;
	rows = 0;
	grayMax = 0;
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
Image::Image(int col, int row, int grays)
{
	rows = row;
	cols = col;
	grayMax = grays;
	//*****************************************************
	//The 2D array requires a loop in order to fully allocate
	//the memory for it. One dimension of the array is allocated
	//outside the loop and then the loop allocates arrays of 
	//pointers to be given to the first dimension.
	//******************************************************
	pixelVal = new int *[cols];
	for(int colCount = 0; colCount < cols; colCount++)
	{
		pixelVal[colCount] = new int[rows];
		for(int rowCount = 0; rowCount < rows; rowCount++)
		{
			pixelVal[colCount][rowCount] = 0;
		}
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
	cols = copyImage.cols;
	rows = copyImage.rows;
	grayMax = copyImage.grayMax;
	pixelVal = new int *[rows];
	//***************************************************************
	//The nested for loop allocates rows to the pixelVal array and
	//fills the individual elements of the array with the copied
	//pixel values from the passed image.
	//***************************************************************
	for(int colCount = 0; colCount < cols; colCount++)
	{
		pixelVal[colCount] = new int[cols];
		for(int rowCount = 0; rowCount < rows; rowCount++)
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
	cout << "In deconstructor" << endl;
	for(int delRow = 0; delRow < rows; delRow++)
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
	rows = cols;
	cols = rows;
	max = grayMax;
}
//**********************************************
//Function name:getPixelVal
//Return Type:	Void
//Purpose:	Return the value of the pixel
//		at the specified coordinates.
//		Throws an OUT-OF-BOUNDS
//		exception if the coordinates
//		fall outside the image.	
//*********************************************
void Image::getPixelVal(int rowNum, int colNum, int &retVal)
{
	if(colNum > cols || rowNum > rows)
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
	//****************************************************
	//If the coordinates given are not out of bounds, the
	//function sets the retVal variable equal to the 
	//value of the pixel at the coordinates.
	//****************************************************
	else
	{
		retVal = pixelVal[rowNum][colNum];
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
	if(colSpec > cols || rowSpec > rows || rowSpec < 0 || colSpec < 0)
	{
		//************************************
		//If the coordinates are outside the
		//image, this error will occur. This 
		//function, when called, needs to be
		//placed in a try/catch block in 
		//order to output the error to the
		//screen.
		//************************************
		cout << "ERROR: OUT-OF-BOUNDS";
	}
	//****************************************************
	//If the coordinates given are not out of bounds, the
	//function sets the pixel value at the coordinates
	//equal to the new value.
	//****************************************************
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
void Image::getSubImage(int ULrows,int ULcols,int LRrows,int LRcols,Image &oldImage)
{
	if(ULcols > cols || ULrows > rows || LRcols > cols || LRrows > rows)
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
		int **tempPixel;
		//*******************************************************
		//Creating a temporary array to store the subimage. The
		//temporary array is made to be the exact size of the 
		//subimage, using the difference between the coordinates
		//passed to the function to calculate the size. 
		//*******************************************************
		tempPixel = new int *[(LRrows - ULrows)];
		for(int i = 0; i < (LRcols - ULcols); i++)
		{
			tempPixel[i] = new int[(LRcols - ULcols)];
		}
		//*******************************************************
		//This double nested for loop sorts through the old image
		//and finds the coordinates of the subimage and copies
		//that to the temporary image array.
		//*******************************************************
		for(int subCount = ULrows; subCount < LRrows; subCount++)
		{
			
			for(int subColCount = ULcols; subColCount < LRcols; subColCount++)
			{
				tempPixel[subCount][subColCount] = oldImage.pixelVal[subCount][subColCount];
			}
		}
		//*******************************************************
		//This for loop deallocates the subimage and then sets
		//the pixelVal pointer to the new image array before
		//the funciton ends.
		//*******************************************************
		for(int delRow = 0; delRow < cols; delRow++)
		{
			delete [] oldImage.pixelVal[delRow];
		}
		delete [] oldImage.pixelVal;
		oldImage.pixelVal = tempPixel;
	}
}
//**********************************************
//Function name:meanGray
//Return Type:	int
//Purpose:	Sums and calculates the mean 
//		gray level value of the image.
//*********************************************
int Image::meanGray()
{
	int mean;
	//*************************************************************
	//This double nested for loop sums all of the pixel values
	//in the image into a single integer value.
	//*************************************************************
	for(int rowGray = 0; rowGray < cols; rowGray++)
	{
		for(int colGray = 0; colGray < rows; colGray++)
		{
			mean = mean + pixelVal[rowGray][colGray];
		}
	}
	//**************************************************************
	//Calculating the mean by dividing the summed pixel values by
	//the number of pixels, calculated by multiplying the number
	//of columns by the number of rows before dividing the mean
	//by that number.
	//**************************************************************
	mean = mean / (rows * cols);
	return mean;
}
//**********************************************
//Function name:elargeImage
//Return Type:	Void
//Purpose:	Enlarges the base image by a 
//		scaling factor, sFactor.
//*********************************************
void Image::enlargeImage(int sFactor, Image &eImage)
{
	int **eTempPixel;
	//**************************************************
	//This loop allocates the memory needed for the 
	//temporary pixel array, calculated by
	//multiplying the columns and rows of the original
	//image by the scaling factor.
	//**************************************************
	eTempPixel = new int *[(eImage.cols * sFactor)];
	for(int i = 0; i < (eImage.cols * sFactor); i++)
	{
		eTempPixel[i] = new int[(eImage.rows * sFactor)];
	}
	//*************************************************************
	//The first two loops of this triple loop sort through the 
	//original image, incrementing along it and copying the values.
	//The third loop takes the values and places them into the new
	//array of the enlarged image by copying the pixels a number
	//of times equal to the scaling factor.
	//************************************************************
	for(int oriRowCount = 0; oriRowCount < eImage.cols; oriRowCount++)
	{
		for(int oriColCount = 0; oriColCount < eImage.rows; oriColCount++)
		{
			for(int scaleCount = 0; scaleCount < sFactor; scaleCount++)	
			{
				eTempPixel[oriRowCount][(oriColCount + sFactor)] = eImage.pixelVal[oriRowCount][oriColCount];
			}
		}
	}
	//*************************************************************
	//Deallocating 
	for(int delRow = 0; delRow < cols; delRow++)
	{
		delete [] eImage.pixelVal[delRow];
	}
	delete [] eImage.pixelVal;
	eImage.pixelVal = eTempPixel;
}
		
void writeImage(char fname[], Image &image)
{
 int i, j;
 int cols, rows, grayMax;
 unsigned char *charImage;
 ofstream ofp;

 image.getImageInfo(cols, rows, grayMax);

 charImage = (unsigned char *) new unsigned char [rows*cols];

 // convert the integer values to unsigned char

 int val;

 for(i=0; i<cols; i++)
   for(j=0; j<rows; j++) {
     image.getPixelVal(i, j, val);
     charImage[i*rows+j]=(unsigned char)val;
   }

 ofp.open(fname, ios::out | ios::binary);

 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P5" << endl;
 ofp << rows << " " << cols << endl;
 ofp << grayMax << endl;

 ofp.write( reinterpret_cast<char *>(charImage), (rows*cols)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();

 delete [] charImage;

}

void readImage(char fname[], Image &image)
{
 int i, j;
 int cols, rows, grayMax;
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

ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 rows=strtol(header,&ptr,0);
 cols=atoi(ptr);

 ifp.getline(header,100,'\n');
 grayMax=strtol(header,&ptr,0);

 charImage = (unsigned char *) new unsigned char [rows*cols];

 ifp.read( reinterpret_cast<char *>(charImage), (rows*cols)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();

 //
 // Convert the unsigned characters to integers
 //

 int val;
 for(i=0; i<cols; i++)
   for(j=0; j<rows; j++) {
     val = (int)charImage[i*rows+j];
     image.setPixelVal(i, j, val);  
   }
 delete [] charImage;
}

void readImageHeader(char fname[], int& cols, int& rows, int& grayMax, bool& type)
{
 int i, j;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 type = false; // PGM

 ifp.getline(header,100,'\n');
 if ( (header[0] == 80) &&  /* 'P' */
      (header[1]== 53) ) {  /* '5' */
      type = false;
 }
 else if ( (header[0] == 80) &&  /* 'P' */
      (header[1] == 54) ) {        /* '6' */
      type = true;
 } 
 else {
   cout << "Image " << fname << " is not PGM or PPM" << endl;
   exit(1);
 }

ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 rows=strtol(header,&ptr,0);
 cols=atoi(ptr);

 ifp.getline(header,100,'\n');

 grayMax=strtol(header,&ptr,0);

 ifp.close();

}
