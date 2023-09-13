#include<stdio.h>

#define MaxElement 200

typedef struct {
	int key;
}element;

typedef struct {
	element  heap[MaxElement];
	int HeapSize;
}HeapType;

HeapType heap;
//HeapType* heap = create;