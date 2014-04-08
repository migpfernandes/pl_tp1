//
//  Concepts.c
//  Flex
//
//  Created by Miguel Fernandes on 03/04/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concepts.h"


Concept initConcept(char *ID){
    Concept res = (void*) malloc(sizeof(ConceptN));
    res -> Id = strdup(ID);
    res -> prefLabel = "";
    res -> altLabel =list_create((void*) NULL);
    res -> relatedIDs =list_create((void*) NULL);
    res -> narrowerIDs =list_create((void*) NULL);
    res -> broaderIDs =list_create((void*) NULL);
    
    return res;
}

Global initGlobal(){
    Global res;
    res.title = "";
    res.data = "";
    res.concepts = NULL;
    res.topConcepts = NULL;

    return res;
}

int findID(void *concList, void *Id)
{
	return strcmp(((Concept) concList)->Id, (char*)Id)?0:1;
}

int fprintConceptList(void *s,FILE *file){
    if (s) {
        fprintf(file,"\t\t\t<li><a href=""concepts/%s.html"">%s</a></li>\n",
                ((Concept) s)->Id,((Concept) s)->prefLabel);
    }
    return 0;
}

int fprintRelationships(void *s,void* list,FILE *file){
    NODE* match;
    
    if ((s) && (match=list_find((NODE*) list,findID ,(char*) s))) {
        fprintf(file,"\t\t<li><a href=""%s.html"">%s</a></li>\n",
                (char *) s,((Concept)match->data)->prefLabel);
    }
    return 0;
}

int fprintTopConcepts(void *s,void* list,FILE *file){
    NODE* match;
    
    if ((s) && (match=list_find((NODE*) list,findID ,(char*) s))) {
        fprintf(file,"\t\t<li><a href=""concepts/%s.html"">%s</a></li>\n",
                (char *) s,((Concept)match->data)->prefLabel);
    }
    return 0;
}

int fprintAltLabel(void *s,void* list,FILE *file){
    if (s) {
        fprintf(file,"\t\t<li>%s</li>\n",(char *) s);
    }
    return 0;
}


int geraConceptPage(void* node,void* list,char* title){
    FILE *file;
    Concept c;
    
    if (!node) return -1;
    c =(Concept) node;
    
    char filename[250]="concepts/";
    
    strcat(filename,c->Id);
    strcat(filename,".html");
    
    file = fopen(filename,"w");
    
    char *htmltag = "<html xmlns:rdf=""http://www.w3.org/1999/02/22-rdf-syntax-ns#"" xmlns:rdfs=""http://www.w3.org/2000/01/rdf-schema#"" xmlns:skos=""http://www.w3.org/2004/02/skos/core#"" xmlns:dc=""http://purl.org/dc/elements/1.1/"">\n";
    fprintf(file,htmltag);
    
    char* head = "<head>\n    <meta http-equiv=""Content-Type"" content=""text/html; charset=Western (Windows 1252)"">\n    <title>%s :: Concept</title>\n</head>\n";
    fprintf(file,head,title);
    
    char *bodyh1 = "<body>\n\t<h1>%s :: Concept :: %s :: %s</h1>\n";
    fprintf(file,bodyh1,title,c->prefLabel,c->Id);
    
    char *bodyh2 = "\t<h2>%s</h2>\n";
    fprintf(file,bodyh2,c->prefLabel);
    
    if ((c->altLabel) && (c->altLabel->data)){
        fprintf(file, "\t<h3>Alternative definitions:</h3>\n");
        fprintf(file, "\t<ul>\n");
        list_foreach_global_file(c->altLabel,list,file, fprintAltLabel);
        fprintf(file, "\t</ul>\n");
    }
    
    if ((c->relatedIDs) && (c->relatedIDs->data)){
        fprintf(file, "\t<h3>Related to:</h3>\n");
        fprintf(file, "\t<ul>\n");
        list_foreach_global_file(c->relatedIDs,list,file, fprintRelationships);
        fprintf(file, "\t</ul>\n");
    }
    
    if ((c->narrowerIDs) && (c->narrowerIDs->data)){
        fprintf(file, "\t<h3>Narrowed to:</h3>\n");
        fprintf(file, "\t<ul>\n");
        list_foreach_global_file(c->narrowerIDs,list,file, fprintRelationships);
        fprintf(file, "\t</ul>\n");
    }

    if ((c->broaderIDs) && (c->broaderIDs->data)){
        fprintf(file, "\t<h3>Broader:</h3>\n");
        fprintf(file, "\t<ul>\n");
        list_foreach_global_file(c->broaderIDs,list,file, fprintRelationships);
        fprintf(file, "\t</ul>\n");
    }

    char *index = "\t<address>\n\t\t[<a href=""../index.html"">Main index</a>]\n\t</address>\n";
    fprintf(file,index);
    
    char *bodyend =  "</body>\n";
    fprintf(file,bodyend);
    
    char *htmlend = "</html>\n";
    fprintf(file,htmlend);
    
    fclose(file);
    return 0;
}

int geraIndex(Global global){
    FILE *file;
    file = fopen("index.html","w");
    
    char *htmltag = "<html xmlns:rdf=""http://www.w3.org/1999/02/22-rdf-syntax-ns#"" xmlns:rdfs=""http://www.w3.org/2000/01/rdf-schema#"" xmlns:skos=""http://www.w3.org/2004/02/skos/core#"" xmlns:dc=""http://purl.org/dc/elements/1.1/"">\n";
    fprintf(file,htmltag);
    
    char* head = "<head>\n    <meta http-equiv=""Content-Type"" content=""text/html; charset=Western (Windows 1252)"">\n    <title>%s</title>\n</head>\n";
    fprintf(file,head,global.title);
    
    
    char *bodyh1 = "<body>\n\t<h1>%s</h1>\n";
    fprintf(file,bodyh1,global.title);
    
    char *tablebegin = "<table width=""100%%"">\n\t<tr>\n\t\t<td width=""30%%"">\n\t\t<h3>Concept Index</h3>\n\t\t<ol>\n";
    fprintf(file,tablebegin);
    
    list_foreach_file(global.concepts,file, fprintConceptList);
    
    fprintf(file, "\t\t</ol>\n\t\t</td>\n\t\t<td width=""70%%"" valign=""top"">\n");
    
    if((global.topConcepts)&&(global.topConcepts->data)){
        fprintf(file, "\t\t<h3>Top Concepts</h3>\n<ul>\n");
        list_foreach_global_file(global.topConcepts,global.concepts,file, fprintTopConcepts);
        fprintf(file, "</ul>\n");
    }
    
    char *tableclose = "</tr>\n\t</table>\n";
    fprintf(file, tableclose);
    
    fprintf(file,"</body>\n</html>\n");
    
    fclose(file);
    return 0;
}

void geraPaginas(Global global){
    list_foreach_global(global.concepts,global.concepts,global.title,geraConceptPage);
    geraIndex(global);
}