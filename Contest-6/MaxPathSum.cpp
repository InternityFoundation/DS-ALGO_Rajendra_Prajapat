#include <bits/stdc++.h> 
using namespace std; 

typedef struct Node { 
	int key; 
	Node *left;
    Node *right; 
}node; 

node* newNode(int key) 
{ 
	node* temp=new node; 
	temp->key = key; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

int MaxPathSumU(node *root, int& ans) 
{ 
	if (root == NULL)	 
		return 0; 

	int currSum = root->key + MaxPathSumU(root->left, ans) + MaxPathSumU(root->right, ans); 

	ans = max(ans, currSum); 
	return currSum; 
} 

int MaxPathSum(node *root) 
{ 
	if (root == NULL)	 
		return 0; 
	
	int ans = INT_MIN;  
	MaxPathSumU(root, ans); 
	return ans; 
} 

int main() 
{ 
	Node* root = newNode(-10); 
	root->left = newNode(9); 
	root->right = newNode(20); 
	root->right->left = newNode(15); 
	root->right->right = newNode(7); 

	cout << MaxPathSum(root); 
	return 0; 
} 



//ref: https://www.geeksforgeeks.org/find-largest-subtree-sum-tree/