/**
RBTnode.cpp
Red Black Tree Node class declaration and function implementations.
This class is used to store nodes to form a binary search tree.

@author Charles Forrest
@version 1.0 03/15/2015
*/

#include "RBTFunctions.h"

/*
* This function is used to left rotate the given rotateNode
*
* @param Root reference to the main tree
* @param rotateNode node to rotate to the left
* @return N/A
*/
void LeftRotate(RBTNode **Root, RBTNode *rotateNode)
{
	RBTNode *yNode = rotateNode->rightChild;

	//turn y's left tree into x's right subtree
	rotateNode->rightChild = yNode->leftChild;

	if (yNode->leftChild != NULL)
	{
		yNode->leftChild->parent = rotateNode;
	}

	//link x's parent to y's parent
	yNode->parent = rotateNode->parent;

	//if rotate is the current root, make y the new root
	if (rotateNode->parent == NULL)
	{
		*Root = yNode;
	}
	//assign parent based on location
	else if (rotateNode == rotateNode->parent->leftChild)
	{
		rotateNode->parent->leftChild = yNode;
	}
	else
	{
		rotateNode->parent->rightChild = yNode;
	}

	yNode->leftChild = rotateNode;
	rotateNode->parent = yNode;
}

/*
* This function is used to right rotate the given rotateNode
*
* @param Root reference to the main tree
* @param rotateNode node to rotate to the right
* @return N/A
*/
void RightRotate(RBTNode **Root, RBTNode *rotateNode)
{
	RBTNode *yNode = rotateNode->leftChild;

	//turn y's right tree into x's left subtree
	rotateNode->leftChild = yNode->rightChild;

	if (yNode->rightChild != NULL)
	{
		yNode->rightChild->parent = rotateNode;
	}

	//link x's parent to y's parent
	yNode->parent = rotateNode->parent;

	//if rotate is the current root, make y the new root
	if (rotateNode->parent == NULL)
	{
		*Root = yNode;
	}
	else if (rotateNode == rotateNode->parent->leftChild)
	{
		rotateNode->parent->leftChild = yNode;
	}
	else
	{
		rotateNode->parent->rightChild = yNode;
	}

	yNode->rightChild = rotateNode;
	rotateNode->parent = yNode;
}

/*
* This function is used to insert the node z into the tree
* given by root.
*
* @param Root reference to the main tree
* @param z node to add to the main tree
* @return N/A
*/
void RBInsert(RBTNode **Root, RBTNode *z)
{
	RBTNode *yNode = NULL;
	RBTNode *xNode = *Root;

	//search for the position for the node by key
	while (xNode != NULL)
	{
		yNode = xNode;

		if (z->key < xNode->key)
		{
			xNode = xNode->leftChild;
		}
		else
		{
			xNode = xNode->rightChild;
		}
	}

	//make the parent of this spot the new nodes parent
	z->parent = yNode;

	if (yNode == NULL)
	{
		*Root = z;
	}
	else if (z->key < yNode->key)
	{
		yNode->leftChild = z;
	}
	else
	{
		yNode->rightChild = z;
	}

	//new node has no children and is red going into fixup
	z->leftChild = NULL;
	z->rightChild = NULL;
	z->color = RED;
	RBInsertFixUp(Root, z);
}

/*
* This function is used to fix the tree given by
* root after an insertion of a new node.
*
* @param Root reference to the main tree
* @param z node to add to the main tree
* @return N/A
*/
void RBInsertFixUp(RBTNode **Root, RBTNode *z)
{
	RBTNode *yNode = NULL;

	while (z != *Root && z->parent->color == RED)
	{
		if ((z->parent != NULL) && z->parent == z->parent->parent->leftChild)
		{
			yNode = z->parent->parent->rightChild;

			//Case 1 - z's uncle y is red
			if (yNode != NULL && yNode->color == RED)
			{
				z->parent->color = BLACK;
				yNode->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//Case 2 - z's uncle y is black and z is a right child
				if (z == z->parent->rightChild)
				{
					z = z->parent;
					LeftRotate(Root, z);
				}

				//Case 3 - z's uncle y is black and z is a left child
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotate(Root, z->parent->parent);
			}
		}
		else if (z->parent != NULL)
		{
			yNode = z->parent->parent->leftChild;

			//Case 1 - z's uncle y is red
			if (yNode != NULL && yNode->color == RED)
			{
				z->parent->color = BLACK;
				yNode->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//Case 2 - z's uncle y is black and z is a right child
				if (z == z->parent->leftChild)
				{
					z = z->parent;
					RightRotate(Root, z);
				}

				//Case 3 - z's uncle y is black and z is a left child
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(Root, z->parent->parent);
			}
		}
	}

	//Make sure the root is black
	(*Root)->color = BLACK;
}

/*
* This function is used to swap the node u and node v
*
* @param Root reference to the main tree
* @param z node to add to the main tree
* @return N/A
*/
void RBTransplant(RBTNode **Root, RBTNode *u, RBTNode *v)
{
	//if u is root, make v the new root
	if (u->parent == NULL)
	{
		*Root = v;
	}

	//swap the points of u to v to remove u
	else if ((u != NULL) && u == u->parent->leftChild)
	{
		u->parent->leftChild = v;
	}
	else
	{
		u->parent->rightChild = v;
	}

	//swap the parents
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}

/*
* This function is used to delete a node z from the tree
* specified by root
*
* @param Root reference to the main tree
* @param z node to delete to the main tree
* @return N/A
*/
void RBDelete(RBTNode **Root, RBTNode *z)
{
	RBTNode *yNode;
	RBTNode *xNode;
	RBTNode *parentNode;
	BOOL leftNode = false;

	//if the node has less than two children, we can use it.
	//otherwise we have to find the successor
	if (z->leftChild == NULL || z->rightChild == NULL)
	{
		yNode = z;
	}
	else
	{
		yNode = Successor(z);
	}

	//if y has a left child, use it
	//otherwise just assign right child even if its NULL
	if (yNode->leftChild != NULL)
	{
		xNode = yNode->leftChild;
	}
	else
	{
		xNode = yNode->rightChild;
	}

	//assign xNode's parent as yNode if not NULL
	if (xNode != NULL)
	{
		xNode->parent = yNode->parent;
	}

	parentNode = yNode->parent;

	//if parent is false, we have the root
	if (yNode->parent == NULL)
	{
		*Root = xNode;
	}
	//if y's parent leftChild, then we have the left child
	//to delete
	else if (yNode == yNode->parent->leftChild)
	{
		yNode->parent->leftChild = xNode;
		leftNode = TRUE;
	}
	else
	{
		yNode->parent->rightChild = xNode;
		leftNode = FALSE;
	}

	//make sure y and z are matching before the call
	//to fixup
	if (yNode != z)
	{
		z->key = yNode->key;
	}

	//if the node we deleted was black, call fix up.
	//for a red node it doesnt matter
	if (yNode->color == BLACK)
	{
		RBDeleteFixUp(Root, xNode, parentNode, leftNode);
	}
}

/*
* This function is used to fix-up a tree after a recent
* deletion from the tree
*
* @param Root reference to the main tree
* @param z node to delete to the main tree
* @return N/A
*/
void RBDeleteFixUp(RBTNode **Root, RBTNode *z, RBTNode *parent, BOOL leftNode)
{
	RBTNode *tempDelete = new RBTNode;

	//if z is NULL, we can assume that the node deleted
	//has no children. Change to BLACK, which we revert afterwards
	if (z == NULL)
	{
		z = tempDelete;
		tempDelete = z;
		z->color = BLACK;
	}

	//This is to make sure we are not running this when the tree is just the root
	if (Successor(*Root) == NULL && Predeccessor(*Root) == NULL)
	{
		return;
	}

	//while z is not pointing to the root and has a black node
	while (z != *Root && z->color != RED)
	{
		RBTNode *wNode = NULL;

		//if we know we deleted the left node, proceed
		if (leftNode == TRUE)
		{
			wNode = parent->rightChild;

			//Case 1 - z's Sibling is Red
			if (wNode->color == RED)
			{
				wNode->color = BLACK;
				parent->color = RED;
				LeftRotate(Root, parent);
				wNode = parent->rightChild;
			}

			//Case 2 - z's sibling w is black and both children are black
			if ((wNode->leftChild == NULL) && (wNode->rightChild == NULL) ||
				(wNode->leftChild == NULL) && (wNode->rightChild->color == BLACK) ||
				(wNode->rightChild == NULL) && (wNode->leftChild->color == BLACK) ||
				wNode->leftChild->color == BLACK &&	wNode->rightChild->color == BLACK)
			{
				wNode->color = RED;
				z = parent;
				parent = z->parent;

				if ((parent != NULL) && (parent->leftChild != NULL) && z == parent->leftChild)
				{
					leftNode = TRUE;
				}
				else
				{
					leftNode = FALSE;
				}
			}
			//Case 3 - z's sibling w is black with left red and black right
			else
			{
				if ((wNode->rightChild == NULL) || wNode->rightChild->color == BLACK)
				{
					wNode->leftChild->color = BLACK;
					wNode->color = RED;
					RightRotate(Root, wNode);
					wNode = parent->rightChild;
				}

				//Case 4 - z's sibling w is black with a right child is red
				wNode->color = parent->color;
				parent->color = BLACK;

				if (wNode->rightChild != NULL)
				{
					wNode->rightChild->color = BLACK;
				}

				LeftRotate(Root, parent);
				z = *Root;
			}
		}
		//otherwise we deleted the right node
		else
		{
			wNode = parent->leftChild;

			//Case 1 - z's Sibling is Red
			if (wNode->color == RED)
			{
				wNode->color = BLACK;
				parent->color = RED;
				RightRotate(Root, parent);
				wNode = parent->leftChild;
			}

			//Case 2 - z's sibling w is black and both children are black
			if ((wNode->leftChild == NULL) && (wNode->rightChild == NULL) || 
				(wNode->leftChild == NULL) && (wNode->rightChild->color == BLACK) ||
				(wNode->rightChild == NULL) && (wNode->leftChild->color == BLACK) ||
				wNode->leftChild->color == BLACK &&	wNode->rightChild->color == BLACK)
			{
				wNode->color = RED;
				z = parent;
				parent = z->parent;

				if ((parent != NULL) && (parent->leftChild != NULL) && z == parent->leftChild)
				{
					leftNode = TRUE;
				}
				else
				{
					leftNode = FALSE;
				}
			}
			//Case 3 - z's sibling w is black with left red and black right
			else
			{
				if ((wNode->leftChild == NULL) || wNode->leftChild->color == BLACK)
				{
					wNode->rightChild->color = BLACK;
					wNode->color = RED;
					LeftRotate(Root, wNode);
					wNode = parent->leftChild;
				}

				//Case 4 - z's sibling w is black with a right child is red
				wNode->color = parent->color;
				parent->color = BLACK;

				if (wNode->leftChild != NULL)
				{
					wNode->leftChild->color = BLACK;
				}

				RightRotate(Root, parent);
				z = *Root;
			}
		}

	}

	//make z equal to black (cautionary) and delete our
	//allocated memory
	z->color = BLACK;
	delete(tempDelete);
}

/*
* This function is used to find the maximum tree node from
* the subtree starting at searchNode
*
* @param searchNode node to start the search at main tree
* @return searchNode maximum node from the starting searchNode
*/
RBTNode *TreeMaximum(RBTNode *searchNode)
{
	//search the right children until we find the max
	while (searchNode->rightChild != NULL)
	{
		searchNode = searchNode->rightChild;
	}

	return searchNode;
}

/*
* This function is used to find the minimum tree node from
* the subtree starting at searchNode
*
* @param searchNode node to start the search at main tree
* @return searchNode minimum node from the starting searchNode
*/
RBTNode *TreeMinimum(RBTNode *searchNode)
{
	//search the left children until we find the min
	while (searchNode->leftChild != NULL)
	{
		searchNode = searchNode->leftChild;
	}

	return searchNode;
}

/*
* This function is used to find the tree node with specified key
* from the subtree starting at searchNode
*
* @param searchNode node to start the search at main tree
* @param key key value to find in the subtree
* @return searchNode the node with the specified key, or NULL
*/
RBTNode *TreeSearch(RBTNode *searchNode, int key)
{
	//if searchNode is null or we are already at the node
	if (searchNode == NULL || key == searchNode->key)
	{
		return searchNode;
	}
	
	//otherwise, search the tree given its value
	if (key < searchNode->key)
	{
		return TreeSearch(searchNode->leftChild, key);
	}
	else
	{
		return TreeSearch(searchNode->rightChild, key);
	}
}

/*
* This function is used to find the tree node that is the successor
* of the node searchNode
*
* @param searchNode node to start the search at main tree
* @return auxNode the node succeeding searchNode
*/
RBTNode *Successor(RBTNode *searchNode)
{
	if (searchNode == NULL)
	{
		return NULL;
	}

	//find the minimum value of the right subtree if it exists
	if (searchNode->rightChild != NULL)
	{
		return TreeMinimum(searchNode->rightChild);
	}
	
	RBTNode *auxNode = searchNode->parent;

	//go up the tree to find the successor
	while (auxNode != NULL && searchNode == auxNode->rightChild)
	{
		searchNode = auxNode;
		auxNode = auxNode->parent;
	}

	return auxNode;
}

/*
* This function is used to find the tree node that is the predeccessor
* of the node searchNode
*
* @param searchNode node to start the search at main tree
* @return auxNode the node preceeding searchNode
*/
RBTNode *Predeccessor(RBTNode *searchNode)
{
	if (searchNode == NULL)
	{
		return NULL;
	}

	//find the max or tree if it exists
	if (searchNode->leftChild != NULL)
	{
		return TreeMaximum(searchNode->leftChild);
	}

	RBTNode *auxNode = searchNode->parent;

	//go up the tree to find the predeccesor
	while (auxNode != NULL && searchNode == auxNode->leftChild)
	{
		searchNode = auxNode;
		auxNode = auxNode->parent;
	}

	return auxNode;
}

/*
* This function is used to print the tree starting at
* subtreeNode
*
* @param subtreeNode node to start printing from
* @return N/A
*/
void printNodeTree(RBTNode *subtreeNode)
{
	char tempString[100];
	char colorString[6];

 	if (subtreeNode != NULL)
	{
		printNodeTree(subtreeNode->leftChild);

 		if (subtreeNode->color == RED)
		{
			sprintf_s(colorString, sizeof(colorString), "RED");
		}
		else
		{
			sprintf_s(colorString, sizeof(colorString), "BLACK");
		}

		sprintf_s(tempString, sizeof(tempString), "Node: color: %s key: %d\n",
			colorString, subtreeNode->key);
		printf("%s", tempString);

		printNodeTree(subtreeNode->rightChild);
	}
}

/*
* This function is used to print the tree in pre-order starting at
* subtreeNode
*
* @param subtreeNode node to start printing from
* @return N/A
*/
void printRootLRNodeTree(RBTNode *subtreeNode)
{
	char tempString[100];
	char colorString[6];

	if (subtreeNode != NULL)
	{
		if (subtreeNode->color == RED)
		{
			sprintf_s(colorString, sizeof(colorString), "RED");
		}
		else
		{
			sprintf_s(colorString, sizeof(colorString), "BLACK");
		}

		sprintf_s(tempString, sizeof(tempString), "Node: color: %s key: %d\n",
			colorString, subtreeNode->key);
		printf("%s", tempString);

		printRootLRNodeTree(subtreeNode->leftChild);
		printRootLRNodeTree(subtreeNode->rightChild);
	}
}

/*
* This function is used to determine if the root->leaf
* paths have the same black node count
*
* @param subtreeNode node to start the count at
* @param int current black node count
* @param int current path count
* @return retVal or T/F depending on if the black node counts match
*/
BOOL RBTBlackNodeCounter(RBTNode *subtreeNode, int blackNumber, int *pathCount)
{
	BOOL retVal = TRUE;

	//if we find a new black node, increment
	if ((subtreeNode != NULL) && subtreeNode->color == BLACK)
	{
		blackNumber++;
	}
	
	//if we are at the end, check the count to all other counts using reference
	if (subtreeNode->leftChild == NULL || subtreeNode->rightChild == NULL ||
		subtreeNode == NULL)
	{
		//if we got this path first, use it
		if (*pathCount == -1)
		{
			*pathCount = blackNumber;
		}
		else
		{
			//check vs the current reported path (recursive)
			if (blackNumber == *pathCount)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}

	//if we can continue on, keep going left
	if (subtreeNode->leftChild != NULL)
	{
		retVal = RBTBlackNodeCounter(subtreeNode->leftChild, blackNumber, pathCount);
	}

	//if we get false, return immediately.. no reason not to
	if (retVal == FALSE)
	{
		return FALSE;
	}

	//and keep going right recursive
	if (subtreeNode->rightChild != NULL)
	{
		retVal = RBTBlackNodeCounter(subtreeNode->rightChild, blackNumber, pathCount);
	}

	return retVal;
}