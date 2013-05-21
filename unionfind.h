/* 
 * File:   unionfind.h
 * Author: abhi
 *
 * Created on May 16, 2013, 10:31 PM
 */

#ifndef UNIONFIND_H
#define	UNIONFIND_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct LabelChild_t {
        int label;
        struct LabelChild_t* next;
    } LabelChild;
    
    typedef struct Labelset_t {
        int numLabels;
        int* parentSet; // Array of labels
        LabelChild** childrenSet; // Linked List of children
    } LabelSet;
    
    LabelSet createLabelSet(int size);
    void unionSet(LabelSet labelset, int label1, int label2 );
    int findSet(LabelSet labelset, int label);
    void printLabelSet(LabelSet labelSet);
    LabelSet getNonEmptyLabelSet(LabelSet initialLabelSet, int labelCount);
    LabelSet getInvertedNonEmptyLabelSet(LabelSet nonEmptyLabelSet, int initialLabelCount);
    int getIndexForValue(LabelSet labelSet, int value);

#ifdef	__cplusplus
}
#endif

#endif	/* UNIONFIND_H */

