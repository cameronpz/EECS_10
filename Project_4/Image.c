/* Image.c: file for basic image manipulations		     */ 
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include <assert.h>

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
//add asserts that image exists
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

//assert that coordinates are in the 600x400 image
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

// creating the 1D pixel out of the (x,y) coordinates
int pix;
pix = x + y*( ImageWidth(image));
return (image->R[pix]);
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
//add asserts that image exists
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

/* assert that coordinates are in the 600x400 image */
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

// creating the 1D pixel out of the (x,y) coordinates
int pix;
pix = x + y*( ImageWidth(image));
return (image->G[pix]);
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
//add asserts that image exists
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

/* assert that coordinates are in the 600x400 image */
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

// creating the 1D pixel out of the (x,y) coordinates 
int pix;
pix = x + y*( ImageWidth(image));
return (image->B[pix]);
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
//add asserts that image exists 
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

/* assert that coordinates are in the 600x400 image */
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

int pix;
pix = x + y*( ImageWidth(image));
image->R[pix] = r;
}
/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
//add asserts that image exists
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

/* assert that coordinates are in the 600x400 image */
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

int pix;
pix = x + y*( ImageWidth(image));
image->G[pix] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
//add asserts that image exists
assert(image != NULL);
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

/* assert that coordinates are in the 600x400 image */
assert(0<=x && x< ImageWidth(image));
assert(0<=y && y< ImageHeight(image));

int pix;
pix = x + y*( ImageWidth(image));
image->B[pix] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
//create a pointer that points to the struct and initialize to NULL
IMAGE *image = NULL;

//allocate memory for struct
image = malloc(sizeof(IMAGE));

//check malloc didn't return NULL (NULL => no free memory left)
if (image == NULL)
	{
	printf("out of memory");
	return (image);
	}
	
//allocate memory for the R/G/B values
image->R = malloc(sizeof(char)*Width*Height);
image->G = malloc(sizeof(char)*Width*Height);
image->B = malloc(sizeof(char)*Width*Height);

//save the user inputs of width and height
image->W= Width;
image->H = Height;

return(image);
}


/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
//add asserts that image exists before freeing memory
assert(image != NULL); 
assert((image->R) != NULL);
assert((image->B) != NULL);
assert((image->G) != NULL);

//free memory allocated to R/G/B values and then set pointers to NULL
free(image->R);
free(image->G);
free(image->B);
image->R = NULL;
image->G = NULL;
image->B = NULL;
free(image);
image = NULL;

}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
return(image->W);
}
/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
return(image->H);
}
