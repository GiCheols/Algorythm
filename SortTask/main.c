#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define BUCKETS 10
#define DIGITS 5

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_SIZE];
	int heap_size;
}HeapType;

typedef struct {
	int queue[MAX_SIZE];
	int front, rear;
} QueueType;

int list[MAX_SIZE] = { 0 };
int sorted[MAX_SIZE]; // 추가 공간이 필요

void Print(int list[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf(" %d ", list[i]);
	printf("\n");
}

void selection_sort_O(int list[], int n) //선택정렬[오름버젼]
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
		Print(list, n);
	}
	printf("\n\n↓  [선택] 정렬 오름차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [선택] 정렬 오름차순 버젼 결과  ↑\n\n\n");
}

void selection_sort_N(int list[], int n) //선택정렬[내림버젼]
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) // 최소값 탐색
			if (list[j] > list[least]) least = j;
		SWAP(list[i], list[least], temp);
		Print(list, n);
	}
	printf("\n\n↓  [선택] 정렬 내림차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [선택] 정렬 내림차순 버젼 결과  ↑\n\n\n");
}

void insertion_sort_O(int list[], int n) // 삽입 정렬 오름차순 버젼  
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; // 레코드의 오른쪽 이동
		list[j + 1] = key;
		Print(list, n);
	}
	printf("\n\n↓  [삽입] 정렬 오름차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [삽입] 정렬 오름차순 버젼 결과  ↑\n\n\n");
}

void insertion_sort_N(int list[], int n) // 삽입 정렬 내림차순 버젼
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] < key; j--) //key가 더 커야함
			list[j + 1] = list[j]; // 레코드의 오른쪽 이동
		list[j + 1] = key;
		Print(list, n);
	}
	printf("\n\n↓  [삽입] 정렬 내림차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [삽입] 정렬 내림차순 버젼 결과  ↑\n\n\n");
}

void bubble_sort_O(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) // 앞뒤의 레코드를 비교한 후 교체
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		Print(list, n);
	}
	printf("\n\n↓  [버블] 정렬 오름차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [버블] 정렬 오름차순 버젼 결과  ↑\n\n\n");
}

void bubble_sort_N(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) // 앞뒤의 레코드를 비교한 후 교체
			if (list[j] < list[j + 1]) //이거바꾸었음
				SWAP(list[j], list[j + 1], temp);
		Print(list, n);
	}
	printf("\n\n↓  [버블] 정렬 내림차순 버젼 결과  ↓\n\n");
	for (i = 0; i < n; i++) {
		printf(" %d ", list[i]);
	}
	printf("\n\n↑  [버블] 정렬 내림차순 버젼 결과  ↑\n\n\n");
}

void merge(int list[], int left, int mid, int right, int n, char select)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	if (select == 'i')
	{
		while (i <= mid && j <= right)
		{
			if (list[i] <= list[j])
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
	}
	if (select == 'd')
	{
		while (i <= mid && j <= right)
		{
			if (list[i] >= list[j])
				sorted[k++] = list[i++];
			else
				sorted[k++] = list[j++];
		}
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void merge_sort(int list[], int left, int right, int n, char select)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid, n, select);
		merge_sort(list, mid + 1, right, n, select);
		merge(list, left, mid, right, n, select);
	}
}

void quick_sort(int list[], int left, int right, int n, char select)
{
	int q;
	if (left < right)
	{
		q = partition(list, left, right, n, select);
		quick_sort(list, left, q - 1, n, select);
		quick_sort(list, q + 1, right, n, select);
	}
}

int partition(int list[], int left, int right, int n, char select)
{
	int pivot, temp;
	int low, high, i;

	low = left;
	high = right + 1;
	pivot = list[left];

	if (select == 'i') // 오름차순 정렬
	{
		do {
			do
				low++;
			while (low <= right && list[low] < pivot);
			do
				high--;
			while (high >= left && list[high] > pivot);
			if (low < high)
			{
				SWAP(list[low], list[high], temp);
				for (i = 0; i < n; i++)
					printf("%d ", list[i]);
				printf("\n");
			}
		} while (low < high);
		SWAP(list[left], list[high], temp);
		for (i = 0; i < n; i++)
			printf("%d ", list[i]);
		printf("\n");
	}
	else if (select == 'd') // 내림차순 정렬
	{
		do {
			do
				low++;
			while (low <= right && list[low] > pivot);
			do
				high--;
			while (high >= left && list[high] < pivot);
			if (low < high)
			{
				SWAP(list[low], list[high], temp);
				for (i = 0; i < n; i++)
					printf("%d ", list[i]);
				printf("\n");
			}
		} while (low < high);
		SWAP(list[left], list[high], temp);
		for (i = 0; i < n; i++)
			printf("%d ", list[i]);
		printf("\n");
	}
	return high;
}

void inc_insertion_sort_O(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
		Print(list, last + 1);
	}
}

void inc_insertion_sort_N(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key > list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
		Print(list, last + 1);
	}
}

void shell_sort_O(int list[], int n) // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++) // 부분 리스트의 개수는 gap
			inc_insertion_sort_O(list, i, n - 1, gap);
	}
}

void shell_sort_N(int list[], int n) // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++) // 부분 리스트의 개수는 gap
			inc_insertion_sort_N(list, i, n - 1, gap);
	}
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i].key = item;
}

int delete_max_heap(HeapType* h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1].key;
	temp = h->heap[(h->heap_size)--].key;
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent].key = temp;
	return item;
}

void insert_min_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i].key = item;
}

int delete_min_heap(HeapType* h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1].key;
	temp = h->heap[(h->heap_size)--].key;
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent].key = temp;
	return item;
}

void heap_sort(int list[], int n, char select)
{
	int i, s;
	HeapType h;

	init(&h);

	if (select == 'i')
	{
		for (i = 0; i < n; i++)
		{
			insert_max_heap(&h, list[i]);
		}
		for (i = (n - 1); i >= 0; i--)
		{
			list[i] = delete_max_heap(&h);
			for (s = 0; s < n; s++) // 중간과정 프린트
				printf("%d ", list[s]);
			printf("\n");
		}
		printf("\n\n↓  [히프] 정렬 오름차순 버젼 결과  ↓\n\n");

		for (i = 0; i < n; i++) {
			printf(" %d ", list[i]);
		}
		printf("\n\n↑  [히프] 정렬 오름차순 버젼 결과  ↑\n\n\n");
	}
	else if (select == 'd')
	{
		for (i = 0; i < n; i++)
		{
			insert_min_heap(&h, list[i]);
		}
		for (i = (n - 1); i >= 0; i--)
		{
			list[i] = delete_min_heap(&h);
			for (s = 0; s < n; s++) // 중간과정 프린트
				printf("%d ", list[s]);
			printf("\n");
		}
		printf("\n\n↓  [히프] 정렬 내림차순 버젼 결과  ↓\n\n");

		for (i = 0; i < n; i++) {
			printf(" %d ", list[i]);
		}
		printf("\n\n↑  [히프] 정렬 내림차순 버젼 결과  ↑\n\n\n");
	}
}

void binit(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_SIZE == q->front);
}

void enqueue(QueueType* q, int item)
{
	if (is_full(q))
	{
		printf("큐가 포화상태입니다! \n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->queue[q->rear] = item;
}

int dequeue(QueueType* q)
{
	if (is_empty(q))
	{
		printf("큐가 공백상태입니다! \n");
		return 0;
	}
	q->front = (q->front + 1) % MAX_SIZE;
	return q->queue[q->front];
}

void radix_sort(int list[], int n, int count, char select)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		binit(&queues[b]);
	for (d = 0; d < count; d++)
	{
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		if (select == 'i') // 오름차순 정렬
		{
			for (b = i = 0; b < BUCKETS; b++)
				while (!is_empty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
		}
		else if (select == 'd') // 내림차순 정렬
		{
			for (b = count, i = 0; b > 0; b--)
				while (!is_empty(&queues[b]))
					list[i++] = dequeue(&queues[b]);
		}
		factor *= 10;
		for (i = 0; i < n; i++)
			printf("%d ", list[i]);
		printf("\n");
	}
	if (select == 'i')
	{
		printf("\n\n↓  [기수] 정렬 오름차순 버젼 결과  ↓\n\n");

		for (i = 0; i < n; i++) {
			printf(" %d ", list[i]);
		}
		printf("\n\n↑  [기수] 정렬 오름차순 버젼 결과  ↑\n\n\n");
	}
	else if (select == 'd')
	{
		printf("\n\n↓  [기수] 정렬 내림차순 버젼 결과  ↓\n\n");

		for (i = 0; i < n; i++) {
			printf(" %d ", list[i]);
		}
		printf("\n\n↑  [ 기수] 정렬 내림차순 버젼 결과  ↑\n\n\n");
	}
	else
		printf("차순 입력 에러 입니다. \n");
}

int ascending(const void* arg1, const void* arg2) {
	if (*(int*)arg1 > *(int*)arg2)
		return 1;
	else if (*(int*)arg1 == *(int*)arg2)
		return 0;
	else
		return -1;
}

int descending(const void* arg1, const void* arg2) {
	if (*(int*)arg1 < *(int*)arg2)
		return 1;
	else if (*(int*)arg1 > *(int*)arg2)
		return -1;
	else
		return 0;
}

void main()
{
	int i, count = 0;
	char num[MAX_SIZE] = { 'a' };
	char sel = 'a', sel2 = 'a';
	int radix_count = 0;

	while (sel != 'x') {
		printf("===========================================\n");
		printf("[s] [선택]정렬 \n");
		printf("[i] [삽입]정렬 \n");
		printf("[b] [버블]정렬 \n");
		printf("[l] [ 쉘 ]정렬 \n");
		printf("[h] [히프]정렬 \n");
		printf("[m] [합병]정렬 \n");
		printf("[q] [ 퀵 ]정렬 \n");
		printf("[r] [기수]정렬 \n");
		printf("[t] [ 퀵 ]정렬(라이브러리 함수) \n");
		printf("[x] 프로그램 종료 \n");
		printf("===========================================\n");
		printf("무엇을 실행할까요?? ");
		scanf("%c", &sel);
		getchar();
		switch (sel) {
		case 's':
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				fflush(stdin);
				printf("[선택] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				selection_sort_N(list, i);
			}
			else if (sel2 == 'i') {
				selection_sort_O(list, i);
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'i':
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				fflush(stdin);
				printf("[삽입] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				insertion_sort_N(list, i);
			}
			else if (sel2 == 'i') {
				insertion_sort_O(list, i);
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'b':
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[버블] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				bubble_sort_N(list, i);
			}
			else if (sel2 == 'i') {
				bubble_sort_O(list, i);
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'm':
			count = 0;
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[합병] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				count++;
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				merge_sort(list, 0, i - 1, i, sel2);
				printf("\n\n↓  [합병] 정렬 내림차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [합병] 정렬 내림차순 버젼 결과  ↑\n\n\n");
			}
			else if (sel2 == 'i') {
				merge_sort(list, 0, i - 1, i, sel2);
				printf("\n\n↓  [합병] 정렬 오름차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [합병] 정렬 오름차순 버젼 결과  ↑\n\n\n");
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'h':
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				fflush(stdin);
				printf("[히프] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				heap_sort(list, i, sel2);
			}
			else if (sel2 == 'i') {
				heap_sort(list, i, sel2);
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'q':
			count = 0;
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[ 퀵 ] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				count++;
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				quick_sort(list, 0, i - 1, i, sel2);
				printf("\n\n↓  [ 퀵 ] 정렬 내림차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 퀵 ] 정렬 내림차순 버젼 결과  ↑\n\n\n");
			}
			else if (sel2 == 'i') {
				quick_sort(list, 0, i - 1, i, sel2);
				printf("\n\n↓  [ 퀵 ] 정렬 오름차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 퀵 ] 정렬 오름차순 버젼 결과  ↑\n\n\n");
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'r':
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			printf("자리 수 입력 : ");
			scanf("%d", &radix_count);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[기수] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				count++;
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				radix_sort(list, i, radix_count, sel2);
			}
			else if (sel2 == 'i') {
				radix_sort(list, i, radix_count, sel2);
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;


		case 'l':
			count = 0;
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[ 쉘 ] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				count++;
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				shell_sort_N(list, i);
				printf("\n\n↓  [ 쉘 ] 정렬 내림차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 쉘 ] 정렬 내림차순 버젼 결과  ↑\n\n\n");
			}
			else if (sel2 == 'i') {
				shell_sort_O(list, i);
				printf("\n\n↓  [ 쉘 ] 정렬 오름차순 버젼 결과  ↓\n\n");

				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 쉘 ] 정렬 오름차순 버젼 결과  ↑\n\n\n");
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;

		case 't':
			count = 0;
			printf("내림차순은 d번, 오름차순은 i번 선택 :");
			scanf("%c", &sel2);
			getchar();
			for (i = 0; i < MAX_SIZE; i++) {
				printf("[ 퀵 ] 정렬입니다. 현재 %d번째입력[종료는 = 입력] : ", i + 1);
				count++;
				gets(num);
				list[i] = atoi(num);
				if ((strcmp(num, "=")) == 0) {
					printf("입력 Stop! \n");
					break;
				}
			}
			if (sel2 == 'd') {
				qsort(list, i, sizeof(int), descending);
				printf("\n\n↓  [ 퀵 ] 정렬(라이브러리) 내림차순 버젼 결과  ↓\n\n");
				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 퀵 ] 정렬(라이브러리) 내림차순 버젼 결과  ↑\n\n\n");
			}
			if (sel2 == 'i') {
				qsort(list, i, sizeof(int), ascending);
				printf("\n\n↓  [ 퀵 ] 정렬(라이브러리) 오름차순 버젼 결과  ↓\n\n");
				for (i = 0; i < count - 1; i++) {
					printf(" %d ", list[i]);
				}
				printf("\n\n↑  [ 퀵 ] 정렬(라이브러리) 오름차순 버젼 결과  ↑\n\n\n");
			}
			else
				printf("\n차순 선택을 잘못하셨습니다. \n");
			break;

		case 'x':
			printf("프로그램을 종료합니다 ");
			break;
		}
		printf("아무 키나 입력해 다른 정렬 찾아보기 >> ");
		scanf("%c", &i);
		system("cls");
	}
}