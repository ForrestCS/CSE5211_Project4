/**
RBTFunctions.h
Red Black Tree Node class declaration and function implementations.
This class is used to store nodes to form a binary search tree.

@author Charles Forrest
@version 1.0 03/15/2015
*/

#ifndef RBTFUNCTIONS_H
#define RBTFUNCTIONS_H

#include "RBTNode.h"

/* @brief Function to left rotate a node rotateNode to the left */
void LeftRotate(RBTNode **Root, RBTNode *rotateNode);

/* @brief Function to right rotate a node rotateNode to the right */
void RightRotate(RBTNode **Root, RBTNode *rotateNode);

/* @brief Function to insert a node z into the Root tree */
void RBInsert(RBTNode **Root, RBTNode *z);

/* @brief Function to fix-up a red black tree root after insertion */
void RBInsertFixUp(RBTNode **Root, RBTNode *z);

/* @brief Function to swap a node u and v */
void RBTransplant(RBTNode **Root, RBTNode *u, RBTNode *v);

/* @brief Function to delete a node z from tree root */
void RBDelete(RBTNode **Root, RBTNode *z);

/* @brief Function to fix-up a red black tree root after deletion */
void RBDeleteFixUp(RBTNode **Root, RBTNode *z, RBTNode *parent, BOOL leftNode);

/* @brief Function to find the max-value node of a specified tree */
RBTNode *TreeMaximum(RBTNode *searchNode);

/* @brief Function to find the min-value node of a specified tree */
RBTNode *TreeMinimum(RBTNode *searchNode);

/* @brief Function to find the key-value node of a specified tree */
RBTNode *TreeSearch(RBTNode *searchNode, int key);

/* @brief Function to find the next node of a specified tree */
RBTNode *Successor(RBTNode *searchNode);

/* @brief Function to find the previous node of a specified tree */
RBTNode *Predeccessor(RBTNode *searchNode);

/* @brief Function to the specified tree in order */
void printNodeTree(RBTNode *subtreeNode);

/* @brief Function to the specified tree in pre-order */
void printRootLRNodeTree(RBTNode *subtreeNode);

/* @brief Function to count and verify root->leaf black node count of subtreeNode  */
BOOL RBTBlackNodeCounter(RBTNode *subtreeNode, int blackNumber, int *pathCount);

#endif