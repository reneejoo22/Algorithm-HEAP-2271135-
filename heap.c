#include<stdio.h>
#include<stdlib.h>

#define MaxElement 200

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MaxElement];
	int HeapSize;
}HeapType;

HeapType* create() {	//heaptype만큼 동적 메모리 할당_삭제함수나 삽입함수 구현을 위해 필요

	return (HeapType*)malloc(sizeof(HeapType));
}

//HeapType heap;	//정적할당
HeapType* heap = create;	//동적할당

//최대 히프_insert 함수_업힙(자식노드->부모노드 비교해야해서)

//insert min heap 함수

//삭제함수(다운힙 부모노드->자식노드)

//delete min heap 함수