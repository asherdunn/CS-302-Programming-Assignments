#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "image.h"

ImageType::ImageType()
{
 N = 0;
 M = 0;
 Q = 0;

 pixelValue = NULL;
}

ImageType::ImageType(int tmpN, int tmpM, int tmpQ)
{
 int i, j;

 N = tmpN;
 M = tmpM;
 Q = tmpQ;

 pixelValue = new int* [N];
 for(i=0; i<N; i++)
 {
   pixelValue[i] = new int[M];
   for(j=0; j<M; j++)
   {
        pixelValue[i][j] = 0;
   }
 }
}

ImageType::~ImageType()
{
	for (int colCount=0; colCount < N; colCount++)
    {
		delete [] pixelValue [colCount];
    }
	delete [] pixelValue;
}

void ImageType::getImageInfo(int& rows, int& cols, int& levels)
{
    rows = N;
    cols = M;
    levels = Q;
} 

void ImageType::setImageInfo(int rows, int cols, int levels)
{
    N= rows;
    M= cols;
    Q= levels;
} 

void ImageType::setPixelVal(int i, int j, int pixelV)
{
 pixelValue[i][j] = pixelV;
}

void ImageType::getPixelVal(int i, int j, int& pixelV)
{
 pixelV = pixelValue[i][j];
}

void ImageType::Threshold(ImageType& image)
{
    int thresh, pixelV;
    
    cout << "Enter threshold: ";
    cin >> thresh;

 // threshold image 

 for(int i=0; i<N; i++)
    for(int j=0; j<M; j++) 
    {
    image.getPixelVal(i, j, pixelV);
    if(pixelV < thresh) 
        image.setPixelVal(i, j, 255);
    else
        image.setPixelVal(i, j, 0);
    }
    
}

/*ImageType& ImageType::Scale(ImageType& image)
//{
//	int pixelV;
//	float size;
//  	cout << "Enter multiplier \n";
//	cin >> size;
//	// allocate memory for the image array
//	int MM=int(ceil(M*size));
//	int NN=int(ceil(N*size));
//	ImageType imageScaled(NN, MM, Q);
//	
//	// enlarge image 
//	for(int i=0; i<N; i++)
//    {
//		for(int j=0; j<M; j++) 
//        {
//			image.getPixelVal(i, j, pixelV);
//			imageScaled.setPixelVal(int(floor(i*size)), int(floor(j*size)), pixelV);
//
//		}
 //   }
 //   return imageScaled;
}
*/

// Overloaded operator functions
ImageType ImageType::operator = (const ImageType & image)
{
	for (int colCount=0; colCount < N; colCount++)
    {
		delete [] pixelValue [colCount];
    }
	delete [] pixelValue;    
}

void readImageHeader(char fname[], int& N, int& M, int& Q, bool& type)
{
    int i, j;
    unsigned char *charImage;
    char header [100], *ptr;
    ifstream ifp;

    ifp.open(fname, ios::in | ios::binary);

    if (!ifp) 
    {
    cout << "Can't read image: " << fname << endl;
    exit(1);
    }

 // read header

    type = false; // PGM

    ifp.getline(header,100,'\n');
    if ( (header[0] == 80) &&  /* 'P' */
         (header[1]== 53) ) 
        {  /* '5' */
            type = false;
        }
    else if ( (header[0] == 80) &&  /* 'P' */
              (header[1] == 54) ) 
            {
                /* '6' */
                type = true;
            } 
    else 
    {
        cout << "Image " << fname << " is not PGM or PPM" << endl;
        exit(1);
    }

    ifp.getline(header,100,'\n');
    while(header[0]=='#')
        ifp.getline(header,100,'\n');

    M=strtol(header,&ptr,0);
    N=atoi(ptr);

    ifp.getline(header,100,'\n');

    Q=strtol(header,&ptr,0);

    ifp.close();

}

void readImage(char fname[], ImageType& image)
{
    int i, j;
    int N, M, Q;
    unsigned char *charImage;
    char header [100], *ptr;
    ifstream ifp;

    ifp.open(fname, ios::in | ios::binary);

    if (!ifp) 
    {
        cout << "Can't read image: " << fname << endl;
        exit(1);
    }

 // read header

    ifp.getline(header,100,'\n');
    if ( (header[0]!=80) ||    /* 'P' */
         (header[1]!=53) ) 
    {   /* '5' */
            cout << "Image " << fname << " is not PGM" << endl;
            exit(1);
    }

    ifp.getline(header,100,'\n');
    while(header[0]=='#')
        ifp.getline(header,100,'\n');

    M=strtol(header,&ptr,0);
    N=atoi(ptr);

    ifp.getline(header,100,'\n');
    Q=strtol(header,&ptr,0);

    charImage = (unsigned char *) new unsigned char [M*N];

    ifp.read( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

    if (ifp.fail()) 
    {
        cout << "Image " << fname << " has wrong size" << endl;
        exit(1);
    }

    ifp.close();

 //
 // Convert the unsigned characters to integers
 //

    int val;

    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++) 
        {
            val = (int)charImage[i*M+j];
            image.setPixelVal(i, j, val);     
        }
    }

    delete [] charImage;

}

void writeImage(char fname[], ImageType& image)
{
    int i, j;
    int N, M, Q;
    unsigned char *charImage;
    ofstream ofp;

    image.getImageInfo(N, M, Q);

    charImage = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

    int pixelV;

    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++) 
        {
            image.getPixelVal(i, j, pixelV);
            charImage[i*M+j]=(unsigned char)pixelV;
        }
    }

    ofp.open(fname, ios::out | ios::binary);

    if (!ofp) 
    {
        cout << "Can't open file: " << fname << endl;
        exit(1);
    }

    ofp << "P5" << endl;
    ofp << M << " " << N << endl;
    ofp << Q << endl;

    ofp.write( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

    if (ofp.fail()) 
    {
        cout << "Can't write image " << fname << endl;
        exit(0);
    }

    ofp.close();

    delete [] charImage;

}