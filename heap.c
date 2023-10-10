//2271135_�������ڵ�(����)  

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MaxElement 200
#define MaxTreeInput 10 
#define MaxCharInput 100 

typedef struct TreeNode {

	int weight;	//�󵵼�
	char ch;	//����
	char newNode[MaxTreeInput];   //�ΰ��� ��带 ��ġ�鼭 ���� (���ڰ��� ����)���ο� ���
	
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

//��ȣȭ�� �͵��� ���
void print_list(CodeSave* head) {

	int i = 0;

	while (head->code[i] != '\0') {
		printf("%c", head->code[i]);
		i++;
	}
}

//���� ��ȣȭ�� �ڵ� ���� ����Ʈ�� ����
CodeSave* insert_first(CodeSave* phead, char codes[], char oris, int top) {

	CodeSave* p = (CodeSave*)malloc(sizeof(CodeSave));

	if (p) {	//��� 6011 ������ �߰��� ���ǹ�

		for (int i = 0; i < top; i++) {
			p->code[i] = codes[i];
			//printf("\n��忡 ���Ե� �ڵ� = %c", codes[i]);
		}

		p->code[top] = '\0';	//�ڿ� �ΰ� ����
		p->ori = oris;			//�޾ƿ� oris�� ����

		p->link = phead;		//��� �������� ���� ����
		phead = p;			//��� ������ ����, ��尡 ���� ������ ��� ����Ŵ
	}
	else {
		printf("p���� �Ҵ���� ����");  //  �� �Ҵ� �Ǵ� ���� ó���� �ʿ���. 
	}

	print_list(phead);
	
	return phead;
}

//3�� ����//////////////////////


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

//��Ʈ ��� �Լ�
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


	if (root != NULL) {
		if (root->ch == '\0') {

			printf("%s ", root->newNode);
		}
		else if (root->ch !=  '\0' ) {
			printf("%c ", root->ch);
		}
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
		x->ch = '\0'; // NULL;	//���ڸ� ������ �ִ� ������� �ƴ��� �����ϱ� ���ؼ�

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
	bitCal(freq, n);	//��Ʈ ���
	printf("\n���� ������ �ڵ�� ǥ����: %d", sum);

	return e;

}

//�ߺ��� ���� �ִ��� Ȯ���ϴ� �Լ�
int isDuplicate(char ch, char* ch_list, int length) {
	for (int i = 0; i < length; i++) {
		if (ch == ch_list[i]) {
			return 1; // �ߺ��� ���ڰ� �߰ߵǸ� 1�� ��ȯ
		}
	}
	return 0; // �ߺ��� ���ڰ� ������ 0�� ��ȯ
}


int main() {

	int num = 0;	//�Է¹��� �ڷ��� ����

	char input = 0;	
	int isDup = 0;


	printf("�Է��� �ڷ��� ������ ���ÿ�-> ");
	if (scanf("%d", &num) == 0) { printf("scanf error \n"); }	//6031 ��� ������ ��ȯ���� �������� Ȯ���� �� �ִ� ���ǹ���


	char* ch_list = (char*)malloc(num * sizeof(char));
	int* freq = (int*)malloc(num * sizeof(int));

	for (int i = 0; i < num; i++) {
		
		input = 0;
		isDup = 0;

		do{
			isDup = 0; // �ʱⰪ 0���� ����
			
			printf("\n�Է��� ����-> ");
			if( scanf(" %c", &input) == 0 ) { printf("scanf error \n"); }

			if (isDuplicate(input, ch_list, i)) { //�ߺ��� ���� �ִ��� Ȯ��
				printf("�̹� �Է��� �����Դϴ�. �ٸ� ���ڸ� �Է��ϼ���.\n");
				isDup = 1; // �ߺ��� ���ڰ� ������ isDup�� 1�� 
			}
		} while (isDup); // �ߺ��� ���ڰ� ������ �ٽ� �Է� �ޱ�

		ch_list[i] = input;

		printf("�Է��� �󵵼�-> ");
		if( scanf("%d", &freq[i]) == 0 ) { printf("scanf error \n"); }
	} 
	printf("\n\n");


	element e = HuffmanTree(freq, ch_list, num);


	int numm = 0; // �Է¹��� ������ ������ ���缭 ���� �迭 �Ҵ�

	printf("\n\n��ȣȭ�� ���ڿ��� ������ �Է��Ͻÿ�-> ");
	if( scanf("%d", &numm) ==0 ) { printf("scanf error \n"); }

	char* original = (char*)malloc((numm + 1) * sizeof(char)); // ���ڿ� + �� ���� ����('\0')�� ���� ���� �Ҵ�

	if (original == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return 1; // ���� �ڵ� ��ȯ
	}

	printf("��ȣȭ�� ���ڸ� �Է��Ͻÿ�-> ");
	if(scanf(" %s", original) ==0 ) { printf("scanf error \n"); }


	char codes[MaxCharInput], top = 0;

	for (int i = 0; i < numm; i++) { 

		if ((explore(original[i], e.ptree)) != NULL || original[i] != NULL) {	//�ִ��� ������ Ȯ��
			//printf("\n%c ��ȣȭ ����", original[i]);
			Encode(e.ptree, codes, top, original[i]);
		}
		else printf("\n%c ���� ���ڷ� ��ȣȭ �Ұ���", original[i]);

	}

	//��ȣȭ ����

	char decode[MaxCharInput] = { 0, };	//���� �ʱ�ȭ
	char* decodedString;

	printf("\n��ȣȭ�� �ڵ带 �Է��Ͻÿ�-> ");
	if( scanf(" %s", decode) ==0 ) { printf("scanf error \n"); }

	int decodeLength = strlen(decode); // ���ڿ��� ���̸� ���
	
	decodedString = (char*)malloc((decodeLength + 1) * sizeof(char));	//�Է¹��� ���ڿ� ���̸�ŭ �����Ҵ�
	if (decodedString == 0) { return;  }

	strcpy(decodedString, decode);

	Decode(e.ptree, decodedString);


	//�޸� ����
	free(original); free(decodedString);
	DestroyTree(e.ptree); free(heap);
	free(ch_list); free(freq);

	return 0;
}