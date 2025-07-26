######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2017
#
# 11/08/17 Mina Moghadam : updated for EECS22 Assignment 3 Fall 2017
# 10/08/16 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2016
# 10/17/15 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2015
# 10/21/14 Nistha Tandiya: updated for EECS22 Assignment 3 Fall 2014
# 10/27/13 Yasaman Samei : updated for EECS22 Assignment 3 Fall 2013
# 10/16/11 Weiwei Chen   : updated for EECS22 Assignment 3 Fall 2012
# 10/10/11 Weiwei Chen   : initial solution version
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         sharpen.ppm \
         hue.ppm \
         noise.ppm \
         posterize.ppm \
         blur.ppm

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Image.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h Image.h Test.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h Image.h Test.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o

#target to generate Image.o
Image.o: Image.h Image.c
	$(CC) $(CFLAGS) $(DEBUG) -c Image.c -o Image.o

#target to generate Test.o
Test.o: Test.h Test.c Constants.h Image.h FileIO.h DIPs.h Advanced.h
	$(CC) $(CFLAGS) $(DEBUG) -c Test.c -o Test.o

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: PhotoLab.o FileIO.o libFilter.a Image.o Test.o DIPs.o Advanced.o 
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o DIPs.o Advanced.o Test.o -L. -lFilter -o PhotoLab -lm

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o libFilter.a Image.o Test.o DIPs.o Advanced.o
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o FileIO.o Image.o Advanced.o DIPs.o Test.o -L. -lFilter -o PhotoLabTest -lm

#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

