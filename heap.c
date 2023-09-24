//Heap를 이용한 Huffman Code

#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct TreeNode {
	
	//이 두가지의 정보와+ 왼오 위치 정보값을 가짐
	int weight;	//빈도수
	char ch;	//문자
	struct TreeNode *left;		//왼쪽위치
	struct TreeNode* right;		//오른쪽위치
}TreeNode;


typedef struct {

	// 트리노드의 위치값을 저장함
	TreeNode* ptree;

	int key;	//정수값 저장, 트리노드의 빈도수를 여기에 저장
	char ch;	//문자열 저장, 트리노드의 문자열을 여기에 저장
	
}element;

typedef struct {
	element heap[MaxElement];	//위치   
	int HeapSize;	//heap에 몇개의 요소가 저장되어있는지
}HeapType;


//생성+초기화 함수
HeapType* create() {	//heaptype만큼 동적 메모리 할당(삭제함수나 삽입함수 구현을 위해 필요)+ 초기화

	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));

	if (heap == NULL) {	//heap이 비어있을 경우
		printf("heap 메모리가 할당되지 않았습니다");
		return heap;
	}

	heap->HeapSize = 0;		//비어있지 않으면 0으로 초기화하고 

	return heap;	//돌려보내기
}


//삽입 함수(최소)
void InsertMin(HeapType* h, element item) {	//새 노드 저장_업

	int where;	//새로운 노드를 저장할 위치
	where = ++(h->HeapSize);	//가장 마지막 자리에 저장

	while ((where != 1) && (item.key < h->heap[where / 2].key)) {	//위치가 더 올라갈 곳 있을때 && 부모가 자식보다 클때_돌아감

		h->heap[where] = h->heap[where / 2];	//자신의 부모노드가 있는 곳으로 올라감
		where /= 2;		//저장장소도 갱신
	}
	h->heap[where] = item;
}

//삭제함수(최소)
element DeleteMin(HeapType* h) {	//삭제함수_다운, 노드키값>자식노드키값

	int parent, kid;	//부모노드와 자식노드의 위치
	element item, tmp;

	item = h->heap[1];	//삭제할 루트의 키값을 item에 저장
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

		if ((kid < h->HeapSize) && (h->heap[kid].key) > (h->heap[kid + 1].key))	// 왼자> 오자 
			kid++;	//오 자식의 위치로 바꿈(더 작은 값으로)
		if (tmp.key < h->heap[kid].key)break;	//막내 노드< 자식키값_ 성립ㅇ, 정착

		h->heap[parent] = h->heap[kid];	//if문 둘다 맞지 않아서 벗어나온 경우, 아래값을 위의 값으로 넘김
		parent = kid;	//히프사이즈 값을 넘어가지 않은 한 계속 반복해야함. 아래로 내려가야하니 parent한테 현재의 막내노드 위치값을 넘겨줌
		kid *= 2;	//키드는 현재 페런트의 바로 아래로 내려가야하니 *2 해줌
	}

	h->heap[parent] = tmp;	//최종 자리에 넣어줌
	return item;
}

//이진 트리 생성함수(트리노드 동적으로 할당하는 함수)
TreeNode* MakeTree(TreeNode* left, TreeNode* right) {
	
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));	//트리노드만큼 메모리 동적할당

	if (node == NULL) {	//혹시라도 node이 비어있을 경우
		printf("node 메모리가 할당되지 않았습니다");
		return node;
	}

	node->left = left;	//노드의 왼쪽은 받은 매개변수의 값을 그대로 넣어줌
	node->right = right;	//노드의 오른쪽은 받은 매개변수의 값을 그대로 넣어줌
	return node;
}

//이진 트리 제거 함수(트리노드 동적으로 할당한 메모리 해제 함수)
void DestroyTree(TreeNode* root) {

	if (root == NULL)return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	free(root);

}

int is_leaf(TreeNode* root) {

	return !(root->left) && !(root->right);
	//루트의 왼쪽과 오른쪽 둘다 비어있는 경우 참을 돌려보냄
}

//출력하기
void PrintArray(int codes[], int n) {

	for (int i = 0; i < n; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

//코드를 분석하고 값을 넘겨줌
void PrintCodes(TreeNode* root, int codes[], int top) {

	//1을 저장하고 순환호출한다
	if (root->left) {		
		codes[top] = 1;	//왼쪽에 자리가 있으면 내려가서 1을 넣음
		PrintCodes(root->left, codes, top + 1);
	}
	//0을 저장하고 순환호출한다
	if (root->right) {
		codes[top] = 0;		//오른쪽에 자리가 있으면 내려가서 1을 넣음
		PrintCodes(root->right, codes, top + 1);
	}
	if (is_leaf(root)) {	//오른쪽 왼쪽 전부 돌았으면
		printf("%c: ", root->ch);
		PrintArray(codes, top);
	}
}

//허프만 코드 생성 함수
void HuffmanTree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, * x;
	HeapType* heap;	
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();	//동적할당하고 초기화함
	for (i = 0; i < n; i++) {	//받은 매개변수 n만큼 

		node = MakeTree(NULL, NULL);	//트리를 동적할당함
		e.ch = node->ch = ch_list[i];	//문자를 엘리멘트랑 트리노드에 둘 다 저장함
		e.key = node->weight = freq[i];	//빈도수(정수)를 엘리멘트랑 트리노드에 둘 다 저장함
		e.ptree = node;
		InsertMin(heap, e);
	}
	for (i = 1; i < n; i++) {
		//최소값을 가지는 두개의 노드를 삭제
		//앞의 반복문을 통해 최소히프의 형태가 됨(루트가 최솟값인),
		e1 = DeleteMin(heap);
		e2 = DeleteMin(heap);
		//두개의 노드를 합침
		x = MakeTree(e1.ptree, e2.ptree);	//최솟값으로 이루어진 트리의 주소지를 x에 넘겨줌
		e.key = x->weight = e1.key + e2.key;	//합친 값을 저장
		e.ptree = x;
		printf("%d + %d -> %d\n", e1.key, e2.key, e1.key + e2.key);
		InsertMin(heap, e);	//합친 값을 삽입
	}

	e = DeleteMin(heap);	//최종트리
	PrintCodes(e.ptree, codes, top);
	DestroyTree(e.ptree);
	free(heap);

}


int main() {

	char ch_list[] = {'s', 'i', 'n', 't', 'e'};
	int freq[] = { 4,6,8,12,15 };

	HuffmanTree(freq, ch_list, 5);

	return 0;
}
