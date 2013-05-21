
#include "contour.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


PointSet getComponentPoints(int** labelImg, int length, int width, int numComponents) {
    /* returns atleast one point in each component */
    
    int x,y,pixelLabel;
    PointSet componentPts;
    
    // allocate
    componentPts.numPoints = numComponents; // includes background as label 0
    componentPts.x = (int*)malloc(componentPts.numPoints * sizeof(int));
    componentPts.y = (int*)malloc(componentPts.numPoints * sizeof(int));
    
    for (x = 0; x < length; x++) {
        for (y = 0; y < width; y++) {
            pixelLabel = labelImg[x][y];
            componentPts.x[pixelLabel] = x;
            componentPts.y[pixelLabel] = y;
        }
    }
    
    return componentPts;
    
}

int getLeftmostComponentPt(int** labelImg, int j, int xStart, int yStart) {
    /* returns yLeftmost for (xStart,yLeftmost) Point */
    
    int i, labelComponent;
    
    labelComponent = labelImg[xStart][yStart];
    
    for (i = yStart; i >= 0; i--) {
        if ( labelImg[xStart][i] != labelComponent ) {
            i++;
            break;
        }
    }
    
    return i;

}

PointSet getContourInitPoint(PointSet initComponentPts, int** labelImg, int length, int width, int numComponents) {
    /* gets single point on periphery of component */
    
    int i;
    PointSet peripheryPts;
    
    // allocate
    peripheryPts.numPoints = numComponents; // includes background as label 0
    peripheryPts.x = (int*)malloc(peripheryPts.numPoints * sizeof(int));
    peripheryPts.y = (int*)malloc(peripheryPts.numPoints * sizeof(int));
    
    // Label 0 = Background
    for (i = 1; i < numComponents; i++) {
        peripheryPts.x[i] = initComponentPts.x[i];
        peripheryPts.y[i] = getLeftmostComponentPt(labelImg, i, initComponentPts.x[i], initComponentPts.y[i]);
    }
    
    return peripheryPts;
    
}

ContourSet getContourSet(PointSet componentInitPoints, int** labelImg, int length, int width) {
    
    int i;
    ContourSet contourSet;
    
    // allocate
    contourSet.numCountours = componentInitPoints.numPoints; // includes background as label 0
    contourSet.contour = (PointSet*)malloc(contourSet.numCountours * sizeof(PointSet));
    
    // Label 0 = Background
    for (i = 1; i < contourSet.numCountours; i++) {
        // allocate
        contourSet.contour[i].numPoints = MAX_CONTOUR_LEN;
        contourSet.contour[i].x = (int*)malloc(contourSet.contour[i].numPoints * sizeof(int));
        contourSet.contour[i].y = (int*)malloc(contourSet.contour[i].numPoints * sizeof(int));
        
        // find contour
        if (( componentInitPoints.x[i] > 0 ) && ( componentInitPoints.y[i] > 0 )) {
                getContour(&contourSet.contour[i], componentInitPoints.x[i], componentInitPoints.y[i], MAX_CONTOUR_LEN, labelImg, length, width);
        }
    }
    
    return contourSet;

}

void getContour(PointSet* componentContour, int initX, int initY, int maxContourLen, int** labelImg, int length, int width) {
    
    int ptIndex, isIsolatedPoint, componentLabel, neighbourFound,
        currentDirectionIndex, currentPointX, currentPointY, 
        possibleDirectionIndex, possiblePointX, possiblePointY;
    
    // initialize direction vector
    int directionX[8] = {  0, -1, -1, -1, 0, 1, 1,  1 };
    int directionY[8] = { -1, -1,  0,  1, 1, 1, 0, -1 };
    
    //printf("Processing Contour starting with (%d, %d) ...\n", initX, initY);
    
/*
    if (( initX == 1645 ) && ( initY == 251 )) {
        printf("--Break--\n");
    }
*/
    
    ptIndex = -1;
    isIsolatedPoint = 0;
    componentLabel = labelImg[initX][initY];
    currentPointX = initX;
    currentPointY = initY;
    
/*
    // add initial points
    ptIndex++;
    componentContour->x[ptIndex] = initX;
    componentContour->y[ptIndex] = initX;
*/
    
    currentDirectionIndex = 3; // start from North-West direction, as initial Point is leftmost point along the horizontal line it lies in
    
    do {
        
        possibleDirectionIndex = ( currentDirectionIndex + 6 ) % 8; // start at clockwise right-angles to prev. dir.
        
        neighbourFound = 0;
        
        while ( possibleDirectionIndex != (( currentDirectionIndex + 5 ) % 8) ) {
            
            possiblePointX = currentPointX + directionX[possibleDirectionIndex];
            possiblePointY = currentPointY + directionY[possibleDirectionIndex];
            
            //printf("Possible Point (%d, %d) has label %d ...\n", possiblePointX, possiblePointY, labelImg[possiblePointX][possiblePointY] );
            
            if ( labelImg[possiblePointX][possiblePointY] == componentLabel ) {
                // add point
                ptIndex++;
                componentContour->x[ptIndex] = possiblePointX;
                componentContour->y[ptIndex] = possiblePointY;
                
                // update current Point
                neighbourFound = 1;
                currentPointX = possiblePointX;
                currentPointY = possiblePointY;
                
                //printf("Point (%d, %d) found...\n", currentPointX, currentPointY );
                
                break;
            }
            
            // increment direction
            possibleDirectionIndex = ( possibleDirectionIndex + 1 ) % 8;
            
        }
        
        if (!neighbourFound) {
            isIsolatedPoint = 1;
        }
        
        // update direction
        currentDirectionIndex = possibleDirectionIndex;
        
    } while ( (( currentPointX != initX ) || ( currentPointY != initY )) && !isIsolatedPoint  && (ptIndex < (maxContourLen-1)) ) ; // && (ptIndex < (maxContourLen-1)) ); // && !isIsolatedPoint && (ptIndex < (maxContourLen-1)) );
    
    if (!isIsolatedPoint) {
        componentContour->numPoints = ptIndex+1 /*- 1*/; // exclude last added init Point
    } else {
        componentContour->numPoints = 1;
    }
    
    return;
    
}

void printPointSet(PointSet pointSet) {
    
    int i;
    
    for (i = 0; i < pointSet.numPoints; i++) {
        printf("%d -> (%d, %d)\n", i, pointSet.x[i], pointSet.y[i]);
    }
    
    return;
    
}

void printContourSet(ContourSet contourSet) {
    
    int i,j;
    
    printf("Contours : \n\n");
    
    for (i = 0; i < contourSet.numCountours; i++) {
        printf("Component %d : ", i);
        for (j = 0; j < contourSet.contour[i].numPoints; j++) {
            printf("(%d,%d) ", contourSet.contour[i].x[j], contourSet.contour[i].y[j] );
        }
        printf("\n");
    }
    
    return;
}