/* 
 * File:   contour.h
 * Author: abhi
 *
 * Created on May 19, 2013, 11:02 PM
 */

#ifndef CONTOUR_H
#define	CONTOUR_H

#define MAX_CONTOUR_LEN 1500

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct PointSet_t {
        int numPoints;
        int* x;
        int* y;
    } PointSet;
    
    typedef struct ContourSet_t {
        int numCountours;
        PointSet* contour;
    } ContourSet;
    
    PointSet getComponentPoints(int** labelImg, int length, int width, int numComponents);
    int getLeftmostComponentPt(int** labelImg, int i, int xStart, int yStart);
    PointSet getContourInitPoint(PointSet initComponentPts, int** labelImg, int length, int width, int numComponents);
    ContourSet getContourSet(PointSet componentInitPoints, int** labelImg, int length, int width);
    void getContour(PointSet* componentContour, int initX, int initY, int maxContourLen, int** labelImg, int length, int width);
    
    void printPointSet(PointSet pointSet);
    void printContourSet(ContourSet contourSet);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* CONTOUR_H */

