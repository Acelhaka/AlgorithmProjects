/************************************************************
*				Amarilda Celhaka							*
*				Project #3									*
*				CS 3130										*
*				Dr. Galina									*
*				Due Date: 11/24/2018						*
*	Description:  Operation of binary search tree			*
*	Inserting elements on a binary search tree, displaying	*
*	the results using inOrder, postOrder and preOrder		*
*	traversals, writing a tree-search function to search	*
*	for certain keys and writing a function to delete nodes *
*************************************************************/


#include "stdafx.h"
#include <iostream>
using namespace std;

struct TreeNode
{
	int key;  
	TreeNode *left, *right; //pointer that will point on the left or the right node
};

TreeNode *root;
//function prototypes
void insert(TreeNode *&nodePtr, TreeNode *&newNode);
void treeInsert(int arrayEl);
void inOrder(TreeNode *nodePtr);
void inOrder();
void postOrder(TreeNode *nodePtr);
void postOrder();
void preOrder(TreeNode *nodePtr);
void preOrder();
bool treeSearch(int num);
void search(int num);
struct TreeNode * treeSucessor(TreeNode *&node);
struct TreeNode* treeDelete(TreeNode *&root, int key);
int main()
{
	cout << "*************************************************************"<< endl;
	cout << " Project #3 " << endl;
	cout << " Amarilda Celhaka " << endl;
	cout << " Description:  Operation of binary search tree			" << endl;
	cout << " Inserting elements on a binary search tree, displaying	" << endl;
	cout << " the results using inOrder, postOrder and preOrder		" << endl;
	cout << " traversals, writing a tree - search function to search	" << endl;
	cout << " for certain keys and writing a function to delete nodes " << endl;
	cout << "*************************************************************\n\n" << endl;

	cout << "Array of the elements to build a binary search tree: " << endl;
	cout << "{ 30, 10, 45, 38, 20, 50, 25, 33, 8, 12 }\n\n" << endl;

	//array of elements given 
	int array[] = { 30, 10, 45, 38, 20, 50, 25, 33, 8, 12 };
	 
	for (int i = 0; i < sizeof(array)/4; i++)
	{	
		//inserting each of the area on the tree;
		treeInsert(array[i]); 
	}
	cout << "\nTREE-INSERT\n" << endl;
	cout << "In-order traversal of the binary tree: " << endl;
	inOrder(); //calling inOrder to display in order traversal of the binary tree

	cout << "\n\nPost-order traversal of the binary tree: " << endl;
	postOrder();//calling postOrder to display post order traversal of the binary tree

	cout << "\n\nPre-order traversal of the binary tree: " << endl;
	preOrder(); //calling preOrder to display pre order traversal of the binary tree

	cout << "\n\n********************************************************\n" << endl;
	cout << "TREE-SEARCH\n" << endl;
	cout << "\nSearching for  the key 38..." << endl;
	cout << "Sequence of the nodes examined:" << endl;
	//calling function search to look for the key 9 and will display a message if found or not
	search(38);  

	cout << "\n\nSearching for  the key 9..." << endl;
	cout << "Sequence of the nodes examined: " << endl;
	//calling function search to look for the key 9 and will display a message if found or not
	search(9);  
	


	cout << "\n\n********************************************************\n" << endl;
	cout << "TREE-DELETE\n" << endl;

	cout << "Deleting the node with key 10...\n" << endl;
	cout << "Loading...\n" << endl;
	//calling function treeDelete to delete key 38
	treeDelete(root, 10);

	//calling inOrder to display in order traversal of the new binary tree
	cout << "In order traversal of the binary tree: " << endl;
	inOrder();

	//calling postOrder to display in order traversal of the binary tree
	cout << "\n\nPost order traversal of the binary tree: " << endl;
	postOrder();

	//calling preOrder to display in order traversal of the binary tree
	cout << "\n\nPre order traversal of the binary tree: " << endl;
	preOrder();

	cout << endl << endl;
	
	system("Pause");
   return 0;
}



/*TreeInsert function will create a new node for each element it will take*/
void treeInsert( int arrayEl) 
{
	TreeNode * newNode = nullptr;

	//create a new node and store value in it
	newNode = new TreeNode; 
	newNode->key = arrayEl;
	newNode->left = newNode->right = nullptr;
	//calling insert node that will place the new element on the right position
	insert(root, newNode);

}

/***************************************************************************
*Insert- function will place the element of the array in the right position*
* to the right if the elements are greater than the key value, or to the   *
* left if smaller, or will create a new node if the nodePtr is pointing to *
* NULL																	   *
****************************************************************************/
void insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
	if (nodePtr == nullptr)
	{
		nodePtr = newNode;
	}

	else if (newNode->key < nodePtr->key)
	{
		//calling insert function to create a new node pointing to the left
		insert(nodePtr->left, newNode);
	}
	else
	{
		//calling insert function to create a new node pointing to the right
		insert(nodePtr->right, newNode);
	}
}


/******************************************************
* inOrder function will display the traversals of the *
* binary tree   in order =>>> left - root - right     * 
*******************************************************/
void inOrder(TreeNode *nodePtr)
{
	//left - root - right
	if (nodePtr)
	{
		inOrder(nodePtr->left);
		
		cout << nodePtr->key << " ";

		inOrder(nodePtr->right);
	}
}



void inOrder()
{
	inOrder(root);
}


/********************************************************
* postOrder function will display the traversals of the *
* binary tree post order =>>> root - left - right       *
*********************************************************/
void postOrder(TreeNode *nodePtr)
{
	//root - left -right
	if (nodePtr)
	{
		cout << nodePtr->key << " ";

		postOrder(nodePtr->left);

		postOrder(nodePtr->right);
	}
}


void postOrder()
{
	postOrder(root);
}


/********************************************************
* preOrder function will display the traversals of the  *
* binary tree pre order =>>> left - right - root        *
*********************************************************/
void preOrder(TreeNode *nodePtr)
{

	//left-right-root
	if (nodePtr)
	{
		preOrder(nodePtr->left);
		
		preOrder(nodePtr->right);

		cout << nodePtr->key << " ";
	}
}


void preOrder()
{
	preOrder(root);
}


/********************************************************
* treeSearch function will traverse the BST and return  *
* true if it finds the keyValue and returns false if not*
*********************************************************/
bool treeSearch(int keyValue)
{
	TreeNode *nodePtr = root;

	//traverse the array until no more values, point to NULL
	while (nodePtr)
	{
		//if value found return true
		if (nodePtr->key == keyValue)
		{
			cout << nodePtr->key << " ";
			return true;
		}
		//if keyValue is less than node key, traverse through left subtree
		else if (keyValue < nodePtr->key)
		{
			cout << nodePtr->key << " ";
			nodePtr = nodePtr->left;
		}
		//if keyValue is greater than node key, traverse through right subtree
		else
		{
			cout << nodePtr->key << " ";
			nodePtr = nodePtr->right;
			
		}
	}
	return false;
}

/*****************************************
*search function displays the message if *
* node found or not                      *
******************************************/
void search(int keyValue)
{
	if (treeSearch(keyValue))
	{
		cout << "\nKey " << keyValue << " was found in the tree" << endl;
	}
	else
	{
		cout << "\nKey " << keyValue << " was not found in the tree" << endl;
	}
}


/**************************************************
*tree Successor will return the tree successor	  *
* the smallest element of the right subtree which *
* is positioned on the left most position of the  *
* right substree								  *
***************************************************/

struct TreeNode * treeSucessor(TreeNode *&node)
{

	//succesorr is pointing to right substree
	TreeNode *successor = node->right;
	
	while (successor->left != NULL)
	{
		successor = successor->left;
	}
	return successor;
}



/********************************************************************
*TreeDelete function will delete the keyValue, it will walk through	*
* each subtree until it finds the key and will delete,				*
* replacing the keyValue with the left key, right key or tree		*
* successor depending on how many children it has					*
*********************************************************************/

struct TreeNode *treeDelete( TreeNode *&nodePtr, int keyValue)
{
 
	if (nodePtr == NULL)
	{
		return nodePtr;
	}
	//go through left subtree if keyNode is greater than keyValue
	if (keyValue < nodePtr->key)
	{
		nodePtr->left = treeDelete(nodePtr->left, keyValue);
	}
	//go through right subtree if keyNode is less than keyValue
	else if (keyValue > nodePtr->key)
	{
		nodePtr->right = treeDelete(nodePtr->right, keyValue);
	}
	//if found the keyValue check how many children it has, left or right node
	// pointing to null or not
	else
	{
		//if left node is null, make the right child a root for the subtree
		if (nodePtr->left == NULL)
		{
			struct TreeNode *temp = nodePtr->right;
			delete nodePtr;
			return temp;
		}

		//if right node is null, make the left child a root for the subtree
		else if (nodePtr->right == NULL)
		{
			struct TreeNode *temp = nodePtr->left;
			delete nodePtr;
			return temp;
		}
		//if it has two children make the treeSuccessor the root for the subtree
		struct TreeNode* tempNodePtr = treeSucessor(nodePtr);
		nodePtr->key = tempNodePtr->key;
		nodePtr->right = treeDelete(nodePtr->right, tempNodePtr->key);
	}
	return nodePtr;
}