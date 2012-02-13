#ifndef image_h
#define image_h


class Image
{
public:
	Image();
	Image(int , int , int);
	Image(const Image &);
	~Image();
	void getImageInfo(int &, int &, int &);
	void getPixelVal(int, int, int &);
	void setPixelVal(int, int, int);
	void getSubImage(int, int, int, int, Image &);
	int meanGray();
	void enlargeImage(int, Image &);
	void shrinkImage(int, Image &);
	void reflectImage(int, Image &);
	void translateImage(int, Image &);
	void rotateImage(int, Image &);
	void negateImage(Image &);
	Image operator+(const Image &);
	Image operator-(const Image &);
	const Image operator=(const Image &);
private:
	int rows, cols, grayMax;
	int **pixelVal;
};

	void readImage(char[], Image &);
	void writeImage(char[], Image &);
	void readImageHeader(char[], int &, int &, int &, bool &);
	void menu();
#endif
	
	
	
