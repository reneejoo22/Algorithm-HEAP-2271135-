#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct {
	int key;
}element;

typedef struct {
	int heap[MaxElement];
	int HeapSize;	//heap에 몇개의 요소가 저장되어있는지
}HeapType;

HeapType* create() {	//heaptype만큼 동적 메모리 할당(삭제함수나 삽입함수 구현을 위해 필요)+ 초기화

	HeapType* heap= (HeapType*)malloc(sizeof(HeapType));
	
	if (heap == NULL) {
		printf("메모리가 할당되지 않았습니다");
		return heap;
	}

	heap->HeapSize = 0;
}

//HeapType heap;	//정적할당
//HeapType* heap = create;	//동적할당

void InsertMax(HeapType* h, int item) {	//새 노드 저장

	int where;	//새로운 노드를 저장할 위치
	where = ++(h->HeapSize);	//가장 마지막 자리에 저장

	while ((where != 1) && (item > h->heap[where / 2])) {	//where가 1이 아니고(더 올라갈 곳 X) && 부모노드보다 클때

		h->heap[where] = h->heap[where / 2];	//자신의 부모노드가 있는 곳으로 올라감
		where /= 2;		//저장장소도 갱신
	}
	h->heap[where] = item;
}


void main() {

	int e1 = 10, e2 = 20, e3 = 30;

	HeapType* heap;

	heap = create();	//히프 동적 할당

	InsertMax(heap, e1); InsertMax(heap, e2); InsertMax(heap, e3);	//삽입
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
