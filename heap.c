#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct {
	int key;	//정수값 저장
}element;

typedef struct {
	element heap[MaxElement];	//위치   
	int HeapSize;	//heap에 몇개의 요소가 저장되어있는지
}HeapType;


HeapType* create() {	//heaptype만큼 동적 메모리 할당(삭제함수나 삽입함수 구현을 위해 필요)+ 초기화

	HeapType* heap= (HeapType*)malloc(sizeof(HeapType));
	
	if (heap == NULL) {
		printf("메모리가 할당되지 않았습니다");
		return heap;
	}

	heap->HeapSize = 0;

	return heap;
}



void InsertMax(HeapType* h, element item) {	//새 노드 저장_업

	int where;	//새로운 노드를 저장할 위치
	where = ++(h->HeapSize);	//가장 마지막 자리에 저장

	while ((where != 1) && (item.key > h->heap[where / 2].key)) {	//where가 1이 아니고(더 올라갈 곳 X) && 부모노드보다 클때

		h->heap[where] = h->heap[where / 2];	//자신의 부모노드가 있는 곳으로 올라감
		where /= 2;		//저장장소도 갱신
	}
	h->heap[where] = item;
}


element DeleteMax(HeapType* h) {	//삭제함수_부모노드키값>자식노드키값

	int parent, kid;	//부모노드와 자식노드의 위치
	element item, tmp;

	item = h->heap[1];	//삭제할 루트 값의 키값을 item에 저장
	tmp = h->heap[(h->HeapSize)--];	//막내 노드의 키값 저장

	parent = 1;	//맨 위의 위치
	kid = 2;	// 그아래 왼쪽 위치

	while (kid <= h->HeapSize) {	//자식이 정해진 범위 안에 있는 동안만

		/*
		루트 노드와 자식 노드를 비교
		1. [첫번째 if문] 왼자, 오자 중 비교할 것 추리기(둘 중 하나 고르기, 제일 값이 큰 애로)
		2. [두번째 if문] 고른 쪽의 왼쪽 자식의 키값과 루트노드의 키 값 비교. 부모>자식 성립하면 멈추고 아니면

		부모<자식이니
		자식의 키값을 부모가 위치한쪽으로 덮어씌움+ 가르키는 위치는 아래로 내려감
		*/

		if ((kid < h->HeapSize) && (h->heap[kid].key) < (h->heap[kid + 1].key))	// 왼자< 오자 
			kid++;	//오 자식의 위치로 바꿈
		if (tmp.key >= h->heap[kid].key)break;	//막내 노드>= 자식키값_ 성립ㅇ, 정착

		h->heap[parent] = h->heap[kid];	//if문 둘다 맞지 않아서 벗어나온 경우, 아래값을 위의 값으로 넘김
		parent = kid;	//히프사이즈 값을 넘어가지 않은 한 계속 반복해야함. 아래로 내려가야하니 parent한테 현재의 막내노드 위치값을 넘겨줌
		kid *= 2;	//키드는 현재 페런트의 바로 아래로 내려가야하니 *2 해줌
	}

	h->heap[parent] = tmp;	//최종 자리에 넣어줌
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

	heap = create();	//히프 동적 할당과 초기화

	InsertMax(heap, e1); InsertMax(heap, e2); InsertMax(heap, e3);	//heap 하나에 엘리멘트를 전부 넣기
	/*
			30
		   /  \
		  10  20
	*/
	printf("삽입한 순서\n");
	PrintHeap(heap);
	

	printf("삭제 값\n");
	e4 = DeleteMax(heap);	//heap의 삭제된 값을 e4에 저장
	printf("%d ", e4.key);

	e5 = DeleteMax(heap);	//heap의 삭제된 값을 e4에 저장
	printf("%d ", e5.key);

	e6 = DeleteMax(heap);	//heap의 삭제된 값을 e4에 저장
	printf("%d ", e6.key);
		
	free(heap);

}
