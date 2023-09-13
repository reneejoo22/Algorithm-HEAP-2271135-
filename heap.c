#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct {
	int key;
}element;

typedef struct {
	int heap[MaxElement];
	int HeapSize;	//heap�� ��� ��Ұ� ����Ǿ��ִ���
}HeapType;

HeapType* create() {	//heaptype��ŭ ���� �޸� �Ҵ�(�����Լ��� �����Լ� ������ ���� �ʿ�)+ �ʱ�ȭ

	HeapType* heap= (HeapType*)malloc(sizeof(HeapType));
	
	if (heap == NULL) {
		printf("�޸𸮰� �Ҵ���� �ʾҽ��ϴ�");
		return heap;
	}

	heap->HeapSize = 0;
}

//HeapType heap;	//�����Ҵ�
//HeapType* heap = create;	//�����Ҵ�

void InsertMax(HeapType* h, int item) {	//�� ��� ����

	int where;	//���ο� ��带 ������ ��ġ
	where = ++(h->HeapSize);	//���� ������ �ڸ��� ����

	while ((where != 1) && (item > h->heap[where / 2])) {	//where�� 1�� �ƴϰ�(�� �ö� �� X) && �θ��庸�� Ŭ��

		h->heap[where] = h->heap[where / 2];	//�ڽ��� �θ��尡 �ִ� ������ �ö�
		where /= 2;		//������ҵ� ����
	}
	h->heap[where] = item;
}


void main() {

	int e1 = 10, e2 = 20, e3 = 30;

	HeapType* heap;

	heap = create();	//���� ���� �Ҵ�

	InsertMax(heap, e1); InsertMax(heap, e2); InsertMax(heap, e3);	//����
	/*
			30
		   /  \
		  10  20
	*/

	for (int num = 1; num <heap->HeapSize+1 ; num++) {

		printf("%d ", heap->heap[num]);
	}

	free(heap);

}
