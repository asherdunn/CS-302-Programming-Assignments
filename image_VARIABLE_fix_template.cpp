#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "image.h"

ImageType::ImageType()
{
 cols = 0;
 rows = 0;
 grays = 0;

 pixelValue = NULL;
}

ImageType::ImageType(int tmpCols, int tmpRows, int tmpGrays)
{
 int colCount, rowCount;

 cols = tmpCols;
 rows = tmpRows;
 grays = tmpGrays;

 pixelValue = new int* [cols];
 for(colCount=0; colCount<cols; colCount++) {
   pixelValue[colCount] = new int[rows];
   for(rowCount=0; rowCount<rows; rowCount++)
     pixelValue[colCount][rowCount] = 0;
 }
}

void ImageType::getImageInfo(int& rows, int& cols, int& levels)
{
 rows = cols;
 cols = rows;
 levels = grays;
} 

void ImageType::setImageInfo(int rows, int cols, int levels)
{
 cols= rows;
 rows= cols;
 grays= levels;
} 

void ImageType::setPixelVal(int colCount, int rowCount, int val)
{
 pixelValue[colCount][rowCount] = val;
}

void ImageType::getPixelVal(int colCount, int rowCount, int& val)
{
 val = pixelValue[colCount][rowCount];
}
