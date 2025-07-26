#include <stdio.h>
#include <string.h>
#include "Image.h"
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{

#ifdef DEBUG
    AutoTest();
#else
    IMAGE *image = NULL;
    IMAGE *imout = NULL;
    int rc;
    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    PrintMenu();
    scanf("%d", &option);

    /* Hue() parameter */
    int hue;

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* MotionBlur() parameter */
    int blur_amount;
    
    /* Enlarge() parameter */
    int percentage = 0;

    /* Square() parameter */
    int x_o;
    int y_o;
    int sq;

    /* BrightnessandContrast() parameter */
    int b, c;

    while (option != EXIT) {
        if(option == 1) {
	    if (image != NULL)
	        {
		DeleteImage(image);
		image = NULL;
		}
	    printf("Please input the file name to load: ");
            scanf("%s", fname);
            image = LoadImage(fname);
            imout = image;
	    //setting both pointers to the same image
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 12) 
	{
	     if (image == NULL && imout == NULL) //if both pointers are NULL then we aren't pointing to any image. 
		{
                printf("No image to process");
                } 
            /* now image is loaded */
            else 
		{
                switch (option)		
		    {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
			if (imout != NULL)
			{
                        SaveImage(fname, imout);
			DeleteImage(imout);
			imout = NULL;
			image = NULL;
	                } //after we save, we delete the image and set the pointers to NULL
                        break;
                    case 3:
                        imout = BlackNWhite(image);
			printf("\"Black amd White\" operation is done!\n");
                        break;
                    case 4:
                        imout = Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        imout = Hue(image, hue);
                        printf("\"Hue\" operatin is done!\n");
			break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        imout = Noise(image, n);
                        printf("\"Noise\" operation is done!\n");
			break;
                    case 7:
                        printf("Enter the number of posterization bits for R channel (1 to 8): ");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G channel (1 to 8): ");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B channel (1 to 8): ");
                        scanf("%hhu", &bbits);
                        imout = Posterize(image, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
			break;
                    case 8:
                        printf("Please input the amount of blur: ");
                        scanf("%d", &blur_amount);
                        imout = MotionBlur(image, blur_amount);
                        printf("\"Motion Blur Filter\" operation is done!\n");
                        break;
		    case 9:
			printf("Please input the enlarging percentage (integer between 100 - 200): ");
			scanf("%d", &percentage);
			imout = Enlarge(image, percentage);
			image = imout;
			printf("\"Enlarge the image\" operation is done!\n");
			break;
		    case 10:
			printf("Please enter the X offset value: ");
			scanf("%d", &x_o);
			printf("Please enter the Y offset value: ");
			scanf("%d", &y_o);
			printf("Please input the cropped square size: ");
			scanf("%d", &sq);
			imout = Square(image, x_o, y_o, sq); 
			image = imout;
			printf("\"Square\" operation is done!\n");
			break; 
		    case 11:
			printf("Please input the brightness level (integer between -255 - 255): ");
			scanf("%d", &b);
			while (b<-255 || b>255)
			{
			printf("Please enter a valid input (integer between -255 - 255): ");
			scanf("%d", &b);
			}
			printf("Please input the contrast level (integer between -255 - 255): ");
			scanf("%d", &c);
			while (c<-255 || c>255)
                        {
                        printf("Please enter a valid input (integer between -255 - 255): ");
                        scanf("%d", &c);
                        }	
			imout = BrightnessandContrast(image, b, c);
			printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
			break;
		    default:
                        break;

                   }//end of case
            }//end of else
        }//end of else if

        else if (option == 12) {
            rc = AutoTest(); 
	    if (rc != 0)
		{
		printf("AutoTest failed, error code %d", rc);
		}
	    printf("AutoTest finished successfully");
            rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }
        /* Process finished, waiting for another input */
	PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");

if (imout != NULL)
	{
        DeleteImage(imout);
        imout = NULL;
        image = NULL;
        } 
if (image != NULL)
	{
	image = NULL;
	}
#endif

 return 0;
}

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add Noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Motion blur an image\n");
    printf("9: Enlarge the picture by percentage\n");
    printf("10: Crop a square portion of the image\n");
    printf("11: Adjust the Brightness and Contrast of an image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
