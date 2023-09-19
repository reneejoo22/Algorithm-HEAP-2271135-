#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct {
	int key;	//������ ����
}element;

typedef struct {
	element heap[MaxElement];	//��ġ   
	int HeapSize;	//heap�� ��� ��Ұ� ����Ǿ��ִ���
}HeapType;


HeapType* create() {	//heaptype��ŭ ���� �޸� �Ҵ�(�����Լ��� �����Լ� ������ ���� �ʿ�)+ �ʱ�ȭ

	HeapType* heap= (HeapType*)malloc(sizeof(HeapType));
	
	if (heap == NULL) {
		printf("�޸𸮰� �Ҵ���� �ʾҽ��ϴ�");
		return heap;
	}

	heap->HeapSize = 0;

	return heap;
}



void InsertMax(HeapType* h, element item) {	//�� ��� ����_��

	int where;	//���ο� ��带 ������ ��ġ
	where = ++(h->HeapSize);	//���� ������ �ڸ��� ����

	while ((where != 1) && (item.key > h->heap[where / 2].key)) {	//where�� 1�� �ƴϰ�(�� �ö� �� X) && �θ��庸�� Ŭ��

		h->heap[where] = h->heap[where / 2];	//�ڽ��� �θ��尡 �ִ� ������ �ö�
		where /= 2;		//������ҵ� ����
	}
	h->heap[where] = item;
}


element DeleteMax(HeapType* h) {	//�����Լ�_�θ���Ű��>�ڽĳ��Ű��

	int parent, kid;	//�θ���� �ڽĳ���� ��ġ
	element item, tmp;

	item = h->heap[1];	//������ ��Ʈ ���� Ű���� item�� ����
	tmp = h->heap[(h->HeapSize)--];	//���� ����� Ű�� ����

	parent = 1;	//�� ���� ��ġ
	kid = 2;	// �׾Ʒ� ���� ��ġ

	while (kid <= h->HeapSize) {	//�ڽ��� ������ ���� �ȿ� �ִ� ���ȸ�

		/*
		��Ʈ ���� �ڽ� ��带 ��
		1. [ù��° if��] ����, ���� �� ���� �� �߸���(�� �� �ϳ� ����, ���� ���� ū �ַ�)
		2. [�ι�° if��] �� ���� ���� �ڽ��� Ű���� ��Ʈ����� Ű �� ��. �θ�>�ڽ� �����ϸ� ���߰� �ƴϸ�

		�θ�<�ڽ��̴�
		�ڽ��� Ű���� �θ� ��ġ�������� �����+ ����Ű�� ��ġ�� �Ʒ��� ������
		*/

		if ((kid < h->HeapSize) && (h->heap[kid].key) < (h->heap[kid + 1].key))	// ����< ���� 
			kid++;	//�� �ڽ��� ��ġ�� �ٲ�
		if (tmp.key >= h->heap[kid].key)break;	//���� ���>= �ڽ�Ű��_ ������, ����

		h->heap[parent] = h->heap[kid];	//if�� �Ѵ� ���� �ʾƼ� ����� ���, �Ʒ����� ���� ������ �ѱ�
		parent = kid;	//���������� ���� �Ѿ�� ���� �� ��� �ݺ��ؾ���. �Ʒ��� ���������ϴ� parent���� ������ ������� ��ġ���� �Ѱ���
		kid *= 2;	//Ű��� ���� �䷱Ʈ�� �ٷ� �Ʒ��� ���������ϴ� *2 ����
	}

	h->heap[parent] = tmp;	//���� �ڸ��� �־���
	return item;
}

void PrintHeap(HeapType* h) {

	for (int num = 1; num < h->HeapSize + 1; num++) {

		printf("%d ", h->heap[num].key);
	}
	printf("\n");
}

void main() {

	element e1 = { 10 }, e2 = { 20 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType* heap;

	heap = create();	//���� ���� �Ҵ�� �ʱ�ȭ

	InsertMax(heap, e1); InsertMax(heap, e2); InsertMax(heap, e3);	//heap �ϳ��� ������Ʈ�� ���� �ֱ�
	/*
			30
		   /  \
		  10  20
	*/
	printf("������ ����\n");
	PrintHeap(heap);
	

	printf("���� ��\n");
	e4 = DeleteMax(heap);	//heap�� ������ ���� e4�� ����
	printf("%d ", e4.key);

	e5 = DeleteMax(heap);	//heap�� ������ ���� e4�� ����
	printf("%d ", e5.key);

	e6 = DeleteMax(heap);	//heap�� ������ ���� e4�� ����
	printf("%d ", e6.key);
		
	free(heap);

}
