CFLAGS = -g -Wno-deprecated

image.o:	image.h image.cpp
	g++ -c $(CFLAGS) image.cpp


