#define _CRT_SECURE_NO_WARNNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_ELEMENT 200

int codes_sum = 0, count = 0;


typedef struct TreeNode {
	int weight;	//�󵵼�
	char ch;	//����(����), �ڵ带 �ο��� ���
	struct TreeNode* left;
	struct TreeNode* right;
	int nodeNumber;	//�߰��� ����� ������ ��� ����
}TreeNode;

typedef struct {
	TreeNode* ptree;	//�ش� element Ÿ���� ������ ������Ʈ���� 
						//��� ���Ǵ��� �˷��ֱ� ���� ������
	char ch;
	int key;	//�󵵼� ����
	int nodeNumber;
}element;

typedef struct {
	element heap[MAX_ELEMENT];	//�ּ�����
	int heap_size;
}HeapType;

//���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//�ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

//���� ����� ������ heap_size�� ���� h�� item�� ������
//�����Լ�
void insertMinHeap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//Ʈ���� �Ž��� �ö󰡸鼭 �θ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//���� �Լ�
element deleteMinHeap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//���� ����� �ڽĳ�� �� �� ���� �ڽ� ��带 ã��
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key)
			break;

		//�� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//����Ʈ�� �����Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//����Ʈ�� �����Լ�
void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	if (root->ch == 'H')
		printf("%c-%d ", root->ch, root->nodeNumber);
	else {
		printf("%c ", root->ch);
	}

	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//�ܸ���� �˻� �Լ�
int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {	//������ȸ
	//1�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	//0�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	//�ܸ�����̸� �ڵ带 ����Ѵ�.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
		top *= root->weight;
		codes_sum += top;
	}
}

void huffman_tree(int freq[], char ch_list[], int n) {
	int i;
	int sum = 0;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int tops = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insertMinHeap(heap, e);
	}

	for (i = 1; i < n; i++) {	//������ Ʈ�� �������, ��Ʈ�� ������ �߰�
		//�ּҰ��� ������ �� ���� ��带 ����
		e1 = deleteMinHeap(heap);
		e2 = deleteMinHeap(heap);
		//�� ���� ��带 ��ģ��.
		x = make_tree(e1.ptree, e2.ptree);
		e.ch = x->ch = 'H';
		e.key = x->weight = e1.key + e2.key;
		e.nodeNumber = x->nodeNumber = ++count;
		e.ptree = x;
		printf("%d + %d -> %d (H-%d) \n", e1.key, e2.key, e.key, x->nodeNumber);
		insertMinHeap(heap, e);
	}
	e = deleteMinHeap(heap);	//����Ʈ��
	printf("----------�ο��� ������ �ڵ�----------\n");
	print_codes(e.ptree, codes, tops);
	
	printf("------------������ȸ ���-------------\n");
	destroy_tree(e.ptree);
	free(heap);
}

int main() {
	int T, sum = 0;
	scanf("%d", &T);
	TreeNode* huff_tree;

	char* ch_list = (char*)malloc(sizeof(char) * T);
	int* freq = (int*)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		scanf("%s %d", &ch_list[i], &freq[i]);
		sum += freq[i] * 4;
	}
	huffman_tree(freq, ch_list, T);
	printf("\n--------------------------------------\n");
	printf("4��Ʈ �ڵ� ���� %d bits ���\n", sum);
	printf("huffman �ڵ� ���� %d bits ���\n", codes_sum);
	return 0;
}