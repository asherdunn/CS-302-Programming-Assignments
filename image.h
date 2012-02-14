#ifndef IMAGE_H
#define IMAGE_H

// a simple example - you would need to add more funtions

class ImageType {
 public:
    ImageType();
    ImageType(int, int, int);
	~ImageType();
    void getImageInfo(int&, int&, int&);
    void setImageInfo(int, int, int);
    void setPixelVal(int, int, int);
    void getPixelVal(int, int, int&);
    void Threshold(ImageType&);
//    ImageType& Scale(ImageType&);
    // Overloaded operator functions
    ImageType operator = (const ImageType &);
 private:
    int N, M, Q;
    int **pixelValue;
};

    void readImageHeader(char[], int&, int&, int&, bool&);
    void readImage(char[], ImageType&);
    void writeImage(char[], ImageType&);
#endif
