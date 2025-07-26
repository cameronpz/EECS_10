#Makefile: PhotoLab_v2 //aka for Assignment 3

# convenience targets
all: PhotoLab PhotoLabTest

clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest
	rm -f blur.ppm
	rm -f posterize.ppm
	rm -f bw.ppm
	rm -f hue.ppm
	rm -f sharpen.ppm
	rm -f noise.ppm
# compilation rules

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o
PhotoLab.o: PhotoLab.c Constants.h FileIO.h DIPs.h Advanced.h
	gcc -Wall -ansi -std=c99 -c PhotoLab.c -o PhotoLab.o
PhotoLabTest.o: PhotoLab.c Constants.h FileIO.h DIPs.h Advanced.h
	gcc -Wall -ansi -std=c99 -c PhotoLab.c -DDEBUG -o PhotoLabTest.o
DIPs.o: DIPs.c Constants.h DIPs.h
	gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o
Advanced.o: Advanced.c Constants.h Advanced.h
	gcc -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o
PhotoLab: FileIO.o PhotoLab.o DIPs.o Advanced.o
	gcc -Wall -ansi -std=c99 FileIO.o PhotoLab.o DIPs.o Advanced.o -lm -o PhotoLab
	
PhotoLabTest: FileIO.o PhotoLabTest.o DIPs.o Advanced.o
	gcc -Wall -ansi -std=c99 FileIO.o PhotoLabTest.o DIPs.o Advanced.o -lm -o PhotoLabTest

