#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;

} TreeNode;

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key)
{
	if (node == NULL) return new_node(key);
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	return node;
}

void binary_search_tree_inorder(TreeNode* root) {
	if (root == NULL) return;
	binary_search_tree_inorder(root->left);
	printf("[%d] ", root->key);	
	binary_search_tree_inorder(root->right);
}

int main(void) {
	int list[11] = { 11,3,4,1,56,5,6,2,98,32,23 };
	TreeNode* root = NULL;

	root = insert_node(root, list[0]);

	for (int i = 1; i < 11; i++)
		insert_node(root, list[i]);

	binary_search_tree_inorder(root);
}
