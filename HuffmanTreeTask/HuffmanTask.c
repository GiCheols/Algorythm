#define _CRT_SECURE_NO_WARNNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_ELEMENT 200

int codes_sum = 0, count = 0;


typedef struct TreeNode {
	int weight;	//빈도수
	char ch;	//문자(글자), 코드를 부여할 대상
	struct TreeNode* left;
	struct TreeNode* right;
	int nodeNumber;	//추가된 노드의 정보를 담는 변수
}TreeNode;

typedef struct {
	TreeNode* ptree;	//해당 element 타입의 정보가 허프만트리의 
						//어디에 사용되는지 알려주기 위한 포인터
	char ch;
	int key;	//빈도수 정보
	int nodeNumber;
}element;

typedef struct {
	element heap[MAX_ELEMENT];	//최소히프
	int heap_size;
}HeapType;

//생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

//현재 요소의 개수가 heap_size인 히프 h에 item을 삽입함
//삽입함수
void insertMinHeap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//트리를 거슬러 올라가면서 부모노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//삭제 함수
element deleteMinHeap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//현재 노드의 자식노드 중 더 작은 자식 노드를 찾음
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key)
			break;

		//한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//이진트리 생성함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//이진트리 제거함수
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

//단말노드 검사 함수
int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {	//전위순회
	//1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	//0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	//단말노드이면 코드를 출력한다.
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

	for (i = 1; i < n; i++) {	//허프만 트리 구축과정, 루트를 생성해 추가
		//최소값을 가지는 두 개의 노드를 삭제
		e1 = deleteMinHeap(heap);
		e2 = deleteMinHeap(heap);
		//두 개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.ch = x->ch = 'H';
		e.key = x->weight = e1.key + e2.key;
		e.nodeNumber = x->nodeNumber = ++count;
		e.ptree = x;
		printf("%d + %d -> %d (H-%d) \n", e1.key, e2.key, e.key, x->nodeNumber);
		insertMinHeap(heap, e);
	}
	e = deleteMinHeap(heap);	//최종트리
	printf("----------부여된 허프만 코드----------\n");
	print_codes(e.ptree, codes, tops);
	
	printf("------------전위순회 결과-------------\n");
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
	printf("4비트 코드 사용시 %d bits 사용\n", sum);
	printf("huffman 코드 사용시 %d bits 사용\n", codes_sum);
	return 0;
}