#include "Image.h"
#include "DIPs.h"
#include "Constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

/* Example of DIP */
/* make the picture color black & white */

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    assert(image != NULL);
    int x, y;
    for (x = 0; x < ImageWidth(image); x++)
    {   for(y = 0; y < ImageHeight(image); y++)
        {   
		SetPixelR(image,x,y,(GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y)) / 3);
		SetPixelG(image,x,y,GetPixelR(image,x,y));
		SetPixelB(image,x,y,GetPixelR(image,x,y));
        }
    }
return image; 
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{
    assert(image != NULL);
    int x, y;
    IMAGE *timage;
    timage = CreateImage(ImageWidth(image), ImageHeight(image));

    int tmpr = 0, tmpg = 0, tmpb = 0;
    for (x = 0; x < ImageWidth(image); x++)
    {   for(y = 0; y < ImageHeight(image); y++)
        {   
	    SetPixelR(timage,x,y, GetPixelR(image,x,y));
	    SetPixelG(timage,x,y, GetPixelG(image,x,y));
            SetPixelB(timage,x,y, GetPixelB(image,x,y));
        }
    }
    for (x = 1; x < ImageWidth(image) - 1; x++)
    {   for (y = 1; y < ImageHeight(image) - 1; y++)
        {   tmpr = 9 * GetPixelR(image,x,y) - GetPixelR(image,x-1,y-1) - GetPixelR(image,x-1,y) - GetPixelR(image,x-1,y+1) - GetPixelR(image,x,y-1) - GetPixelR(image,x,y+1) - GetPixelR(image,x+1,y-1) - GetPixelR(image,x+1,y) - GetPixelR(image,x+1,y+1);
            tmpg = 9 * GetPixelG(image,x,y) - GetPixelG(image,x-1,y-1) - GetPixelG(image,x-1,y) - GetPixelG(image,x-1,y+1) - GetPixelG(image,x,y-1) - GetPixelG(image,x,y+1) - GetPixelG(    image,x+1,y-1) - GetPixelG(image,x+1,y) - GetPixelG(image,x+1,y+1);
	    tmpb = 9 * GetPixelB(image,x,y) - GetPixelB(image,x-1,y-1) - GetPixelB(image,x-1,y) - GetPixelB(image,x-1,y+1) - GetPixelB(image,x,y-1) - GetPixelB(image,x,y+1) - GetPixelB(    image,x+1,y-1) - GetPixelB(image,x+1,y) - GetPixelB(image,x+1,y+1);
        SetPixelR(timage,x,y, ((tmpr > 255)?255:(tmpr < 0)?0:tmpr));
	SetPixelG(timage,x,y, ((tmpg > 255)?255:(tmpg < 0)?0:tmpg));
        SetPixelB(timage,x,y, ((tmpb > 255)?255:(tmpb < 0)?0:tmpb));
        tmpr = tmpg = tmpb = 0;
        }
    }
    for (x = 0; x < ImageWidth(image); x++)
    {   for(y = 0; y < ImageHeight(image); y++)
        {   
	    SetPixelR(image,x,y, GetPixelR(timage,x,y));
            SetPixelG(image,x,y, GetPixelG(timage,x,y));
            SetPixelB(image,x,y, GetPixelB(timage,x,y));
        }
    }
    DeleteImage(timage);
return image;
}


// Hue function
IMAGE *Hue(IMAGE *image, int degree)
{
    assert(image != NULL);
    int x, y;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmp_r, tmp_g, tmp_b;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x < ImageWidth(image); x++)
    {   for (y = 0; y < ImageHeight(image); y++)
        {   tmp_r = GetPixelR(image,x,y) * a + GetPixelG(image,x,y) * b + GetPixelB(image,x,y) * r;
            tmp_g = GetPixelR(image,x,y) * r + GetPixelG(image,x,y) * a + GetPixelB(image,x,y) * b;
            tmp_b = GetPixelR(image,x,y) * b + GetPixelG(image,x,y) * r + GetPixelB(image,x,y) * a;

            SetPixelR(image,x,y, ((tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r));
	    SetPixelG(image,x,y, ((tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g));
            SetPixelB(image,x,y, ((tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b));
        }
    }
return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
