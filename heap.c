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

HeapType* create() {	//heaptype��ŭ ���� �޸� �Ҵ�_�����Լ��� �����Լ� ������ ���� �ʿ�

	return (HeapType*)malloc(sizeof(HeapType));
}

//HeapType heap;	//�����Ҵ�
HeapType* heap = create;	//�����Ҵ�

//�ִ� ����_insert �Լ�_����(�ڽĳ��->�θ��� ���ؾ��ؼ�)

//insert min heap �Լ�

//�����Լ�(�ٿ��� �θ���->�ڽĳ��)

//delete min heap �Լ�