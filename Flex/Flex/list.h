/*
 *  list.h
 *  
 *
 *  Created by Miguel Fernandes on 02/04/2014.
 *	http://en.literateprograms.org/Singly_linked_list_(C)
 *
 */
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_s {
	void *data;
	struct node_s *next;	
} NODE;

NODE *list_create(void *data);
NODE *list_insert_after(NODE *node, void *data);
NODE *list_insert_beginning(NODE *list, void *data);
NODE *list_insert_sorted(NODE *list, void *data,int(*func)(void*,void*));
int list_remove(NODE *list, NODE *node);
int list_foreach(NODE *node, int(*func)(void*));
int list_foreach_file(NODE *node,FILE * file, int(*func)(void*,FILE*));
int list_foreach_global(NODE *node,NODE* list,char* title,int(*func)(void*,void*,char*));
int list_foreach_global_file(NODE *node,NODE* list,FILE* file, int(*func)(void*,void*,FILE*));
NODE *list_find(NODE *node, int(*func)(void*,void*), void *data);

#endif