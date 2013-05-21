
#include "components.h"
#include <stdlib.h>
#include <stdio.h>


void checkPrevNeighbours(short** image, int** imgLabel, int* minNeighbourLabel, int* similarNeighbourExists, int length, int width, int x, int y ) {
    
    int i,j,neighbourLabel;
    
    // initialize
    *similarNeighbourExists = 0;
    *minNeighbourLabel = MAX_COMPONENTS + 1;
    
    //printf("checkPrevNeighbours: Pixel (%d, %d)\n",x,y);
    
    for (i = -1; i <= 0; i++) {
        for (j = -1; j <= 1; j++) {
            
            // skip last iteration and pixel itself
            if (( i == 0 && j == 1 ) || ( i == 0 && j == 0 )) {
                continue;
            }

            // check for boundaries
            if (( (x+i) >= 0 ) && ( (x+i) < length ) && ( (y+j) >= 0 ) && ( (y+j) < width )) {
                
                // check if neighbour is foreground pixel
                if ( image[x+i][y+j] == image[x][y] ) {
                    *similarNeighbourExists = 1;
                    
                    // get neighbour label
                    neighbourLabel = imgLabel[x+i][y+j];
                    
                    // get min. label among foreground neighbours
                    if ( neighbourLabel < *minNeighbourLabel ) {
                        *minNeighbourLabel = neighbourLabel;
                    }
                }                

            }
            
        }
    }

    return;
    
}

void modifyPrevNeighbourLabels(short** image, int** imgLabel, LabelSet labelSet, int length, int width, int x, int y ) {
    
    int i,j,neighbourLabel,prevLabel;
    
    // initialize
    prevLabel = -1;
    
    //printf("modifyPrevNeighbourLabels: Pixel (%d, %d) being processed...\n",x,y);    
    
    for (i = -1; i <= 0; i++) {
        for (j = -1; j <= 1; j++) {
            
            // skip last iteration and pixel itself
            if (( i == 0 && j == 1 ) || ( i == 0 && j == 0 )) {
                continue;
            }
            
            // check for boundaries
            if (( (x+i) >= 0 ) && ( (x+i) < length ) && ( (y+j) >= 0 ) && ( (y+j) < width )) {
                
                // check if neighbour is foreground pixel
                if ( image[x+i][y+j] == image[x][y] ) {
                    
                    neighbourLabel = imgLabel[x+i][y+j];
                    
                    if ( neighbourLabel == 0 ) {
                        printf("--Break-- Found a foreground neighbour (%d, %d) with label 0 \n",(x+i),(y+j));
                    }
                    
                    if ( prevLabel != -1 ) {
                        
                        unionSet(labelSet, prevLabel, neighbourLabel);
                    }
                    
                    prevLabel = neighbourLabel;
                    
                }
                
            }
            
        }
    }
    
    return;
    
}

int** labelComponents(short** image, int length, int width, int* numComponents, int* numActualComponents) {
    
    int x,y,minNeighbourLabel,similarNeighbourExists,tmpLabel;
    int **imgLabel,labelCount;
    LabelSet labelSet, nonEmptyLabelSet, invertedNonEmptyLabelSet;
    
    // initialize Labels with background (0)
    imgLabel=(int**)malloc(length*sizeof(int*));
    for (x = 0; x < length; x++) {
        imgLabel[x] = (int*)malloc(width*sizeof(int));
        for (y = 0; y < width; y++) {
            imgLabel[x][y] = 0;
        }
    }
    
    // get Label Set
    labelSet = createLabelSet(MAX_COMPONENTS+1);
    //printLabelSet(labelSet);
    
    //initialization
    labelCount = 0;
    
    // 1st pass
    for (x = 0; x < length; x++) {
        for (y = 0; y < width; y++) {
            
/*
            if ( x==1 && y==5 ) {
                printf("--Break--\n");
                printLabelSet(labelSet);
            }
*/
            
/*
            printf("Pixel (%d, %d) being processed...\n",x,y);
*/
            // check if foreground pixel
            if ( image[x][y] == 1 ) {
                
                // check if neighbour with same pixel value exists
                checkPrevNeighbours(image, imgLabel, &minNeighbourLabel, &similarNeighbourExists, length, width, x, y);

                if ( similarNeighbourExists == 0 ) {
                    //printf("For Pixel (%d, %d), no similar neighbour found...\n",x,y);
                    // increment Label Count
                    labelCount++;
                    // assign Label
                    imgLabel[x][y] = labelCount;
                    
                } else {
                    //printf("For Pixel (%d, %d), similar neighbour found...\n",x,y);
                    // assign smallest neighbour label
                    imgLabel[x][y] = minNeighbourLabel;
                    // perform union of neighbour labels
                    modifyPrevNeighbourLabels(image, imgLabel, labelSet, length, width, x, y);
                    //printLabelSet(labelSet);
                }
                
            }
            
        }
        //printLabelSet(labelSet);
/*
        printf("Current Label Count = %d \n",labelCount);
*/
    }
    
    *numComponents = labelCount; // Note: includes Background as label 0 too
    
/*
    printLabelSet(labelSet);
    printf("Current Label Count = %d \n",labelCount);
*/
    
    // 2nd pass
    for (x = 0; x < length; x++) {
        for (y = 0; y < width; y++) {
            imgLabel[x][y] = findSet(labelSet, imgLabel[x][y]);
        }
    }
    
    // get Non-empty Labels
    nonEmptyLabelSet = getNonEmptyLabelSet(labelSet, labelCount);
    
    *numActualComponents = nonEmptyLabelSet.numLabels;
    
/*
    printLabelSet(nonEmptyLabelSet);
    printf("Non-Empty Label Count = %d \n",nonEmptyLabelSet.numLabels);
*/
    
    // get inverted Label Set
/*
    invertedNonEmptyLabelSet = getInvertedNonEmptyLabelSet(nonEmptyLabelSet, labelCount);
    printLabelSet(invertedNonEmptyLabelSet);
*/
    
    // 3rd pass - to assign re-mapped low-value labels
    for (x = 0; x < length; x++) {
        for (y = 0; y < width; y++) {
            imgLabel[x][y] = getIndexForValue(nonEmptyLabelSet, imgLabel[x][y]);
/*
            if ( imgLabel[x][y] > 0 ) {
                tmpLabel = (int)imgLabel[x][y];
                imgLabel[x][y] = invertedNonEmptyLabelSet.parentSet[tmpLabel];
            }
*/
        }
    }
    
    return imgLabel;
    
}
