COMPILER = g++
CFLAGS = -g -Wno-deprecated

# Primary target
driver:	image.h image.o \
		driver.cpp
	${COMPILER} -o driver $(CFLAGS) image.o  \
					driver.cpp


image.o:	image.h image.cpp
	${COMPILER} -c $(CFLAGS) image.cpp