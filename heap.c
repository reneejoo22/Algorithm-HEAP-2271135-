//2271135_�������ڵ�(����)_ȣ���� �ڵ���� ��� ����(����)+ ��ȣȭ ��ȣȭ + preorderTraversal
//+ �޸� ����

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MaxElement 200

typedef struct TreeNode {

	//�� �ΰ����� ������+ �޿� ��ġ �������� ����
	int weight;	//�󵵼�
	char ch;	//����
	char newNode[10];	//�ΰ��� ��带 ��ġ�鼭 ���� (���ڰ��� ����)���ο� ���
	struct TreeNode* left;		//������ġ
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
typedef struct CodeSave {

	char code[20];	// ��ȣȭ�� �� ����
	char ori;	//���� ����
	struct codeSave* link;	//������ ��带 ����

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
		//printf("\n��忡 ���Ե� �ڵ� = %c", codes[i]);
	}
	p->code[top] = '\0';	//�ڿ� �ΰ� ����
	p->ori = oris;			//�޾ƿ� oris�� ����

	p->link = head;		//��� �������� ���� ����
	head = p;			//��� ������ ����, ��尡 ���� ������ ��� ����Ŵ

	print_list(head);
	return head;
}


//4�� ����//////////////////////


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
		//printf("������ ��");
		PrintCodes(root->left, codes, top + 1, sum);
	}

	if (root->right) {
		codes[top] = 0;
		//printf("������ ��");
		PrintCodes(root->right, codes, top + 1, sum);
	}

	if (is_leaf(root)) {

		printf("��Ʈ ��� %c: ", root->ch);
		PrintArray(codes, top);
		huffmanbitt = root->weight * top;
		*sum += huffmanbitt;

	}

}

//��ȣȭ, �Է¹��� ����(�ϳ���) 
void Encode(TreeNode* root, char codes[], int top, char c) {

	if (root == NULL) {
		return;
	}

	if (root->left) {
		codes[top] = '1';
		//printf("\n�� %c",codes[top]);
		Encode(root->left, codes, top + 1, c);
	}

	if (root->right) {
		codes[top] = '0';
		//printf("\n�� %c", codes[top]);
		Encode(root->right, codes, top + 1, c);
	}

	if (is_leaf(root) && root->ch == c) {
		//printf("\n����");
		insert_first(head, codes, root->ch, top);
		//����Ʈ ��忡 �ڵ�� ���ڸ� ������ ���̴� 
		return;
	}
}

//��ȣȭ�Ϸ��� �Է¹��� ���ڰ� ������ Ʈ���� �ִ��� ������ Ȯ��
TreeNode* explore(char c, TreeNode* root) {


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
	if (result == NULL) {
		//printf("\n�������� ����");

		result = explore(c, root->right);
	}

	return result;

}

//��ȣȭ �Լ�
void Decode(TreeNode* root, const char* encodedMessage) {

	TreeNode* currentNode = root;

	for (int i = 0; i < encodedMessage[i] != '\0'; i++) {
		if (encodedMessage[i] == '0') {
			//printf("\n�������� ��");
			currentNode = currentNode->right;
		}
		else if (encodedMessage[i] == '1') {
			//printf("\n������ ��");
			currentNode = currentNode->left;
		}
		else {
			printf("���� ����Դϴ�, �ٽ� �Է��Ͻʽÿ�");
			break;
		}
		if (is_leaf(currentNode)) {
			//printf("\nã��");
			printf("%c", currentNode->ch);
			currentNode = root;
			//printf("\n���� �� ã���� ��");
		}
	}
}

//2��Ʈ ��� �Լ�
void bitCal(int freq[], int num) {

	int summ = 0;	//�󵵼��� ���� �����ϴ� ��

	int N2 = 1, bitsNeeded = 0;	//N2�� while���� �������� 2�� ���ϴ� ��
	int tmp = num;

	for (int i = 0; i < num; i++) {	//�󵵼��� ���� ���
		summ += freq[i];
	}

	//���Ʈ���� ���
	while (tmp != 1 && tmp != 0) {	//�������� 0�̰ų� 1�̸� ����

		tmp /= 2;
		N2 *= 2;	//�������� 2����
		bitsNeeded++;	//�� ���
	}

	if (num > N2) {	//���� ��� num�� 20�̸� 2��4�� �̻��̴� 5��Ʈ�� �ʿ�

		bitsNeeded++;	//�׷��� ��Ʈ���� +1
	}
	else if (num <= N2) {	//���� ��쿡�� ���� ���� ���� ����

		bitsNeeded += 0;
	}

	printf("\n%d ��Ʈ �ڵ�� ǥ����: %d", bitsNeeded, summ * bitsNeeded);

}


//������ȸ
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

//������ �ڵ� ���� �Լ�
element HuffmanTree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, * x;
	//HeapType* heap;    �޸� ������ ������
	element e, e1, e2;
	int codes[100];	//������ ��带 ���� �迭
	int top = 0;

	//ȣ�����ڵ� ��Ʈ ���� ����� ���� ������ ���� 
	int sum = 0;

	//3������ ������ ���� ����
	int test = 1;


	heap = create();	//�����Ҵ��ϰ� �ʱ�ȭ��
	for (i = 0; i < n; i++) {	//���� �Ű����� n��ŭ 

		node = MakeTree(NULL, NULL);	//Ʈ���� �����Ҵ���
		e.ch = node->ch = ch_list[i]; //���ڸ� ������Ʈ�� Ʈ����忡 �� �� ������
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

		sprintf(x->newNode, "(H-%d)", test);  // ���ڿ��� "H-n" ���� ����
		test++;
		x->ch = NULL;	//���ڸ� ������ �ִ� ������� �ƴ��� �����ϱ� ���ؼ�

		e.ptree = x;
		printf("%d + %d -> %d", e1.key, e2.key, e.key);
		printf(" %s\n", x->newNode);

		InsertMin(heap, e);	//��ģ ���� ����
	}


	e = DeleteMin(heap);	//����Ʈ��

	//������ȸ
	printf("\n*** preorder traversal_������ȸ ***\n");
	preorderTraversal(e.ptree);
	printf("\n\n");

	//�� ����� ���(�ڵ�) ���
	printf("*** �� ����� ��� ***\n");
	PrintCodes(e.ptree, codes, top, &sum);

	//��Ʈ �ڵ�� ���
	bitCal(freq, n);	//2��Ʈ ���
	printf("\n���� ������ �ڵ�� ǥ����: %d", sum);

	return e;
	//���߿� �ּ� ó�� �����
	//DestroyTree(e.ptree);
	//free(heap);

}


int main() {

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


	//char ch_list[] = { 'a','b','c' };
	//int freq[] = { 1,2,4 };

	element e = HuffmanTree(freq, ch_list, num);


	int numm; // �Է¹��� ������ ������ ���缭 ���� �迭 �Ҵ�

	printf("\n\n��ȣȭ�� ���ڿ��� ������ �Է��Ͻÿ�-> ");
	scanf("%d", &numm);

	char* original = (char*)malloc((numm + 1) * sizeof(char)); // ���ڿ� + �� ���� ����('\0')�� ���� ���� �Ҵ�

	if (original == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return 1; // ���� �ڵ� ��ȯ
	}

	printf("��ȣȭ�� ���ڸ� �Է��Ͻÿ�-> ");
	scanf(" %s", original);


	char codes[100], top = 0;

	for (int i = 0; i < numm; i++) {

		if ((explore(original[i], e.ptree)) != NULL) {	//�ִ��� ������ Ȯ��
			//printf("\n%c ��ȣȭ ����", original[i]);
			Encode(e.ptree, codes, top, original[i]);
		}
		else printf("\n%c ���� ���ڷ� ��ȣȭ �Ұ���", original[i]);

	}

	//��ȣȭ ����

	char decode[100];

	printf("\n��ȣȭ�� �ڵ带 �Է��Ͻÿ�-> ");
	scanf(" %s", decode);

	int decodeLength = strlen(decode); // ���ڿ��� ���̸� ���
	const char* decodedString = (char*)malloc((decodeLength + 1) * sizeof(char));	//�Է¹��� ���ڿ� ���̸�ŭ �����Ҵ�

	strcpy(decodedString, decode);

	Decode(e.ptree, decodedString);


	//�޸� ����
	free(original); free(decodedString);
	DestroyTree(e.ptree); free(heap);

	return 0;
}