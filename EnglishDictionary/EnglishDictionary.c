#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

//������ ����
typedef struct {
	char word[MAX_WORD_SIZE]; //key field
	char meaning[MAX_MEANING_SIZE];
}element;

//����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

/*
���� e1 < e2 ���, -1 ��ȯ
���� e1 == e2 ���, 0 ��ȯ
���� e1 > e2 ���, 1 ��ȯ
*/
int compare(element e1, element e2) { return strcmp(e1.word, e2.word); }

//���� Ž�� Ʈ�� ����Լ�
void display(TreeNode* p) {
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s : %s", p->key.word, p->key.meaning);
		display(p->right);
		printf(")");
	}
}

//���� Ž�� Ʈ�� Ž�� �Լ�
TreeNode* search(TreeNode* root, element key) {
	TreeNode* p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0)
			return p;
		else if (compare(key, p->key) < 0)
			p = p->left;
		else if (compare(key, p->key) > 0)
			p = p->right;
	}
	return p; //Ž�� �������� ��� NULL ��ȯ
}
TreeNode* newNode(element item) {
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	tmp->key = item;
	tmp->left = tmp->right = NULL;
	return tmp;
}
TreeNode* insertNode(TreeNode* node, element key) {
	//Ʈ���� �����̶�� ���ο� ��� ��ȯ
	if (node == NULL) return newNode(key);

	//�׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (compare(key, node->key) < 0)
		node->left = insertNode(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insertNode(node->right, key);
	//��Ʈ �����͸� ��ȯ
	return node;
}
TreeNode* minValueNode(TreeNode* node) {
	TreeNode* current = node;
	//�� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;
	return current;
}

//����Ž��Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� ���ο� ��Ʈ��带 ��ȯ�Ѵ�.
TreeNode* deleteNode(TreeNode* root, element key) {
	if (root == NULL) return root;

	//���� Ű�� ��Ʈ���� ������ ���� ����Ʈ���� �ִ� ����
	if (compare(key, root->key) < 0)
		root->left = deleteNode(root->left, key);
	//���� Ű�� ��Ʈ���� ũ�ٸ� ������ ����Ʈ���� �ִ� ����
	else if (compare(key, root->key) > 0)
		root->right = deleteNode(root->right, key);
	//Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		//ù ��°�� �� ��° ���: �ڽĳ�尡 ���ų� �ڽ� ��尡 �ϳ��� �ִ� ���
		if (root->left == NULL) {
			TreeNode* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			TreeNode* tmp = root->left;
			free(root);
			return tmp;
		}
		//�� ��°�� ���: �ڽĳ�尡 �� �� �ִ� ���
		TreeNode* tmp = minValueNode(root->right);

		//�߿� ��ȸ�� �İ��带 ����
		root->key = tmp->key;
		//�߿� ��ȸ�� �İ��带 ����
		root->right = deleteNode(root->right, tmp->key);
	}
	return root;
}

void help() {
	printf("\n**** i: �Է�, d: ����, s: Ž��, p: ���, q: ���� ****: ");
}


//���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷�
int main() {
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar(); //����Ű ����
		switch (command) {
		case 'i':
			printf("�ܾ�: ");
			gets_s(e.word, MAX_WORD_SIZE);
			printf("�ǹ�: ");
			gets_s(e.meaning, MAX_MEANING_SIZE);
			root = insertNode(root, e);
			break;
		case 'd':
			printf("�ܾ�: ");
			gets_s(e.word, MAX_WORD_SIZE);
			root = deleteNode(root, e);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("�ܾ�: ");
			gets_s(e.word, MAX_WORD_SIZE);
			tmp = search(root, e);
			if (tmp != NULL)
				//printf("�ǹ�: %s\n", e.meaning);
				printf("�ǹ�: %s\n", tmp->key.meaning);
			else
				printf("%s is not found!\n", e.word);
			break;
		}
	} while (command != 'q');
	return 0;
}