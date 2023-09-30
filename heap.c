//2271135_허프만코드(과제)_호프만 코드길이 계산 구현(수정)+ 암호화 복호화 + preorderTraversal
//+ 메모리 해제

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MaxElement 200

typedef struct TreeNode {

	//이 두가지의 정보와+ 왼오 위치 정보값을 가짐
	int weight;	//빈도수
	char ch;	//문자
	char newNode[10];	//두개의 노드를 합치면서 생긴 (문자값이 없는)새로운 노드
	struct TreeNode* left;		//왼쪽위치
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

//4번 문제//////////////////////
typedef struct CodeSave {

	char code[20];	// 암호화한 것 저장
	char ori;	//원본 저장
	struct codeSave* link;	//이후의 노드를 저장

}CodeSave;

CodeSave* head = NULL;

void print_list(CodeSave* head) {

	int i = 0;


	while (head->code[i] != '\0') {
		printf("%c", head->code[i]);
		i++;
	}
}

CodeSave* insert_first(CodeSave* head, char codes[], char oris, int top) {

	CodeSave* p = (CodeSave*)malloc(sizeof(CodeSave));

	for (int i = 0; i < top; i++) {
		p->code[i] = codes[i];
		//printf("\n노드에 삽입된 코드 = %c", codes[i]);
	}
	p->code[top] = '\0';	//뒤에 널값 넣음
	p->ori = oris;			//받아온 oris를 넣음

	p->link = head;		//헤드 포인터의 값을 복사
	head = p;			//헤드 포인터 변경, 헤드가 새로 생성된 노드 가르킴

	print_list(head);
	return head;
}


//4번 문제//////////////////////


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

void PrintCodes(TreeNode* root, int codes[], int top, int* sum) {

	int huffmanbitt = 0;
	//int sum;

	if (root == NULL) {
		return;
	}

	if (root->left) {
		codes[top] = 1;
		//printf("왼으로 감");
		PrintCodes(root->left, codes, top + 1, sum);
	}

	if (root->right) {
		codes[top] = 0;
		//printf("른으로 감");
		PrintCodes(root->right, codes, top + 1, sum);
	}

	if (is_leaf(root)) {

		printf("비트 계산 %c: ", root->ch);
		PrintArray(codes, top);
		huffmanbitt = root->weight * top;
		*sum += huffmanbitt;

	}

}

//암호화, 입력받은 문자(하나만) 
void Encode(TreeNode* root, char codes[], int top, char c) {

	if (root == NULL) {
		return;
	}

	if (root->left) {
		codes[top] = '1';
		//printf("\n왼 %c",codes[top]);
		Encode(root->left, codes, top + 1, c);
	}

	if (root->right) {
		codes[top] = '0';
		//printf("\n오 %c", codes[top]);
		Encode(root->right, codes, top + 1, c);
	}

	if (is_leaf(root) && root->ch == c) {
		//printf("\n멈춤");
		insert_first(head, codes, root->ch, top);
		//리스트 노드에 코드와 문자를 삽입할 것이다 
		return;
	}
}

//암호화하려고 입력받은 문자가 히프만 트리에 있는지 없는지 확인
TreeNode* explore(char c, TreeNode* root) {


	if (root == NULL) {
		//printf("\n아무것도 없었다"); 
		return NULL;	//루트 값에 아무것도 없으면 돌려보내기
	}

	if (root->ch == c) {
		//printf("\n바로있었다"); 

		return root;	// 입력받은 root가 c이랑 바로 일치하면 돌려보내기
	}

	TreeNode* result = NULL;

	if (root->ch != c && root != NULL) {
		//printf("\n왼으로 간다");

		result = explore(c, root->left);
	}
	if (result == NULL) {
		//printf("\n오른으로 간다");

		result = explore(c, root->right);
	}

	return result;

}

//복호화 함수
void Decode(TreeNode* root, const char* encodedMessage) {

	TreeNode* currentNode = root;

	for (int i = 0; i < encodedMessage[i] != '\0'; i++) {
		if (encodedMessage[i] == '0') {
			//printf("\n오른으로 감");
			currentNode = currentNode->right;
		}
		else if (encodedMessage[i] == '1') {
			//printf("\n왼으로 감");
			currentNode = currentNode->left;
		}
		else {
			printf("없는 경로입니다, 다시 입력하십시오");
			break;
		}
		if (is_leaf(currentNode)) {
			//printf("\n찾음");
			printf("%c", currentNode->ch);
			currentNode = root;
			//printf("\n이후 것 찾으러 감");
		}
	}
}

//2비트 계산 함수
void bitCal(int freq[], int num) {

	int summ = 0;	//빈도수의 합을 저장하는 값

	int N2 = 1, bitsNeeded = 0;	//N2는 while문이 돌때마다 2를 곱하는 값
	int tmp = num;

	for (int i = 0; i < num; i++) {	//빈도수의 합을 계산
		summ += freq[i];
	}

	//몇비트인지 계산
	while (tmp != 1 && tmp != 0) {	//나머지가 0이거나 1이면 멈춤

		tmp /= 2;
		N2 *= 2;	//돌때마다 2곱함
		bitsNeeded++;	//승 계산
	}

	if (num > N2) {	//예를 들어 num이 20이면 2의4승 이상이니 5비트가 필요

		bitsNeeded++;	//그러니 비트수에 +1
	}
	else if (num <= N2) {	//같은 경우에는 따로 취할 조취 없음

		bitsNeeded += 0;
	}

	printf("\n%d 비트 코드로 표현시: %d", bitsNeeded, summ * bitsNeeded);

}


//전위순회
void preorderTraversal(TreeNode* root) {

	//tmp = e;

	if (root != NULL) {
		if (root->ch == NULL) {

			printf("%s ", root->newNode);
		}
		else if (root->ch != NULL) {
			printf("%c ", root->ch);
		}
		//tmp = root->left;
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

HeapType* heap;

//허프만 코드 생성 함수
element HuffmanTree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, * x;
	//HeapType* heap;    메모리 해제를 메인함
	element e, e1, e2;
	int codes[100];	//지나간 노드를 담을 배열
	int top = 0;

	//호프만코드 비트 값의 계산을 담을 정수형 변수 
	int sum = 0;

	//3번문제 때문에 만든 정수
	int test = 1;


	heap = create();	//동적할당하고 초기화함
	for (i = 0; i < n; i++) {	//받은 매개변수 n만큼 

		node = MakeTree(NULL, NULL);	//트리를 동적할당함
		e.ch = node->ch = ch_list[i]; //문자를 엘리멘트랑 트리노드에 둘 다 저장함
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

		sprintf(x->newNode, "(H-%d)", test);  // 문자열로 "H-n" 형식 저장
		test++;
		x->ch = NULL;	//문자를 가지고 있는 노드인지 아닌지 구별하기 위해서

		e.ptree = x;
		printf("%d + %d -> %d", e1.key, e2.key, e.key);
		printf(" %s\n", x->newNode);

		InsertMin(heap, e);	//합친 값을 삽입
	}


	e = DeleteMin(heap);	//최종트리

	//전위순회
	printf("\n*** preorder traversal_전위순회 ***\n");
	preorderTraversal(e.ptree);
	printf("\n\n");

	//각 노드의 경로(코드) 출력
	printf("*** 각 노드의 경로 ***\n");
	PrintCodes(e.ptree, codes, top, &sum);

	//비트 코드시 계산
	bitCal(freq, n);	//2비트 계산
	printf("\n가변 길이의 코드로 표현시: %d", sum);

	return e;
	//나중에 주석 처리 지우기
	//DestroyTree(e.ptree);
	//free(heap);

}


int main() {

	int num;

	printf("입력할 자료의 개수를 쓰시오-> ");
	scanf("%d", &num);

	char* ch_list = (char*)malloc(num * sizeof(char));
	int* freq = (int*)malloc(num * sizeof(int));

	for (int i = 0; i < num; i++) {

		printf("\n입력할 문자-> ");
		scanf(" %c", &ch_list[i]);
		printf("입력할 빈도수-> ");
		scanf("%d", &freq[i]);
	}
	printf("\n");


	//char ch_list[] = { 'a','b','c' };
	//int freq[] = { 1,2,4 };

	element e = HuffmanTree(freq, ch_list, num);


	int numm; // 입력받을 문자의 갯수에 맞춰서 동적 배열 할당

	printf("\n\n암호화할 문자열의 갯수를 입력하시오-> ");
	scanf("%d", &numm);

	char* original = (char*)malloc((numm + 1) * sizeof(char)); // 문자열 + 널 종료 문자('\0')를 위한 공간 할당

	if (original == NULL) {
		printf("메모리 할당 실패\n");
		return 1; // 실패 코드 반환
	}

	printf("암호화할 문자를 입력하시오-> ");
	scanf(" %s", original);


	char codes[100], top = 0;

	for (int i = 0; i < numm; i++) {

		if ((explore(original[i], e.ptree)) != NULL) {	//있는지 없는지 확인
			//printf("\n%c 암호화 가능", original[i]);
			Encode(e.ptree, codes, top, original[i]);
		}
		else printf("\n%c 없는 문자로 암호화 불가능", original[i]);

	}

	//복호화 진행

	char decode[100];

	printf("\n복호화할 코드를 입력하시오-> ");
	scanf(" %s", decode);

	int decodeLength = strlen(decode); // 문자열의 길이를 계산
	const char* decodedString = (char*)malloc((decodeLength + 1) * sizeof(char));	//입력받은 문자열 길이만큼 동적할당

	strcpy(decodedString, decode);

	Decode(e.ptree, decodedString);


	//메모리 해제
	free(original); free(decodedString);
	DestroyTree(e.ptree); free(heap);

	return 0;
}