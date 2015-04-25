/**
RBTNode.h
Red Black Tree Node header file with function declarations.

@author Charles Forrest
@version 1.0 03/15/2014
*/

#ifndef RBTNODE_H
#define RBTNODE_H

#include <iostream>
#include <Windows.h>

enum COLOR{RED, BLACK};

class RBTNode
{
public:
	/* @brief Constructor */
	RBTNode();

	/* @brief Destructor */
	~RBTNode();

	/* @brief Pointer to the parent of the node */
	RBTNode *parent;

	/* @brief Pointer to the left child of the node */
	RBTNode *leftChild;

	/* @brief Pointer to the right child of the node */
	RBTNode *rightChild;

	/* @brief Color of the node (red or black) */
	int color;

	/* @brief Value of the node 0 to MAX_INT */
	int key;

	/* @brief Function used to check the nodes tree holds property 4 */
	BOOL checkProperty4();
};

#endif