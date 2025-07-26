//This file is the main file of the program, including the main function, the print menu function, and the AutoTest function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

void PrintMenu();
void AutoTest(void);

int main() {
    unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
    #ifdef DEBUG
    AutoTest();
    return 0;
    #endif /* DEBUG */

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */
    // char colorOption[SLEN]; /* color option place holder */
    int rc = -1;            /* return code of ReadImage() */
    int hue;            // degree of hue change
    int noise;          // percentage of noise
    int BlurAmount;     //Blur amount
    int rbits, gbits, bbits; //inputs for Posterize filter, rbits => nth LSB for red, etc.

    PrintMenu();
    scanf("%d", &option);
    
    while (option != EXIT)
    {
    	hue = 0;      
    	noise = -1;     
    	BlurAmount = 0;    
    	rbits = 0;
	bbits = 0;
	gbits = 0; 
        if (option == 1)
        {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        /* menu item 2 - 10 requires image is loaded first */
        else if (option >= 2 && option <= 8)
        {
            if (rc != SUCCESS)
            {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else
            {
                switch(option)
                {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        BlackNWhite(R, G, B);
			SaveImage("bw", R, G, B); //save image as bw.ppm
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        Sharpen(R, G, B);
			SaveImage("sharpen", R, G, B); //save image as sharpen.ppm
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        Hue(R, G, B, hue);
			SaveImage("hue", R, G, B); //save image as hue.ppm
                        printf("\"Hue\" operation is done!\n");
                        break;
		    case 6:
                        printf("Please input noise percentage: ");
                        if (noise<0 || noise>100) //must pick a valid percentage (from 0 to 100)
			{
			scanf("%d", &noise);
			}
                        Noise(noise, R, G, B);
			SaveImage("noise", R, G, B); //save image as noise.ppm
                        printf("\"Noise\" operation is done!\n");
                        break;
		    case 7:
                        printf("Enter the number of posterization bits for R channel (1 to 8): ");
			if (rbits<1 || rbits>8) //making sure that input is valid
				{
				scanf("%d", &rbits);
				}
                        printf("Enter the number of posterization bits for G channel (1 to 8): ");
		        if (gbits<1 || gbits>8) //making sure that input is valid
                                {
                                scanf("%d", &gbits);
                                }
		        printf("Enter the number of posterization bits for B channel (1 to 8): ");
                        if (bbits<1 || bbits>8) //making sure that input is valid
                                {
                                scanf("%d", &bbits);
                                }
                        Posterize(R, G, B, rbits, gbits, bbits);
			SaveImage("posterize", R, G, B); //save image as posterize.ppm
                        printf("\"Posterize\" operation is done!\n");
                        break;
		    case 8:
                        printf("Please input motion blur amount: ");
                        scanf("%d", &BlurAmount);
                        MotionBlur(BlurAmount, R, G, B);
			SaveImage("blur", R, G, B); //save image as blur.ppm
                        printf("\"Motion Blur\" operatin is done!\n");
                        break;
                    default:
                        break;
                }
            }
        }
        else if (option == 9) {
            AutoTest();
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        } 
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
    return 0;
}
void PrintMenu() //function prints the menu
{
    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Motion Blur\n");
    printf("9: Test all functions\n");
    printf("10: Exit\n");
    printf("--------------------------\n");
    printf("Please make your choice: ");
}

//function tests all DIP operations with the default values for DIP operations that require them
void AutoTest(void) {

    unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];
    char fname[SLEN] = "CrystalChurch";

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    #ifdef DEBUG
    printf("Black and White tested!\n\n");
    #endif /* DEBUG */

    LoadImage(fname, R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    #ifdef DEBUG
    printf("Sharpen tested!\n\n");
    #endif /* DEBUG */

    LoadImage(fname, R, G, B);
    Hue(R, G, B, 120);
    SaveImage("hue", R, G, B);
    #ifdef DEBUG
    printf("Hue tested!\n\n");
    #endif /* DEBUG */

    LoadImage(fname, R, G, B);
    Noise(30, R, G, B);
    SaveImage("noise", R, G, B);
    #ifdef DEBUG
    printf("Noise tested!\n\n");
    #endif /* DEBUG */

    LoadImage(fname, R, G, B);
    Posterize(R, G, B, 7, 7, 7);
    SaveImage("posterize", R, G, B);
    #ifdef DEBUG
    printf("Posterize tested!\n\n");
    #endif /* DEBUG */

    LoadImage(fname, R, G, B);
    MotionBlur(50, R, G, B);
    SaveImage("blur", R, G, B);
    #ifdef DEBUG
    printf("MotionBlur tested!\n\n");
    #endif /* DEBUG */
}

