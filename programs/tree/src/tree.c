#include <tree.h>
#include <stdio.h>
#include <stdlib.h>

/*
node_t *createNode(node_t *parent, node_t *childL, node_t *childR, int key)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	if(new)
	{
		new->parent = parent;
		new->childL = childL;
		new->childR = childR;
		new->key 	= key;
	}
	return new;
}
*/
node_t *createNode(int key)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	if(new)
	{
		new->key 	= key;
		new->childL = NULL;
		new->childR = NULL;
	}
	return new;
}



/*
 * 
 * name: treeToArray
 * @param arr pointer to array of node_t. The array must be initialised to all NULL.
 * @param root the root of the tree.
 * @param offset pass as 1. arr[0] is to be conventiolally set as NULL. So offset 1 indicates the loaction to start from.
 * @param max_array_length max length of the array pointed by arr.
 * @return void
 * 
 */
void treeToArray(node_t **arr, node_t *root, int offset, int max_array_length)
{
	arr[offset] = root;
	
	
	if(root && ( (offset<<1)+1 < max_array_length) )
	{
		//printf("%2d ", root->key);
		treeToArray(arr, root->childL, offset<<1, max_array_length);
		treeToArray(arr, root->childR, (offset<<1) + 1, max_array_length);
	

	}
	else
	{

	}
	
}


void rotate(node_t *root, int direction)
{
	node_t *x, *T2;
	if(direction == RIGHT)
	{
		x = root->childL;
		T2 = x->childR;
 
		// Perform rotation
		x->childR = root;
		root->childL = T2;
	}
	else
	{
		x = root->childR;
		T2 = x->childL;
 
		// Perform rotation
		x->childL = root;
		root->childR = T2;
	}
}


void dispTreeArray(node_t *root, node_t **array, int max_array_length)
{
	int index=0;
	
	for(index=0;index<max_array_length;index++)
	{
		if(array[index]!=NULL)
		{
			printf("%2d ", array[index]->key);
		}
		else
		{
			printf("** ");
		}
	}
}
 
