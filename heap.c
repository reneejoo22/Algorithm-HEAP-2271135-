//2271135_�������ڵ�(����)_ȣ���� �ڵ���� ��� ����

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
	//HuffmanBit(n);
}

void PrintCodes(TreeNode* root, int codes[], int top, int *sum) {
	
	int huffmanbitt = 0;
	//int sum;
	
	if (root == NULL) {
		return;
	}

	if (root->left) {
		codes[top] = 1;
		//nodePassed[root->ch]++;  // ����� ch ������ �ε����� ����Ͽ� �湮 Ƚ�� ����

		// �׽�Ʈ��
		//printf("\n�� codes[top] -> %d[%d], nodepass-> %d", codes[top], top, nodePassed[root->ch]);
		// �׽�Ʈ��

		PrintCodes(root->left, codes, top + 1, sum);
	}

	if (root->right) {
		codes[top] = 0;
		//nodePassed[root->ch]++;  // ����� ch ������ �ε����� ����Ͽ� �湮 Ƚ�� ����

		// �׽�Ʈ��
		//printf("\n�� codes[top] -> %d[%d], nodepass-> %d", codes[top], top, nodePassed[root->ch]);
		// �׽�Ʈ��

		PrintCodes(root->right, codes, top + 1, sum);
	}

	if (is_leaf(root)) {
		//nodePassed[root->ch]++;  // ����� ch ������ �ε����� ����Ͽ� �湮 Ƚ�� ����
		printf("��Ʈ ��� %c: ", root->ch);
		PrintArray(codes, top);
		huffmanbitt = root->weight * top;
		*sum += huffmanbitt;
		//printf("ȣ���� ��Ʈ ��� %c�� ���̴� %d ", root->ch, huffmanbitt);
		//printf("\n���� %d",*sum);
	}

	//printf("\n\n�� ȣ���� ��Ʈ ��� ���̴� %d ", sum);
}

//�ȵǴ� ����_���� ��Ʈ�� ���ʿ� ch���� ����



//4��Ʈ ��� �Լ�
void fourBit(int freq[], int num) {

	int sum = 0;
	for (int i = 0; i < num; i++) {
		sum += freq[i];
	}
	printf("\n4��Ʈ �ڵ��: %d", sum*2);
}

void HuffmanBit(int freq[], int num, int nodePassed[]) {

	int res = 0;

	for (int i = 0; i < num; i++) {
		res += freq[i] * nodePassed[i];
		//printf("%d\n", res);
	}

	printf("\n������ �ڵ��: %d", res);

}


//������ �ڵ� ���� �Լ�
void HuffmanTree(int freq[], char ch_list[], int n) {

	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	//������ ����� ������ �����ϴ� ����
	//int nodePassed[100] = {0};
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
	//int nodeNum[] = { PrintCodes(e.ptree, codes, top, nodePassed) };
	fourBit(freq, n);	//4��Ʈ ���
	//printf("\n�� ���� ��Ʈ ��: %d\n", nodeNum);
	//HuffmanBit(freq, n, nodeNum);	//ȣ���� ��Ʈ���
	printf("\nȣ���� �ڵ��: %d", sum);
	DestroyTree(e.ptree);
	free(heap);

}



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

	HuffmanTree(freq, ch_list, 3);

	return 0;

}
