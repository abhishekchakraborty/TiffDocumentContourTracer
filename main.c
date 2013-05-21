/* 
 * File:   main.c
 * Author: abhi
 *
 * Created on April 10, 2013, 11:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components.h"
#include "contour.h"
#define MAX_SIZE 100
#define PI 3.142

/*
#define THRESH_VAL 220
*/
#define THRESH_VAL 128

/*
 * 
 */
short **binarization(short **image, int length, int width);
void write_file(char *out_name,short **b,int length, int width);
void writeComponents(char* fileName, int** img, int length, int width);
void writeComponentsWithInitialPts(char* fileName, int** img, PointSet contourPts, int length, int width);
void writeContourPts(char* fileName, int** img, ContourSet contourPts, int length, int width);
void printArr(int** bin, int length, int width, FILE* writeFile);
void freeImg(short** image, int length, int width);

/*
int houghTransform(short **image, int length, int width, int skewRange, int skewStep);
int chooseSkew(int** accumulator, int skewRange, int skewStep, int maxSide );
*/

int main(int argc, char** argv) {
    
    char tmpStr[MAX_SIZE];
    int length,width;
    int skew,numComponents, numActualComponents;
    short **gray,**bin;
    int **components;
    FILE *wFile, *wFile2;
    PointSet componentPts, contourInitPts;
    ContourSet contourSet;
    
    wFile = (FILE*)fopen(argv[3],"w");
    
    gray = (short**)read_tiff_image(argv[1],&length,&width);
    printf("Length = %d \n",length);
    printf("Width = %d \n",width);    
    bin = binarization( gray, length, width);
    //freeImg(gray, length, width);
    
/*
    skew = houghTransform(bin, length, width, 30, 1);
    printf("Skew detected = %d \n", skew);
*/
    components = labelComponents(bin, length, width, &numComponents, &numActualComponents);
    
    componentPts = getComponentPoints(components, length, width, numComponents);
    contourInitPts = getContourInitPoint(componentPts, components, length, width, numActualComponents);
    //printPointSet(contourInitPts);
    
    contourSet = getContourSet(contourInitPts, components, length, width);
    
    //write_file(argv[2],components,length,width);
    //writeComponents(argv[2],components,length,width);
    writeComponentsWithInitialPts(argv[2],components,contourInitPts,length,width);
    
    //printContourSet(contourSet);
    //writeContourPts(argv[2],components,contourSet,length,width);
    
    printArr(components, length, width, wFile);
    
    fclose(wFile);
    
    return (EXIT_SUCCESS);
}


short **binarization(short **image, int length, int width)
{

    int i,j,thresh_value;
    short  **binary, pixelVal;
    
    binary=(short**)malloc(length*sizeof(short*));

    for(i=0;i<length;i++)
        binary[i]=(short*)malloc(width*sizeof(short));
    
    thresh_value= THRESH_VAL; // thres_val_finding(length,width, image) ;
    
    for(i=0;i<length;i++)
    {
        for(j=0;j<width;j++)
        {
            
            pixelVal = image[i][j];

            if(image[i][j]>=0 && image[i][j]< thresh_value)
                binary[i][j]=1;
            else
                binary[i][j]=0;

        }
    }

    return binary;

}

void write_file(char *out_name,short **b,int length, int width)
{

    int k, r;

    for (k = 0; k < length; k++)
        for (r = 0; r < width; r++)
            if (b[k][r] == 0)
                b[k][r] = 255;
            else
                b[k][r] = 0;

    create_file_if_needed(out_name, b, length, width);

    for (k = 0; k < length; k++)
        for (r = 0; r < width; r++) {
            
            if (b[k][r] == 0)
                b[k][r] = 1;
            else
                b[k][r] = 0;

        }

}

void writeComponents(char* fileName, int** img, int length, int width) {
    /*
     * Create Image with Components in different shades
     */
    
    int i,j;
    short **binImg;
    
    // create binary image
    binImg = (short**)malloc(length * sizeof(short*));
    for (i = 0; i < length; i++) {
        binImg[i] = (short*)malloc(width * sizeof(short));
    }

    // write
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            // make binary
            if ( img[i][j] == 0 ) {
                binImg[i][j] = 255;
            } else {
                binImg[i][j] = img[i][j];
            }
        }
    }
    
    create_file_if_needed(fileName, binImg, length, width);
    
    // de-allocate
    for (i = 0; i < length; i++) {
        free(binImg[i]);
    }
    free(binImg);
    
    return;
}

void writeComponentsWithInitialPts(char* fileName, int** img, PointSet contourPts, int length, int width) {
    /*
     * Create Image with Components in different shades and Initial Points
     */
    
    int i,j;
    short **binImg;
    
    // create binary image
    binImg = (short**)malloc(length * sizeof(short*));
    for (i = 0; i < length; i++) {
        binImg[i] = (short*)malloc(width * sizeof(short));
    }

    // write
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            // make binary
            if ( img[i][j] == 0 ) {
                binImg[i][j] = 255;
            } else {
                binImg[i][j] = img[i][j];
            }
        }
    }
    
    // mark contour Points
    for (i = 0; i < contourPts.numPoints; i++) {
        binImg[contourPts.x[i]][contourPts.y[i]] = 0;
    }
    
    create_file_if_needed(fileName, binImg, length, width);
    
    // de-allocate
    for (i = 0; i < length; i++) {
        free(binImg[i]);
    }
    free(binImg);
    
    return;
}

void writeContourPts(char* fileName, int** img, ContourSet contourPts, int length, int width) {
    /*
     * Create Image with only Contour Points
     */
    
    int i,j;
    short **binImg;
    
    // create binary image
    binImg = (short**)malloc(length * sizeof(short*));
    for (i = 0; i < length; i++) {
        binImg[i] = (short*)malloc(width * sizeof(short));
    }

    // write
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            // make binary
            binImg[i][j] = 255;
/*
            if ( img[i][j] == 0 ) {
                binImg[i][j] = 255;
            } else {
                binImg[i][j] = img[i][j];
            }
*/
        }
    }
    
    // mark contour Points
    for (i = 0; i < contourPts.numCountours; i++) {
        for (j = 0; j < contourPts.contour[i].numPoints; j++) {
            binImg[contourPts.contour[i].x[j]][contourPts.contour[i].y[j]] = 0;
        }
    }
    
    create_file_if_needed(fileName, binImg, length, width);
    
    // de-allocate
    for (i = 0; i < length; i++) {
        free(binImg[i]);
    }
    free(binImg);
    
    return;
}

void printArr(int** bin, int length, int width, FILE* writeFile) {
    
    int i,j;
    
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            fprintf(writeFile, "%d ", bin[i][j]);
        }
        fprintf(writeFile, "\n");
    }
    
    return;
    
}

void freeImg(short** image, int length, int width) {
    
    int i;
    for (i = 0; i < length; i++) {
        free(image[i]);
    }
    free(image);
    
    return;

}


/*
int houghTransform(short **image, int length, int width, int skewRange, int skewStep) {
    
    int x,y,rho,theta,maxSide;
    int** accumulator;
    
    maxSide = ( length > width ) ? length : width;
    
    accumulator = (int**)malloc( (2*skewRange/skewStep + 1) * sizeof(int*) );

    for (x = 0; x < (2*skewRange/skewStep + 1); x++) {
        accumulator[x] = (int*)calloc( (2*maxSide/2 + 1) , sizeof(int) );
    }
    
    for (y = 0; y < length; y++) {
        for (x = 0; x < width; x++) {
            if (image[y][x] == 1) {
                
                // 90 - skewRange < actual theta < 90 + skewRange
                for (theta = 0; theta < (2*skewRange + 1); theta = theta + skewStep) {

                    rho = x * cos(PI/180 * (theta + (90 - skewRange)) ) + y * sin(PI/180 * (theta + (90 - skewRange)) );
                    // -maxSide < rho < maxSide
                    ++accumulator[theta/skewStep][rho];

                }
            }
        }
    }
    
    return chooseSkew(accumulator, skewRange, skewStep, maxSide);
    
}

int chooseSkew(int** accumulator, int skewRange, int skewStep, int maxSide ) {
    
    int theta,rho, sum, sumSquared, variance, maxVariance, maxVarThetaIndex;
    // allocate for variance
    // double* variance = (double*)malloc((2*skewRange/skewStep + 1) * sizeof(double));
    maxVariance = 0;
    maxVarThetaIndex = -1;
    
    for (theta = 0; theta < (2*skewRange/skewStep + 1); theta++) {
        sum = 0;
        sumSquared = 0;
        for (rho = 0; rho < (2*maxSide/2 + 1); rho++) {
            sum += accumulator[theta][rho];
            sumSquared += accumulator[theta][rho]*accumulator[theta][rho];
        }
        
        variance = (sumSquared - sum)*1.0/(2*maxSide/2 + 1);
        
        if (variance > maxVariance) {
            maxVariance = variance;
            maxVarThetaIndex = theta;
        }
        
    }
    
    // adjust for step and offset
    return (-1*skewRange + maxVarThetaIndex*skewStep );
    
}
*/