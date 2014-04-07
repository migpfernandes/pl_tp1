/*
 *  list.c
 *  
 *
 *  Created by Miguel Fernandes on 02/04/2014.
 *	http://en.literateprograms.org/Singly_linked_list_(C)
 *
 */
#include "list.h"

NODE *list_create(void *data)
{
	NODE *node;
	if(!(node=malloc(sizeof(NODE)))) return NULL;
	node->data=data;
	node->next=NULL;
	return node;
}

NODE *list_insert_after(NODE *node, void *data)
{
	NODE *newnode;
        newnode=list_create(data);
        newnode->next = node->next;
        node->next = newnode;
	return newnode;
}

NODE *list_insert_beginning(NODE *list, void *data)
{
	NODE *newnode;
        newnode=list_create(data);
        newnode->next = list;
	return newnode;
}

NODE *list_insert_sorted(NODE *node, void *data,int(*func)(void*,void*)){
    if(!node)
        return list_insert_beginning(node,data);
    else if (func(node->data,data) >= 0) {
        return list_insert_beginning(node,data);
    } else {
        node->next = list_insert_sorted(node->next,data,func);
        return node;
    }
}

int list_remove(NODE *list, NODE *node)
{
	while(list->next && list->next!=node) list=list->next;
	if(list->next) {
		list->next=node->next;
		free(node);
		return 0;		
	} else return -1;
}


int list_foreach(NODE *node, int(*func)(void*))
{
	while(node) {
		if(func(node->data)!=0) return -1;
		node=node->next;
	}
	return 0;
}

int list_foreach_file(NODE *node,FILE * file, int(*func)(void*,FILE*)){
	while(node) {
		if(func(node->data,file)!=0) return -1;
		node=node->next;
	}
	return 0;
}

int list_foreach_global(NODE *node,NODE* list,char* title,int(*func)(void*,void*,char*))
{
	while(node) {
		if(func(node->data,list,title)!=0) return -1;
		node=node->next;
	}
	return 0;
}

int list_foreach_global_file(NODE *node,NODE* list,FILE* file, int(*func)(void*,void*,FILE*))
{
	while(node) {
		if(func(node->data,list,file)!=0) return -1;
		node=node->next;
	}
	return 0;
}

NODE *list_find(NODE *node, int(*func)(void*,void*), void *data)
{
	while(node) {
		if(func(node->data, data)>0) return node;
		node=node->next;
	}
	return NULL;
}
