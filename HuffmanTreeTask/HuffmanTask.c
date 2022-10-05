#define _CRT_SECURE_NO_WARNNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

int codes_sum = 0, count = 0;
int j = 0;

typedef struct TreeNode {
	int weight;	//빈도수
	char ch;	//문자(글자), 코드를 부여할 대상
	struct TreeNode* left;
	struct TreeNode* right;
	int nodeNumber;	//추가된 노드의 정보를 담는 변수
}TreeNode;

typedef struct {
	char ch;
	int freq;
	int* codes;
	int codestop;
}encodeArray;

encodeArray* encodearray;

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

void codesArray(int codes[], int freq, char ch, int top) {
	encodearray[j].ch = ch;
	encodearray[j].freq = freq;
	encodearray[j].codestop = top;
	for (int i = 0; i < encodearray[j].codestop; i++) {
		(encodearray[j].codes)[i] = codes[i];
	}
	j++;
}

void encoding(TreeNode* root, int codes[], int top) {
	if (root->left) {
		codes[top] = 1;
		encoding(root->left, codes, top + 1);
	}
	if (root->right) {
		codes[top] = 0;
		encoding(root->right, codes, top + 1);
	}

	if (is_leaf(root)){ 
		codesArray(codes, root->weight, root->ch, top);
	}
}

TreeNode* huffmanTree;
void makeNewHuffmanTree(int freq[], char ch_list[], int n) {
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insertMinHeap(heap, e);
	}

	for (i = 1; i < n; i++) {
		e1 = deleteMinHeap(heap);
		e2 = deleteMinHeap(heap);
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insertMinHeap(heap, e);
	}
	e = deleteMinHeap(heap);
	huffmanTree = e.ptree;

	encoding(e.ptree, codes, 0);
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
	int testcase = 0;
	scanf("%d", &T);

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

	printf("\n--------------------------------------\n");
	scanf("%d", &testcase);
	getchar();
	int alphabetFreq = 26;
	char* alphabet = (char*)malloc(sizeof(char) * alphabetFreq);
	for (int i = 0; i < alphabetFreq; i++)
		alphabet[i] = 'a' + i;
	encodearray = (encodeArray*)malloc(sizeof(encodearray) * codes_sum);
	for (int i = 0; i < testcase; i++) {
		encodearray[i].codes = (int*)malloc(sizeof(encodeArray) * testcase);
	}
	char* string = (char*)malloc(sizeof(char) * testcase);
	makeNewHuffmanTree(freq, ch_list, T);
	for (int i = 0; i < testcase; i++)
		scanf(" %c", &string[i]);

	char tmp;
	int temper;
	int geti = 0;
	int* huffmanEncode = (int*)malloc(sizeof(int) * (codes_sum * 4));
	int size = 0;
	int realsum = 0;
	while (geti < testcase) {
		for (int i = 0; i < testcase; i++) {
			if (encodearray[i].ch == string[geti]) {
				for (int k = 0; k < encodearray[i].codestop; k++) {
					huffmanEncode[size++] = (encodearray[i].codes)[k];
				}
				realsum += encodearray[i].codestop;
				break;
			}
		}
		geti++;
	}

	printf("허프만코드 암호화결과: ");
	for (int i = 0; i < realsum; i++)
		printf("%d", huffmanEncode[i]);
	printf("\n");

	printf("\n---------------복호화-----------------\n");
	scanf("%d", &size);
	getchar();

	char* decoding = (char*)malloc(sizeof(char) * (size + 1));


	for (int i = 0; i < size; i++) {
		scanf("%c", &decoding[i]);
	}

	printf("\n복호화 결과: ");
	TreeNode* temp = huffmanTree;
	for (int i = 0; i < size; i++) {
		if (decoding[i] == '1') {
			temp = temp->left;
			if ((temp->left == NULL) && (temp->right == NULL)) {
				printf("%c", temp->ch);
				temp = huffmanTree;
			}
		}
		else if(decoding[i] == '0'){
			temp = temp->right;
			if ((temp->left == NULL) && (temp->right == NULL)) {
				printf("%c", temp->ch);
				temp = huffmanTree;
			}
		}
	}
	printf("\n");
	
	return 0;
}