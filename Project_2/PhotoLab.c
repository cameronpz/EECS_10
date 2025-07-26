/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Summer 2022                 */
/* First Name: Cameron	
 * Last Name: Peterson-Zopf	
 * UCInet ID:57999719	
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** global definitions ***/

#define WIDTH  600		/* image width */
#define HEIGHT 400		/* image height */
#define SLEN    64		/* maximum length of file names */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
/* written for you; should not been modified */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
/* written for you; should not been modified */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* aging the photo */
/* sample function to get you started */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* chaneg the image hue */
void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


/* retval=1 => load; retval =2 => save; retval =3 => bw; retval =4 => sharpen; retval=5 => hue; retval = 6 => AutoTest; retval = 7 => exit; */
void PrintMenu(void)
{
   printf("1: Load a PPM image\n2: Save the image in PPM and JPEG format\n");
   printf("3: Change the color image to black and white\n4: Sharpen the image\n"); 
   printf("5: Change the hue of image\n6: Test all functions\n7: Exit\n");
}

int main(void)
{
 /* Two dimensional arrays to hold the current image data, */
 /* one array for each color component.                    */
 unsigned char   R[WIDTH][HEIGHT];
 unsigned char   G[WIDTH][HEIGHT];
 unsigned char   B[WIDTH][HEIGHT];
 int menu_option= 0;
 char name[SLEN];
 PrintMenu();
 
 while ((menu_option !=1) && (menu_option != 2) && (menu_option != 3) && (menu_option != 4) && (menu_option != 5) && (menu_option != 6) && menu_option != 7)
        {
        printf("Please make your choice: ");
        scanf("%d", &menu_option);
	printf("\n");
        }
    if (menu_option == 1)
        {
        printf("Please input the file name to load: ");
	scanf("%s", name);
	LoadImage(name, R, G, B);
        }
    if (menu_option == 2)
        {
        printf("Please input the file name to save: ");
        scanf("%s", name);
	SaveImage(name, R, G, B);
        }
    if (menu_option == 3)
        {
        LoadImage("applestore", R, G, B);  
	BlackNWhite(R, G, B); //run the DIP function 
        SaveImage("bw", R, G, B); //save image as bw.ppm
        printf("\"Black & White\" operation is done!");
	}
    if (menu_option == 4)
        {
	LoadImage("applestore", R, G, B);
        Sharpen(R, G, B);
	SaveImage("sharpen", R, G, B); //save image as bw.ppm
        printf("\"Sharpen\" operation is done!");
	}
    if (menu_option == 5)
        {
	LoadImage("applestore", R, G, B);
        Hue(R, G, B, 120);
	SaveImage("hue", R, G, B); //save image as bw.ppm
        printf("\"Hue\" operation is done!");
	}
    if (menu_option == 6)
         {
         AutoTest(R, G, B);
         }
    if (menu_option == 7)
         {
         printf("Exiting Program");
         return 7; //returning 7 => we exited program by selecting exit from menu
         }

 return 0;
}

/* takes in a file name without extension */
/* writes file into R, G, B arrays */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

/* takes R, G, B arrays and writes it in a file */
/* filename (fname) has no extension */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	    B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
            R[x][y] = (unsigned char) (B[x][y]*1.6);
            G[x][y] = (unsigned char) (B[x][y]*1.6);
	}
    }
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("applestore", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
    printf("Aging tested!\n\n");
    
    LoadImage("applestore", R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("bw tested!\n\n"); 
         
    LoadImage("applestore", R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B); 
    printf("sharpen tested!\n\n"); 
 
    LoadImage("applestore", R, G, B);
    Hue(R, G, B, 120);
    SaveImage("hue", R, G, B);
    printf("hue tested!\n\n");
      
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/
//converts the image to a black and white image
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{ 
 int x, y;
     for( y = 0; y < HEIGHT; y++ ) {
         for( x = 0; x < WIDTH; x++ ) {
             B[x][y] = (( R[x][y]+G[x][y]+B[x][y] )/3);
             R[x][y] = B[x][y];
             G[x][y] = B[x][y];
         }
     }
}

//sharpens the image 
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
 int x,y, Bint, Rint, Gint;
 unsigned char tR[WIDTH][HEIGHT];
 unsigned char tG[WIDTH][HEIGHT];
 unsigned char tB[WIDTH][HEIGHT];

     for( y = 1; y < HEIGHT-1; y++ ) {
         for( x = 1; x < WIDTH-1; x++ ) {
             Bint = (int)(9*(int)B[x][y]-(int)B[x-1][y-1]-(int)B[x][y-1]-(int)B[x+1][y-1]-(int)B[x-1][y]-(int)B[x+1][y]-(int)B[x-1][y+1]-(int)B[x][y+1]-(int)B[x+1][y+1]);
             if (Bint < 0)
                {
                Bint = 0;
                }
             if (Bint>255)
                {
                Bint = 255;
                }
             tB[x][y]= (unsigned char)Bint;

             Rint = (int)(9*(int)R[x][y]-(int)R[x-1][y-1]-(int)R[x][y-1]-(int)R[x+1][y-1]-(int)R[x-1][y]-(int)R[x+1][y]-(int)R[x-1][y+1]-(int)R[x][y+1]-(int)R[x+1][y+1]);             
             if (Rint < 0)
                {
                Rint = 0;
                }
             if (Rint>255)
                {
                Rint = 255;
                }
             tR[x][y]= (unsigned char)Rint;

             Gint = (int)(9*(int)G[x][y]-(int)G[x-1][y-1]-(int)G[x][y-1]-(int)G[x+1][y-1]-(int)G[x-1][y]-(int)G[x+1][y]-(int)G[x-1][y+1]-(int)G[x][y+1]-(int)G[x+1][y+1]);
             if (Gint < 0)
                {
                Gint = 0;
                }
             if (Gint>255)
                {
                Gint = 255;
                }
             tG[x][y]= (unsigned char)Gint;
         }
     }
     for( y = 1; y < HEIGHT-1; y++ ) {
         for( x = 1; x < WIDTH-1; x++ ) {
         B[x][y]= tB[x][y];
	 R[x][y]= tR[x][y];
	 G[x][y]= tG[x][y];
	}
     }
}
//changes the hue

void Hue(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int degree)
{
int x,y, Bint, Rint, Gint;
float  alpha, beta, gamma;
alpha = (2*cos((degree*3.14159)/180)+1)/3;
beta = (1-cos((degree*3.14159)/180))/3 - (sin((degree*3.14159)/180))/sqrt(3);
gamma = (1-cos((degree*3.14159)/180))/3 + (sin((degree*3.14159)/180))/sqrt(3);

     for( y = 0; y < HEIGHT; y++ ) {
         for( x = 0; x < WIDTH; x++ ) {
             Bint = (int)(R[x][y]*alpha + G[x][y]*beta + B[x][y]*gamma+0.5);
             if (Bint < 0)
                {
                Bint = 0;
                }
             if (Bint>255)
                {
                Bint = 255;
                }

             Gint = (int)(R[x][y]*gamma + G[x][y]*alpha + B[x][y]*beta+0.5);
             if (Rint < 0)
                {
                Rint = 0;
                }
             if (Rint>255)
                {
                Rint = 255;
                }
             Rint = (int)(R[x][y]*beta + G[x][y]*gamma + B[x][y]*alpha+0.5);
             if (Gint < 0)
                {
                Gint = 0;
                }
             if (Gint>255)
                {
                Gint = 255;
                }
             G[x][y]= (unsigned char)Gint;
	     B[x][y]= (unsigned char)Bint;
	     R[x][y]= (unsigned char)Rint;
         }
     }
}

/* EOF */
