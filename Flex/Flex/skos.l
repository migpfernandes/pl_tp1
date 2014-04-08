%{
#include "concepts.h"
#include "list.h"
Global global;
Concept conc;
%}
%x concept conceptScheme topConcept preflabel altlabel

TITLETAG	\<dc\:title\>.*\<\/dc\:title\>		
DATATAG		\<dc\:date\>.*\<\/dc\:date\>		
ATRIBUTE	\ [a-z]+\:[a-z]+\=\".*\"
PREFLABELBTAG	\<skos\:prefLabel{ATRIBUTE}*\>
PREFLABELETAG	\<\/skos\:prefLabel\>
ALTLABELBTAG	\<skos\:altLabel{ATRIBUTE}*\>
ALTLABELETAG	\<\/skos\:altLabel\>
CONCEPTETAG	\<\/skos\:Concept\>
BROADERTAG	\<skos\:broader\ rdf\:resource\=\".*\"\/\>
NARROWERTAG	\<skos\:narrower\ rdf\:resource\=\".*\"\/\>
RELATEDTAG	\<skos\:related\ rdf\:resource\=\".*\"\/\>

%%
	global = initGlobal();
\<skos\:ConceptScheme	{ BEGIN conceptScheme; }
\<skos\:Concept		{ conc = NULL; BEGIN concept; }

<conceptScheme>\<skos\:hasTopConcept	{BEGIN topConcept; }
<conceptScheme>"</skos:ConceptScheme>"	{BEGIN 0; }
<conceptScheme>{TITLETAG}			{
						global.title=strdup(yytext);
						global.title[strlen(global.title)-11] = '\0';
						global.title = global.title + 10;
					}
<conceptScheme>{DATATAG}			{
						global.data=strdup(yytext);
						global.data[strlen(global.data)-10] = '\0';
						global.data = global.data + 9;
					}

<topConcept>\".+\"			{
						char* id = strdup(yytext);
						id[strlen(id)-1] = '\0';
						id++;
						global.topConcepts = list_insert_beginning(global.topConcepts,id); 
					}
<topConcept>\/\>			{ BEGIN conceptScheme; }

<concept>rdf\:about\=\"[^\"]+\"		{ 
						char* id = strdup(yytext);
						id[strlen(id)-1] = '\0';
						id = id + 11;
						conc = initConcept(id); 
					}
<concept>{PREFLABELBTAG}		{ BEGIN preflabel; }
<concept>{ALTLABELBTAG}			{ BEGIN altlabel; }
<concept>{CONCEPTETAG}			{ global.concepts = addConcept(global.concepts,conc); }
<concept>{BROADERTAG}			{
						char *id = strdup(yytext);
						id[strlen(id)-3]='\0';
						id = id + 28;
						conc->broaderIDs= list_insert_beginning(conc->broaderIDs,id);
					}

<concept>{NARROWERTAG}			{
						char *id = strdup(yytext);
						id[strlen(id)-3]='\0';
						id = id + 29;
						conc->narrowerIDs= list_insert_beginning(conc->narrowerIDs,id);
					}

<concept>{RELATEDTAG}			{
						char *id = strdup(yytext);
						id[strlen(id)-3]='\0';
						id = id + 28;
						conc->relatedIDs= list_insert_beginning(conc->relatedIDs,id);
					}

<preflabel>{PREFLABELETAG}		{ BEGIN concept; }
<preflabel>[^\<]*			{ conc->prefLabel = strdup(yytext); }

<altlabel>{ALTLABELETAG}		{ BEGIN concept; }
<altlabel>[^\<]*			{ 
						char *alt = strdup(yytext);
						conc->altLabel = list_insert_beginning(conc->altLabel,alt); 
					}

<*>[\ \t\n]				;
<*>.					;
%%
int printstring(void *s)
{
	printf("%s\n", (char *)s);
	return 0;
}


int printIDs(void *s){
	printf("%s\n",((Concept) s)->Id);
	return 0;
}

int printprefLabels(void *s){
	printf("%s\n",((Concept) s)->prefLabel);
	return 0;
}

int printaltLabels(void *s){
	printf("%s\n",((Concept) s)->altLabel->data);
	return 0;
}

int printbroader(void *s){
	printf("%s\n",((Concept) s)->broaderIDs->data);
	return 0;
}

int printrelated(void *s){
	printf("%s\n",((Concept) s)->relatedIDs->data);
	return 0;
}

int printnarrower(void *s){
	printf("%s\n",((Concept) s)->narrowerIDs->data);
	return 0;
}

int yywrap(){
	//printf("Title: %s\n",global.title);
	//printf("Data: %s\n",global.data);
	//list_foreach(global.concepts,printIDs);
	//list_foreach(global.topConcepts, printstring);
	//list_foreach(global.concepts,printprefLabels);
	//list_foreach(global.concepts,printaltLabels);
	//list_foreach(global.concepts,printbroader);
	//list_foreach(global.concepts,printrelated);
	//list_foreach(global.concepts,printnarrower);

	geraPaginas(global);	
		
return 1;
}

