/**
RBTnode.cpp
Red Black Tree Node class declaration and function implementations.
This class is used to store nodes to form a binary search tree.

@author Charles Forrest
@version 1.0 03/15/2015
*/

#include "RBTNode.h"
#include "RBTFunctions.h"

/*
* Constructor
*/
RBTNode::RBTNode()
{
	parent = NULL;
	leftChild = NULL;
	rightChild = NULL;
	color = RED;
	key = -99;
}

/*
* Destructor
*/
RBTNode::~RBTNode()
{

}

/*
* This function is used to check that a given node, if red,
* has two black children
*
* @return BOOL true or false if the property holds
*/
BOOL RBTNode::checkProperty4()
{
	BOOL retVal = TRUE;

	if (color == RED)
	{
		//if either the left or right child are red, property 4 is broken
		if (leftChild != NULL && leftChild->color == RED)
		{
			return FALSE;
		}

		if (rightChild != NULL && rightChild->color == RED)
		{
			return FALSE;
		}
	}
	
	//if we can continue on, do so recursively
	if (leftChild != NULL)
	{
		retVal = leftChild->checkProperty4();

		if (retVal == FALSE)
		{
			return FALSE;
		}
	}

	//if we can continue on, do so recursively
	if (rightChild != NULL)
	{
		retVal = rightChild->checkProperty4();

		if (retVal == FALSE)
		{
			return FALSE;
		}
	}

	//else return true
	return retVal;
}