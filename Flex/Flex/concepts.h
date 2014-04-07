/*
 *  concepts.h
 *  
 *
 *  Created by Miguel Fernandes on 02/04/2014.
 *
 */


#ifndef CONCEPTS_H
#define CONCEPTS_H

#include "list.h"

typedef struct concept_s {
    char* Id;
    char* prefLabel;
    NODE *altLabel;
    NODE *relatedIDs;
    NODE *narrowerIDs;
    NODE *broaderIDs;
} *Concept,ConceptN;

typedef struct sGlobal {
    char* title;
    char* data;
    NODE *topConcepts;
    NODE *concepts;
} Global;

Concept initConcept(char *ID);
Global initGlobal();

void geraPaginas(Global global);
    
#endif
