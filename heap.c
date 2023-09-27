//2271135_�������ڵ�(����)_ȣ���� �ڵ���� ��� ����+ ��ȣȭ ��ȣȭ �߰�

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MaxElement 200

typedef struct TreeNode {
	
	//�� �ΰ����� ������+ �޿� ��ġ �������� ����
	int weight;	//�󵵼�
	char ch;	//����
	struct TreeNode *left;		//������ġ
	struct TreeNode* right;		//��������ġ
}TreeNode;


typedef struct {

	// Ʈ������� ��ġ���� ������
	TreeNode* ptree;

	int key;	//������ ����, Ʈ������� �󵵼��� ���⿡ ����
	char ch;	//���ڿ� ����, Ʈ������� ���ڿ��� ���⿡ ����
	
}element;

typedef struct {
	element heap[MaxElement];	//��ġ   
	int HeapSize;	//heap�� ��� ��Ұ� ����Ǿ��ִ���
}HeapType;

//4�� ����//////////////////////
typedef struct {
	
	char code[20];
	char ori;
}CodeSave;

typedef struct {

	CodeSave array[100];
}whereCodeSave;



//����+�ʱ�ȭ �Լ�
HeapType* create() {	//heaptype��ŭ ���� �޸� �Ҵ�(�����Լ��� �����Լ� ������ ���� �ʿ�)+ �ʱ�ȭ

	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));

	if (heap == NULL) {	//heap�� ������� ���
		printf("heap �޸𸮰� �Ҵ���� �ʾҽ��ϴ�");
		return heap;
	}

	heap->HeapSize = 0;		//������� ������ 0���� �ʱ�ȭ�ϰ� 

	return heap;	//����������
}


//���� �Լ�(�ּ�)
void InsertMin(HeapType* h, element item) {	//�� ��� ����_��

	int where;	//���ο� ��带 ������ ��ġ
	where = ++(h->HeapSize);	//���� ������ �ڸ��� ����

	while ((where != 1) && (item.key < h->heap[where / 2].key)) {	//��ġ�� �� �ö� �� ������ && �θ� �ڽĺ��� Ŭ��_���ư�

		h->heap[where] = h->heap[where / 2];	//�ڽ��� �θ��尡 �ִ� ������ �ö�
		where /= 2;		//������ҵ� ����
	}
	h->heap[where] = item;
}

//�����Լ�(�ּ�)
element DeleteMin(HeapType* h) {	//�����Լ�_�ٿ�, ���Ű��>�ڽĳ��Ű��

	int parent, kid;	//�θ���� �ڽĳ���� ��ġ
	element item, tmp;

	item = h->heap[1];	//������ ��Ʈ�� Ű���� item�� ����
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

		if ((kid < h->HeapSize) && (h->heap[kid].key) > (h->heap[kid + 1].key))	// ����> ���� 
			kid++;	//�� �ڽ��� ��ġ�� �ٲ�(�� ���� ������)
		if (tmp.key < h->heap[kid].key)break;	//���� ���< �ڽ�Ű��_ ������, ����

		h->heap[parent] = h->heap[kid];	//if�� �Ѵ� ���� �ʾƼ� ����� ���, �Ʒ����� ���� ������ �ѱ�
		parent = kid;	//���������� ���� �Ѿ�� ���� �� ��� �ݺ��ؾ���. �Ʒ��� ���������ϴ� parent���� ������ ������� ��ġ���� �Ѱ���
		kid *= 2;	//Ű��� ���� �䷱Ʈ�� �ٷ� �Ʒ��� ���������ϴ� *2 ����
	}

	h->heap[parent] = tmp;	//���� �ڸ��� �־���
	return item;
}

//���� Ʈ�� �����Լ�(Ʈ����� �������� �Ҵ��ϴ� �Լ�)
TreeNode* MakeTree(TreeNode* left, TreeNode* right) {
	
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));	//Ʈ����常ŭ �޸� �����Ҵ�

	if (node == NULL) {	//Ȥ�ö� node�� ������� ���
		printf("node �޸𸮰� �Ҵ���� �ʾҽ��ϴ�");
		return node;
	}

	node->left = left;	//����� ������ ���� �Ű������� ���� �״�� �־���
	node->right = right;	//����� �������� ���� �Ű������� ���� �״�� �־���
	return node;
}

//���� Ʈ�� ���� �Լ�(Ʈ����� �������� �Ҵ��� �޸� ���� �Լ�)
void DestroyTree(TreeNode* root) {

	if (root == NULL)return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	free(root);

}

int is_leaf(TreeNode* root) {

	return !(root->left) && !(root->right);
	//��Ʈ�� ���ʰ� ������ �Ѵ� ����ִ� ��� ���� ��������
}

//����ϱ�
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
		
		printf("������ ��");
		PrintCodes(root->left, codes, top + 1, sum);
	}

	if (root->right) {
		codes[top] = 0;
		printf("������ ��");
		PrintCodes(root->right, codes, top + 1, sum);
	}

	if (is_leaf(root)) {

		printf("��Ʈ ��� %c: ", root->ch);
		PrintArray(codes, top);
		huffmanbitt = root->weight * top;
		*sum += huffmanbitt;

	}

	//printf("\n\n�� ȣ���� ��Ʈ ��� ���̴� %d ", sum);
}


void Encode(TreeNode* root, char codes[], int top, char c, CodeSave* cs) {

	if (root == NULL) {
		return;
	}

	if (root->left) {
		codes[top] = '1';
		printf("\n�� %c",codes[top]);
		Encode(root->left, codes, top + 1, c, cs);
	}

	if (root->right) {
		codes[top] = '0';
		printf("\n�� %c", codes[top]);
		Encode(root->right, codes, top + 1, c, cs);
	}

	if (is_leaf(root) && root->ch == c) {
		printf("\n����");
		// Ư�� ������ �ڵ带 encodedCode �迭�� ����
		for (int i = 0; i < top; i++) {
			cs->code[i] = codes[i];
			printf("\nencodedCode = %c",codes[i]);
		}
		cs->code[top] = '\0';
		cs->ori = c;
		return;
	}
}




TreeNode* explore(char c, TreeNode* root) {
	

	//int codes;
	//printf("����");

	if (root == NULL) {
		//printf("\n�ƹ��͵� ������"); 
		return NULL;	//��Ʈ ���� �ƹ��͵� ������ ����������
	}

	if (root->ch == c) {
		//printf("\n�ٷ��־���"); 

		return root;	// �Է¹��� root�� c�̶� �ٷ� ��ġ�ϸ� ����������
	}

	TreeNode* result = NULL;

	if (root->ch != c && root != NULL) {
		//printf("\n������ ����");

		result = explore(c, root->left);
	}
	if(result==NULL){
		//printf("\n�������� ����");
	
		result = explore(c, root->right);
	}
	
	return result;

}


//4��Ʈ ��� �Լ�
void fourBit(int freq[], int num) {

	int summ = 0;
	for (int i = 0; i < num; i++) {
		summ += freq[i];
	}
	printf("\n4��Ʈ �ڵ��: %d", summ*2);
}


//������ �ڵ� ���� �Լ�
element HuffmanTree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];	//������ ��带 ���� �迭
	int top = 0;

	//ȣ�����ڵ� ��Ʈ ���� ����� ���� ������ ���� 
	int sum = 0;


	heap = create();	//�����Ҵ��ϰ� �ʱ�ȭ��
	for (i = 0; i < n; i++) {	//���� �Ű����� n��ŭ 

		node = MakeTree(NULL, NULL);	//Ʈ���� �����Ҵ���
		e.ch = node->ch = ch_list[i];	//���ڸ� ������Ʈ�� Ʈ����忡 �� �� ������
		e.key = node->weight = freq[i];	//�󵵼�(����)�� ������Ʈ�� Ʈ����忡 �� �� ������
		e.ptree = node;
		InsertMin(heap, e);
	}
	for (i = 1; i < n; i++) {
		//�ּҰ��� ������ �ΰ��� ��带 ����
		//���� �ݺ����� ���� �ּ������� ���°� ��(��Ʈ�� �ּڰ���),
		e1 = DeleteMin(heap);
		e2 = DeleteMin(heap);
		//�ΰ��� ��带 ��ħ
		x = MakeTree(e1.ptree, e2.ptree);	//�ּڰ����� �̷���� Ʈ���� �ּ����� x�� �Ѱ���
		e.key = x->weight = e1.key + e2.key;	//��ģ ���� ����
		e.ptree = x;
		printf("%d + %d -> %d\n", e1.key, e2.key, e1.key + e2.key);
		InsertMin(heap, e);	//��ģ ���� ����
	}

	e = DeleteMin(heap);	//����Ʈ��
	printf("\n");
	PrintCodes(e.ptree, codes, top, &sum);
	fourBit(freq, n);	//4��Ʈ ���
	printf("\nȣ���� �ڵ��: %d", sum);
	
	return e;
	//���߿� �ּ� ó�� �����
	//DestroyTree(e.ptree);
	//free(heap);

}

CodeSave codeSaver;

int main() {


	/*
	int num;

	printf("�Է��� �ڷ��� ������ ���ÿ�-> ");
	scanf("%d", &num);

	char* ch_list = (char*)malloc(num * sizeof(char));
	int* freq = (int*)malloc(num * sizeof(int));

	for (int i = 0; i < num; i++) {
		
		printf("\n�Է��� ����-> ");
		scanf(" %c", &ch_list[i]);
		printf("�Է��� �󵵼�-> ");
		scanf("%d", &freq[i]);
	}
	printf("\n");
	HuffmanTree(freq, ch_list, num);
	*/

	char ch_list[] = { 'a','b','c' };
	int freq[] = { 1,2,4 };

	element e = HuffmanTree(freq, ch_list, 3);



	//��ȣȭ ����

	int numm; // �Է¹��� ������ ������ ���缭 ���� �迭 �Ҵ�

	printf("\n��ȣȭ�� ������ ������ �Է��Ͻÿ�-> ");
	scanf("%d", &numm);

	char* original = (char*)malloc((numm + 1) * sizeof(char)); // ���ڿ� + �� ���� ����('\0')�� ���� ���� �Ҵ�

	if (original == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return 1; // ���� �ڵ� ��ȯ
	}

	printf("��ȣȭ�� ���ڸ� �Է��Ͻÿ�-> ");
	scanf(" %s", original); // �ִ� ���̸� 99�� ����

	printf("original: %s\n", original);
	printf("original[1]: %c\n", original[1]);

	char codes[100], encodedCode[100], top = 0;

	for (int i = 0; i < numm; i++) {

		printf("\n--------------------%c ã��", original[i]);

		if ((explore(original[i], e.ptree)) != NULL) {
			printf("\n%c ��ȣȭ ����", original[i]);
			
		}
		else printf("\n%c ��ȣȭ �Ұ���", original[i]);
		
	}

	
	int i = 0;

	printf("a�� ��ȣȭ=========");
	Encode(e.ptree, codes, top, original[0], &codeSaver);

	printf("\n�����Լ����� %c\n", codeSaver.ori);

	
	while (codeSaver.code[i] != '\0') {
		printf("%c", codeSaver.code[i]);
		i++;
	}
	
	//printf("b�� ��ȣȭ=========");
	//Encode(e.ptree, codes, top, original[1], encodedCode);
	
	// �޸� ����
	//free(original);
	
	return 0;
}
