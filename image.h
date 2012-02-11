#ifndef image_h
#define image_h


class Image
{
public:
	Image();
	Image(int , int , int);
	Image(const Image &);
	~Image();
	void readImage(char *, Image &);
	void writeImage(char *, const Image &);
	void getImageInfo(int &, int &, int &);
	int getPixelVal(int, int);
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
	int N, M, Q;
	int **pixelVal;
};

#endif
	
	
	
