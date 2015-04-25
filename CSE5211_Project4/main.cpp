/**
main.cpp
Red Black Tree Node class main application. This program is uses our
implemented red black tree data structure and supporting functions to
insert and delete from a binary search tree.

@author Charles Forrest
@version 1.0 03/15/2015
*/

#include "RBTFunctions.h"

#define PRE_ORDER 1
#define IN_ORDER 0

int main()
{
	int inputRes = 0, currentInput = -1;
	int blackPathCount = -1;
	BOOL done = FALSE, failed = FALSE;
	RBTNode *root = NULL;

	//get node input until user specifies otherwise
	while (!done)
	{
		printf("Enter the positive values for nodes of the RBT, or negative to exit:\n");
		inputRes = scanf_s("%d", &currentInput);

		//verify input criteria
		if (currentInput < 0 || currentInput > INT_MAX || inputRes != 1)
		{
			printf("Invalid Integer\n");
			done = true;
			break;
		}

		//insert a new node into our tree based on key
		RBTNode *insertNode = new RBTNode;
		insertNode->key = currentInput;
		RBInsert(&root, insertNode);

#if PRE_ORDER
		printf("\nPre-Order Tree after Insertion:\n");
		printRootLRNodeTree(root);
#endif
#if IN_ORDER
		printf("\nIn-Order Tree after Insertion:\n");
		printNodeTree(root);
#endif

		if (root != NULL)
		{
			//check the RBT properties 4 and 5
			printf("\nProperty 4 is: ");
			printf(root->checkProperty4() ? "true" : "false");

			printf("\nProperty 5 is: ");
			blackPathCount = -1;
			printf(RBTBlackNodeCounter(root, 0, &blackPathCount) ? "true\n" : "false\n");

			//misc test outputs to test our functions
			printf("\nMax tree node is: %d\n", TreeMaximum(root)->key);
			printf("Min tree node is: %d\n", TreeMinimum(root)->key);
			printf("The root value is: %d\n", root->key);

			if (Successor(root) != NULL)
			{
				printf("The successor of root has value :%d\n", Successor(root)->key);
			}
			else
			{
				printf("Root does not have a successor\n");
			}

			if (Predeccessor(root) != NULL)
			{
				printf("The predecessor of root has value :%d\n\n", Predeccessor(root)->key);
			}
			else
			{
				printf("Root does not have a predeccesor\n\n");
			}
		}
	}

	//if the root is null, then there are no elements
	if (root != NULL)
	{
		done = false;

		while (!done)
		{
			printf("Enter a Node to delete or negative to print and exit:\n");
			inputRes = scanf_s("%d", &currentInput);

			//verify input is valid
			if (currentInput < 0 || currentInput > INT_MAX || inputRes != 1)
			{
				printf("Invalid Integer\n");
				done = true;
				break;
			}

			failed = FALSE;

			//search for the node with the value specified.  Duplicates use the
			//first one found
			RBTNode *deleteNode = TreeSearch(root, currentInput);

			if (deleteNode == NULL)
			{
				printf("Node key is invalid. Retry\n");
				failed = TRUE;
			}
			else
			{
				RBDelete(&root, deleteNode);
			}

			if (root != NULL && failed != TRUE)
			{
#if PRE_ORDER
				printf("\nPre-Order tree after deletion:\n");
				printRootLRNodeTree(root);
#endif
#if IN_ORDER
				printf("\nIn-Order tree after deletion:\n");
				printNodeTree(root);
#endif
				//check the RBT properties 4 and 5
				printf("\nProperty 4 is: ");
				printf(root->checkProperty4() ? "true" : "false");

				printf("\nProperty 5 is: ");
				blackPathCount = -1;
				printf(RBTBlackNodeCounter(root, 0, &blackPathCount) ? "true\n" : "false\n");

				//misc test outputs to test our functions
				printf("\nMax tree node is: %d\n", TreeMaximum(root)->key);
				printf("Min tree node is: %d\n", TreeMinimum(root)->key);
				printf("The root value is: %d\n", root->key);

				if (Successor(root) != NULL)
				{
					printf("The successor of root has value :%d\n", Successor(root)->key);
				}
				else
				{
					printf("Root does not have a successor\n");
				}

				if (Predeccessor(root) != NULL)
				{
					printf("The predecessor of root has value :%d\n\n", Predeccessor(root)->key);
				}
				else
				{
					printf("Root does not have a predeccesor\n\n");
				}
			}
			else
			{
				printf("Tree is empty\n");
			}
		}
	}
	else
	{
		printf("Root is NULL. No further testing can be done.\n");
	}

	system("PAUSE");
	return 0;
}