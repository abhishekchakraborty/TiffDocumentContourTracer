
#include <stdio.h>
#include <stdlib.h>
#include "unionfind.h"


LabelSet createLabelSet(int size) {
    
    int i,j, *newSet;
    LabelSet labelSet, **tmp;
    
    labelSet.numLabels = size;
    
    labelSet.parentSet = (int*)malloc(labelSet.numLabels * sizeof(int));
    // initialize all element as belonging to singleton sets
    for (i = 0; i < labelSet.numLabels; i++) {
        labelSet.parentSet[i] = i;
        //newSet[i] = i; This crashed the malloc in the new line !!!! I hav no idea HOW !!
    }
    
    labelSet.childrenSet = (LabelChild**)malloc(size * sizeof(LabelChild*));
    // initialize with only themselves as children
    for (i = 0; i < labelSet.numLabels; i++) {
        labelSet.childrenSet[i] = (LabelChild*)malloc(sizeof(LabelChild));
        labelSet.childrenSet[i]->label = i; // child label
        labelSet.childrenSet[i]->next = NULL; // for last child
    }

    return labelSet;
    
}

void unionSet(LabelSet labelSet, int label1, int label2 ){
    
    int root1, root2, maxRoot, minRoot;
    LabelChild *maxRootFirstChild, *minRootFirstChild, *minRootLastChild;
    
    // check if arguments are same
    if ( label1 == label2 ) {
        return;
    }
    
    
/*
    if (( label1 == 0  && label2 == 2 ) || ( label1 == 2  && label2 == 0 )) {
        printf("--Break--\n");
        printLabelSet(labelSet);
    }
*/
    
    // get roots
    root1 = labelSet.parentSet[label1];
    root2 = labelSet.parentSet[label2];
    
    // check if both already have same parent
    if ( root1 == root2 ) {
        return;
    }
    
    if ( root1 < root2 ) {
        minRoot = root1;
        maxRoot = root2;
    } else {
        minRoot = root2;
        maxRoot = root1;
    }
    
    // for maxRoot children set, set parent to minRoot
    if ( labelSet.childrenSet[maxRoot] != NULL ) {
        for (maxRootFirstChild = labelSet.childrenSet[maxRoot]; maxRootFirstChild != NULL; maxRootFirstChild=maxRootFirstChild->next) {
            labelSet.parentSet[maxRootFirstChild->label] = minRoot;
        }
    }
    
    // combine sets of max root with min
    minRootFirstChild = labelSet.childrenSet[minRoot];
    minRootLastChild = minRootFirstChild;
    //minRootLastChild = maxRootFirstChild;
    while ( minRootLastChild->next != NULL ) {
        minRootLastChild = minRootLastChild->next;
    }
    
    maxRootFirstChild = labelSet.childrenSet[maxRoot];
    labelSet.childrenSet[maxRoot] = NULL;
    
    minRootLastChild->next = maxRootFirstChild;
    
    return;
    
}

int findSet(LabelSet labelSet, int label) {
    
    return labelSet.parentSet[label];
    
}

void printLabelSet(LabelSet labelSet) {
    
    int i;
    LabelChild* tmpNode;
    
    if (labelSet.childrenSet != NULL) {
        for (i = 0; i < labelSet.numLabels; i++) {
            printf("%d -> %d : ",i, labelSet.parentSet[i] );
            for (tmpNode = labelSet.childrenSet[i]; tmpNode != NULL; tmpNode=tmpNode->next) {
                printf("%d ",tmpNode->label);
            }
            printf("\n");
        }
        printf("\n");
    } else {
        for (i = 0; i < labelSet.numLabels; i++) {
            printf("%d -> %d",i, labelSet.parentSet[i] );
            printf("\n");
        }
        printf("\n");
    }
    
    return;

}

LabelSet getNonEmptyLabelSet(LabelSet initialLabelSet, int labelCount) {
    
    int i, nonEmptyLabelCount;
    LabelSet nonEmptyLabelSet;
    
    nonEmptyLabelSet.parentSet = (int*)malloc(initialLabelSet.numLabels * sizeof(int));
    nonEmptyLabelCount = 0;
    
    for (i = 0; i < (labelCount+1); i++) { // as Label 0 = background
        if ( initialLabelSet.childrenSet[i] != NULL ) {
            nonEmptyLabelSet.parentSet[nonEmptyLabelCount] = i;
            // increment non-empty label count
            nonEmptyLabelCount++;
        }
    }
    
    // set size of non-empty label set
    nonEmptyLabelSet.numLabels = nonEmptyLabelCount; // Note: includes Background as label 0 too
    
/*
 * Causes garbage value in nonEmptyLabelSet.parentSet[277]
    // reduce to actual size
    nonEmptyLabelSet.parentSet = (int*)realloc(nonEmptyLabelSet.parentSet, nonEmptyLabelCount);
*/
    
    // Children set is not used
    nonEmptyLabelSet.childrenSet = NULL;
    
    return nonEmptyLabelSet;
    
}

LabelSet getInvertedNonEmptyLabelSet(LabelSet nonEmptyLabelSet, int initialLabelCount) {
    
    int i, tmpVal;
    LabelSet invertedLabelSet;
    
    // set size
    invertedLabelSet.numLabels = initialLabelCount+1; // 0 = background
    
    // allocate
    invertedLabelSet.parentSet = (int*)malloc( invertedLabelSet.numLabels * sizeof(int));
    
    // initialize to invalid index
    for (i = 0; i < invertedLabelSet.numLabels; i++) {
        invertedLabelSet.parentSet[i] = -1;
    }
    
    // set the inverted indices as per non-empty label set
    for (i = 0; i < nonEmptyLabelSet.numLabels; i++) {
        tmpVal = nonEmptyLabelSet.parentSet[i];
        invertedLabelSet.parentSet[tmpVal] = i;
    }
    
    // Children set is not used
    invertedLabelSet.childrenSet = NULL;
    
    return invertedLabelSet;
    
}

int getIndexForValue(LabelSet labelSet, int value) {
    
    int i, indexVal;
    
    indexVal = -1;
    
    for (i = 0; i < labelSet.numLabels; i++) {
        if ( labelSet.parentSet[i] == value ) {
            indexVal = i;
        }
    }
    
    return indexVal;

}