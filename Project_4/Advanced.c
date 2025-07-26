#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "Image.h"
#include "Advanced.h" 

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
	assert(image != NULL);
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*ImageWidth(image)*ImageHeight(image))/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
		SetPixelR(image,x,y, 255);
		SetPixelG(image,x,y, 255);
		SetPixelB(image,x,y, 255);
	}
return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
	assert(image != NULL);
	int x, y;
	for(x=0; x<ImageWidth(image); x++) {
		for(y=0; y<ImageHeight(image); y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image,x,y, (GetPixelR(image,x,y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image,x,y, (GetPixelR(image,x,y) & one));

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image,x,y, (GetPixelG(image,x,y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image,x,y, (GetPixelG(image,x,y) & one));

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image,x,y, (GetPixelB(image,x,y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image,x,y, (GetPixelB(image,x,y) & one));
		}
	}
return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount)
{
	assert(image != NULL);
	int x,y,m;
	int temp_r , temp_g , temp_b;

	for (x = 0; x < ImageWidth(image); x++)
	{
        	for (y = ImageHeight(image) - 1; y >= 0 ; y--)
		{
			int count = 0;
			temp_r = temp_g = temp_b = 0;
			for (m = 1; m<=BlurAmount ; m++)
			{
				//if ((x-m) >= 0)
				if((y-m) >= 0)
				{
					temp_r += GetPixelR(image,x,y-m);
					temp_b += GetPixelB(image,x,y-m);
					temp_g += GetPixelG(image,x,y-m);
					count++;
				}
			}
			count = (count==0)?1:count;
			SetPixelR(image,x,y, (temp_r / 2.0 / count + GetPixelR(image,x,y) / 2.0));
			SetPixelB(image,x,y, (temp_b / 2.0 / count + GetPixelB(image,x,y) / 2.0));
			SetPixelG(image,x,y, (temp_g / 2.0 / count + GetPixelG(image,x,y) / 2.0));
		}
	}
return image;		
}

/* enlarge an image by the given percentage */
IMAGE *Enlarge(IMAGE *image, int percentage)
{
	assert(image != NULL);
	int x,y;
	unsigned char R = 0;
	unsigned char B = 0;
	unsigned char G = 0;
	int x0= 0;
	int y0= 0;
	float L = percentage/100.0; //enlarging factor
	//the new width and height 
	int New_W = (int)(ImageWidth(image)*L);
	int New_H = (int)(ImageHeight(image)*L);
	int x0Start;
	int x0End;
	int y0Start;
	int y0End;
	IMAGE *imageL = NULL;
	imageL = CreateImage(New_W, New_H);
	while (percentage <100)
	{
		printf("Please print a percentage 100 or above: ");
		scanf("%d", &percentage);	
	}
	for (x = 0; x < ImageWidth(image); x++)
	{
		x0Start = (int)(x*L);
		x0End   = (int)((x+1)*L);
		for (y = 0; y < ImageHeight(image); y++)
		{
			R = GetPixelR(image,x,y);  //getting the colors for the given (x,y) Pixel
			B = GetPixelB(image,x,y);
			G = GetPixelG(image,x,y);
			
			y0Start = (int)(y*L);
			y0End   = (int)((y+1)*L);
			y0 = y0Start;
			x0 = x0Start;
			while (x0 < x0End)
			{
				while (y0 < y0End)
				{
					SetPixelR(imageL,x0,y0,R); //set the pixel (x0,y0) = to the value from (x,y)
					SetPixelB(imageL,x0,y0,B);
					SetPixelG(imageL,x0,y0,G);
					y0++; //go down one pixel
				}
				x0++; //go across one pixel
				y0=y0Start; //make sure to start at top of current height section 
			}
			x0 = x0Start;
		}
	}
DeleteImage(image);
return imageL;
}

IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int square_size)
{
	assert(image != NULL);
        unsigned char R = 0;
        unsigned char B = 0;
        unsigned char G = 0;
	IMAGE *imageL = NULL;
	int D;
	
	D = square_size; //square length 
	// if I try to crop out of bounds 
	if (x_offset+D > ImageWidth(image))
	{
	D = ImageWidth(image) - x_offset;
	}
	if (y_offset+D > ImageHeight(image))
        {
        D = ImageHeight(image) - y_offset;
        }
	// The lesser of the two will determine the square size 
	
	
	// create square image
	imageL = CreateImage(D, D);
	for (int x = x_offset; x < x_offset+D; x++)
	{
		for (int y = y_offset; y < y_offset+D; y++)
		{
			R = GetPixelR(image,x,y);
			B = GetPixelB(image,x,y);
			G = GetPixelG(image,x,y);
			SetPixelR(imageL,x-x_offset,y-y_offset,R);
			SetPixelG(imageL,x-x_offset,y-y_offset,G);
			SetPixelB(imageL,x-x_offset,y-y_offset,B);
		}
	}
DeleteImage(image);				
return imageL;
}

/* Adjust the brightness and contrast of a given image */
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast)
{
	assert(image != NULL);
	int tmp_r, tmp_g, tmp_b;
	int tmp_r1, tmp_g1, tmp_b1;
	double factor;
	//contrast formula factor
	factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));
	for (int x = 0; x < ImageWidth(image); x++) 
	{
		for (int y = 0; y < ImageHeight(image); y++)
		{
			/* getting the colors for the given (x,y) Pixel */
			tmp_r = GetPixelR(image,x,y);  
                        tmp_b = GetPixelB(image,x,y);
                        tmp_g = GetPixelG(image,x,y);
			/* adding brightness to the intensities */
			tmp_r += brightness;
			tmp_b += brightness;
			tmp_g += brightness;
			/* adding in contrast */
			tmp_r1 = (int)(factor * (tmp_r - 128) + 128);
			//printf("%d **", tmp_r);
			tmp_b1 = (int)(factor * (tmp_b - 128) + 128);
			tmp_g1 = (int)(factor * (tmp_g - 128) + 128);
			/* accounting for underflow and overflow */
			SetPixelR(image,x,y, ((tmp_r1 > 255)?255:(tmp_r1 < 0)?0:tmp_r1));
			SetPixelG(image,x,y, ((tmp_g1 > 255)?255:(tmp_g1 < 0)?0:tmp_g1));
			SetPixelB(image,x,y, ((tmp_b1 > 255)?255:(tmp_b1 < 0)?0:tmp_b1));
		}
	}
return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
