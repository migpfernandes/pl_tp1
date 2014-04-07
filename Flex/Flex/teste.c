#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "concepts.h"

int printstring(void *s)
{
	printf("%s\n", (char *)s);
	return 0;
}

int findstring(void *listdata, void *searchdata)
{
	return strcmp((char*)listdata, (char*)searchdata)?0:1;
}

int main2(){
    
    Global glb = initGlobal();
    
    Concept res = initConcept("teste");
    res->prefLabel="Teste de qq coisa";
    list_insert_beginning(res->altLabel, "afinal é qq coisa e tal");
    
    glb.concepts = list_insert_beginning(glb.concepts, res);
    glb.title="ACM COISE";
    

    geraPaginas(glb);
    
    return 0;
}

int main3()
{
	NODE *list, *second, *inserted;
	NODE *match;

	/* Create initial elements of list */
	list=list_create((void*)"First");
	second=list_insert_after(list, (void*)"Second");
	list_insert_after(second, (void*)"Third");

	printf("Initial list:\n");
	list_foreach(list, printstring);
	putchar('\n');

	/* Insert 1 extra element in front */
	list=list_insert_beginning(list, "BeforeFirst");
	printf("After list_insert_beginning():\n");
	list_foreach(list, printstring);
	putchar('\n');

	/* Insert 1 extra element after second */
	inserted=list_insert_after(second, "AfterSecond");
	printf("After list_insert_after():\n");
	list_foreach(list, printstring);
	putchar('\n');

	/* Remove the element */
	list_remove(list, inserted);
	printf("After list_remove():\n");
	list_foreach(list, printstring);
	putchar('\n');

	/* Search */
	if((match=list_find(list, findstring, "Third")))
		printf("Found \"Third\"\n");
	else printf("Did not find \"Third\"\n");

    return 0;
}

int charInsertCompare(void* s1,void* s2){
    //printf("String1: %s\n",(char*)s1);
    //printf("String2: %s\n",(char*)s2);
    
    //printf("STRCMP: %d\n",strcmp((char *) s1, (char*)s2));
    
    return strcmp((char *) s1, (char*)s2);
}

int main()
{
	NODE *list;
    
	/* Create initial elements of list */
	list=list_create((void*)"DSET");
    list=list_insert_sorted(list, "GSET", charInsertCompare);
    list=list_insert_sorted(list, "ESET", charInsertCompare);
    list=list_insert_sorted(list, "CSET", charInsertCompare);
	   
	list_foreach(list, printstring);
	putchar('\n');
    
}