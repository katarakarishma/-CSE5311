#include <tree.h>
#include <stdio.h>
#include <stdlib.h>


#define V(x) (x)?(x)->key:-1

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
		new->key 	 = key;
		new->childL  = NULL;
		new->childR  = NULL;
		new->parent  = NULL;
		new->balance = 0;
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


int rotate(node_t *root, int direction)
{
	
	if(direction == RIGHT)
	{
		node_t *root_l, *root_l_r;
		if(root->childL == NULL)
		{
			printf("canot rotate right. left child must exist.");
			return -1;
		}
		root_l = root->childL;
		root_l_r = root_l->childR;
 
		// Perform rotation
		root->childL = root_l_r;                  printf("%d->childL = %d\n", V(root), 	V(root_l_r));
		if(root_l_r){root_l_r->parent = root;     printf("%d->parent = %d\n", V(root_l_r), V(root));}     
		root_l->childR = root;			  printf("%d->childR = %d\n", V(root_l), V(root));
		root_l->parent = root->parent;            printf("%d->parent = %d\n", V(root_l), V((root->parent)));
		root->parent = root_l;			  printf("%d->parent = %d\n", V(root), V(root_l));
		if(root_l->parent)
		{
			if((root_l->parent)->childL == root){(root_l->parent)->childL = root_l;    printf("X%d->childL = %d\n", V(((root_l->parent))), V(root_l));}
			if((root_l->parent)->childR == root){(root_l->parent)->childR = root_l;    printf("Y%d->childR = %d\n", V(((root_l->parent))), V(root_l));}
		}
	}
	else
	{
		node_t *root_r, *root_r_l;
		if(root->childR == NULL)
		{
			printf("cannot rotate. right child must exist.");
			return -1;
		}
		root_r = root->childR;
		root_r_l = root_r->childL;
		
		//Perform rotation
		root->childR = root_r_l;		  printf("%d->childR = %d\n", V(root), 	V(root_r_l));
		if(root_r_l){root_r_l->parent = root;     printf("%d->parent = %d\n", V(root_r_l), V(root));}
		root_r->childL = root;			  printf("%d->childL = %d\n", V(root_r), V(root));
		root_r->parent = root->parent;            printf("%d->parent = %d\n", V(root_r), V((root->parent)));
		root->parent = root_r;			  printf("%d->parent = %d\n", V(root), V(root_r));
		if(root_r->parent)
		{
			if((root_r->parent)->childL == root){(root_r->parent)->childL = root_r;    printf("X%d->childL = %d\n", V(((root_r->parent))), V(root_r));}
			if((root_r->parent)->childR == root){(root_r->parent)->childR = root_r;    printf("Y%d->childR = %d\n", V(((root_r->parent))), V(root_r));}
		}
	}
	
	
	
	
	
	
	
	/*else
	{
		if(root->childR == NULL)
		{
			printf("canot rotate left. right child must exist.");
			return -1;
		}
		
		x = root->childR;
		T2 = x->childL;
 
		// Perform rotation
		x->childL = root;
		root->childR = T2;
		
		x->parent = root->parent;
		root->parent = x;
		if(T2)
		{
			T2->parent = root;
		}
	}*/
	return 0;
}


void dispTreeArray(/*node_t *root, */node_t **array, int max_array_length)
{
	int index=0;
	
	for(index=0;index<max_array_length;index++)
	{
		if(array[index]!=NULL)
		{
			printf("%d|%.2d ", index, array[index]->key);
		}
		else
		{
			printf("%d|__ ", index);
		}
	}
}
 
int attachLeaf(node_t *new, node_t *root)
{
	if(root)
	{
		if(new->key < root->key)
		{
			//goto left
			if(root->childL)
			{
				attachLeaf(new, root->childL);
			}
			else
			{
				root->childL = new;
				new->parent = root;
			}
		}
		else
		{
			//goto right
			if(root->childR)
			{
				attachLeaf(new, root->childR);
			}
			else
			{
				root->childR = new;
				new->parent = root;
			}
		}
	}
	else
	{
		//should never come here
		return -1;
	}
	return 0;							//successfully added a leaf
}

