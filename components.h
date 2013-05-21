/* 
 * File:   components.h
 * Author: abhi
 *
 * Created on April 26, 2013, 3:37 PM
 */

#ifndef COMPONENTS_H
#define	COMPONENTS_H

#include "unionfind.h"

#define MAX_COMPONENTS 20999

#ifdef	__cplusplus
extern "C" {
#endif
    
    void checkPrevNeighbours(short** image, int** imgLabel, int* minNeighbourLabel, int* similarNeighbourExists, int length, int width, int x, int y );
    void modifyPrevNeighbourLabels(short** image, int** imgLabel, LabelSet labelSet, int length, int width, int x, int y );
    int** labelComponents(short** image, int length, int width, int* numComponents, int* numActualComponents);


#ifdef	__cplusplus
}
#endif

#endif	/* COMPONENTS_H */

