//c file for advanced DIP operations noise, posterize, and motion blur 
#include "Constants.h"
#include "Advanced.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* add noise to an image */
void Noise( int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x,y;
	int npix = n*WIDTH*HEIGHT/100; //taking the percentage n inputted by user and implementing the formula to get the number of pixels
	srand(time(NULL)); //sets to current time
for (int i=0; i<npix; i++) //sets white pixels to "npix" amount of pixels
{
	x = rand()% WIDTH; 
	y = rand()% HEIGHT;
	R[x][y]=255; 
	G[x][y]=255; 
	B[x][y]=255; //R, G, B as 255 => white
}	
	
}
/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int x, y;
	int bnum = 255;
	int rnum = 255;
	int gnum = 255;

	int bor = 0;
	int ror = 0;
	int gor = 0;
	
	/* first part is taking the number 255 (which has all bits as 1) & adding a 0 to the bbits bit */
	bnum ^= (1<<(bbits-1));//we have -1 since we want to go to the bbits bit and shifting 0 ius at the 1st bit so shifting bbits-1 bits will get us to the bbits bit
	rnum ^= (1<<(rbits-1));
	gnum ^= (1<<(gbits-1));

	/*this next part starts with 0 & places all 1s on the LSB bits starting with the bbits-1 bit (or the rbbits-1 or gbits-1) */
	for (int i=bbits-2;i>=0; i--) 
	{
		bor ^= (1<<i);
	}
	 for (int i=rbits-2;i>=0; i--)
        {
                ror ^= (1<<i);
        }
	 for (int i=gbits-2;i>=0; i--)
        {
                gor ^= (1<<i);
        }

	/*we first & the color of the pixel to bnum. Since bnum is all 1s except for the bbits  bit, all bits will be unchaged except the bbits bit which will go to 0 */
	/*take this new value and | it w/ bor. Bor is all 0s except for all the LSB bits bbits-1. All bits will be unchanged except the LSB bits -1 which will be all 1*/
	/*I used bbits, bnum, and bor as the example. This applies for all three colors */
	for( y = 0; y < HEIGHT; y++ ) {
		for( x = 0; x < WIDTH; x++ ) {
			B[x][y] = B[x][y] & bnum; 
			B[x][y] = B[x][y] | bor;
			R[x][y] = R[x][y] & rnum;
			R[x][y] = R[x][y] | ror;
			G[x][y] = G[x][y] & gnum;
			G[x][y] = G[x][y] | gor;
        }
}
}
/*motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	unsigned char R_temp[WIDTH][HEIGHT];
	unsigned char G_temp[WIDTH][HEIGHT];
	unsigned char B_temp[WIDTH][HEIGHT];
	int rsum[WIDTH][HEIGHT] = {};
	int bsum[WIDTH][HEIGHT] = {};
	int gsum[WIDTH][HEIGHT] = {};
	int x, y;
	int r2sum[WIDTH][HEIGHT] = {};
        int b2sum[WIDTH][HEIGHT] = {};
        int g2sum[WIDTH][HEIGHT] = {};


//here we are assigning temp pixels to all pixels
for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R_temp[x][y] = R[x][y];
            G_temp[x][y] = G[x][y];
            B_temp[x][y] = B[x][y];
        }
    }

//summing up the pixels that have "BlurAmount" number of pixels above it
for (x = 0; x < WIDTH; x++)
    {
    for(y = BlurAmount; y < HEIGHT; y++)
		{
		for (int i=y-1; i>=(y-BlurAmount); i--)
			{	
				rsum[x][y] += R[x][i];
				gsum[x][y] += G[x][i];
				bsum[x][y] += B[x][i];
			}
		}
    }
//applying the above summations to the pixels that have "BlurAmount" number of pixels above it
for (x = 0; x < WIDTH; x++)
    {
	for(y = BlurAmount; y < HEIGHT; y++) 
	{
		R_temp[x][y] = (R[x][y]/2) + ((rsum[x][y])/BlurAmount)/2;
		G_temp[x][y] = (G[x][y]/2) + ((gsum[x][y])/BlurAmount)/2;
		B_temp[x][y] = (B[x][y]/2) + ((bsum[x][y])/BlurAmount)/2;
	}
    }
//summing up pixels that hve less than "BlurAmount" number of pixels above it
for(y = 0; y < BlurAmount; y++)
	{
	for (x = 0; x < WIDTH; x++)
		{
		for (int i=y-1; i>=0; i--)
                        {
                                r2sum[x][y] += R[x][i];
                                g2sum[x][y] += G[x][i];
                                b2sum[x][y] += B[x][i];
                        }
                }


	}	

//applying the above summations to the pixels that have less than "BlurAmount" number of pixels above it
for (x = 0; x < WIDTH; x++)
    {
        for(y = 1; y < BlurAmount; y++)
        {
                R_temp[x][y] = (R[x][y]/2) + ((r2sum[x][y])/y)/2;
                G_temp[x][y] = (G[x][y]/2) + ((g2sum[x][y])/y)/2;
                B_temp[x][y] = (B[x][y]/2) + ((b2sum[x][y])/y)/2;
        }
    }

//since we can't divide by zero, I have applied the top row by itself
for (x = 0; x < WIDTH; x++)
    {
	R_temp[x][0] = (R[x][y]/2);
        G_temp[x][0] = (G[x][y]/2);
        B_temp[x][0] = (B[x][y]/2);
    }

//here we need to assign the temp pixels we changed back to the pixels of the image so that the changes will be applied 
for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R[x][y] = R_temp[x][y];
            G[x][y] = G_temp[x][y];
            B[x][y] = B_temp[x][y];
        }
    }
 
} // } for the function 

