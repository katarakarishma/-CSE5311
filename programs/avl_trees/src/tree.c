#include <tree.h>
#include <stdio.h>
#include <stdlib.h>


node_t *ROOT_MAIN;


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
		new->parent = NULL;
		//new->balance= 0;
		new->height = 0;
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

/*
int rotate(node_t *root, int direction)
{
	node_t *x, *T2;
	if(direction == RIGHT)
	{
		if(root->childL == NULL)
		{
			//canot rotate right. left child must exist.
			return -1;
		}
		x = root->childL;
		T2 = x->childR;
 
		// Perform rotation
		x->childR = root;
		root->childL = T2;
	
		x->parent = root->parent;
		(root->parent)->
		root->parent = x;
		if(T2)
		{
			T2->parent = root;
		}
	}
	else
	{
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
	}
	return 0;
}
*/


int rotate(node_t *root, int direction)
{
	
	if(direction == RIGHT)
	{
		node_t *root_l, *root_l_r;
		if(root->childL == NULL)
		{
			printf("canot rotate right. left child must exist.\n");
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
			printf("cannot rotate. right child must exist.\n");
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
		printf("%d %d %d\n", new->key, root->key, ROOT_MAIN->key);
		if(new->key < root->key)
		{
			//goto left
			if(root->childL)
			{
				//left child exists. Go to child and continue recurssion
				
				attachLeaf(new, root->childL);
			}
			else
			{
				root->childL = new;
				new->parent = root;
				printf("%d attached to left of %d\n", new->key, root->key);
			}
		}
		else
		{
			//goto right
			if(root->childR)
			{
				//right child exists. Go to child and continue recurssion
				
				attachLeaf(new, root->childR);
			}
			else
			{
				root->childR = new;
				new->parent = root;
				printf("%d attached to right of %d\n", new->key, root->key);
			}
		}
	}
	else
	{
		//should never come here
		printf("\n\n FATAL ERROR @1 \n\n");
		return -1;
	}
	
	
	//##################################################################
	//Beyond this point we are pulling out of the recurssion.
	//Balance the tree.
	//##################################################################
	
	
	//##################################################################
	//Update the height of all nodes once a leaf is added
	int height_left, height_right, max_height;
	height_left = RETURN_HEIGHT_IF_NODE_EXISTS(root->childL);
	height_right = RETURN_HEIGHT_IF_NODE_EXISTS(root->childR);
	max_height = MAX(height_left, height_right);
	
	root->height = 1 + max_height;
	//##################################################################
	
	//printf("%d\n", root->height);
	
	//if(root->childL!=NULL && root->childR!=NULL)
	//{
		//both children exist
		//int balance_factor = (root->childR)->height - (root->childL)->height;
		int balance_factor = height_right - height_left;
		printf("bftest: key=%d bf=%d\n", root->key, balance_factor);
		//if(balance_factor>1 || balance_factor<-1)
		//{
			//tree is unbalanced at this root.
			//balance it by rotations.
			if(balance_factor>1)
			{
				//tree is leaning to the right
				//Need to find out whether we need to so a single left rotation or a right left rotation.
				//if the right child is left heavy then do right left rotation. Else a single left rotation.
				height_left = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childL);
				height_right = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childR);
				int bal_fac_of_child = height_right-height_left;
				
				
				if(bal_fac_of_child<0)
				{
					//need a right left rotation.
					printf("in_rotate right at %d\n", (root->childR)->key);
					printf("\nroot->childR = %d\n", (root->childR)->key);
					rotate(root->childR, RIGHT);
					printf("\nroot->childR = %d\n", (root->childR)->key);
					//update heights
					//first calculate height of root->childR->childR [previous right child of root]
					//(root->childR)->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS(((root->childR)->childR)->childR), RETURN_HEIGHT_IF_NODE_EXISTS(((root->childR)->childR)->childL) );
					
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS(((root->childR)->childR)->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS(((root->childR)->childR)->childR);
					max_height = MAX(height_left, height_right);
					((root->childR)->childR)->height = 1 + max_height;
					*/
					ADJUST_HEIGHT((root->childR)->childR);
					
					//now calculate height of root->childR  [the new right child of root]
					//root->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS(root->childL), RETURN_HEIGHT_IF_NODE_EXISTS(root->childR) );
					
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childR);
					max_height = MAX(height_left, height_right);
					(root->childR)->height = 1 + max_height;
					*/
					ADJUST_HEIGHT(root->childR);
					
					
					//The remaining left rotation is done anyways below outside this 'if block'
					//printf("rotate left at %d", root->key);  
					//rotate(root, LEFT);
				
				}
					
				
				//int i;
				//for(i=1; i<=balance_factor/2; i++)
				//{
					printf("rotate left at %d\n", root->key);
					rotate(root, LEFT);
					if(root == ROOT_MAIN)
					{
						//if rotation is done at the MAIN ROOT then update the global variable ROOT_MAIN
						ROOT_MAIN = root->parent;
					}
					root = root->parent;
					
					
					//update heights
					//first calculate height of root->childL [left child of the new root [aka the previous root] ]
					//(root->childL)->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childL), RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childR) );
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childR);
					max_height = MAX(height_left, height_right);
					(root->childL)->height = 1 + max_height;
					*/
					ADJUST_HEIGHT(root->childL);
					
					//now calculate height of root  [the new root]
					//root->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS(root->childL), RETURN_HEIGHT_IF_NODE_EXISTS(root->childR) );
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS(root->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS(root->childR);
					max_height = MAX(height_left, height_right);
					root->height = 1 + max_height;
					*/
					ADJUST_HEIGHT(root);
					
				//}
			}
			else if(balance_factor<-1)
			{
				//tree is leaning to the left.
				//Need to find out whether we need to so a single right rotation or a left right rotation.
				//if the left child is right heavy then do left right rotation. Else a single right rotation.
				
				//int i;
				//for(i=1; i<=-balance_factor/2; i++)
				//{
				height_left = RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childL);
				height_right = RETURN_HEIGHT_IF_NODE_EXISTS((root->childL)->childR);
				int bal_fac_of_child = height_right-height_left;	
					
				if(bal_fac_of_child>0)
				{
					//need a left right rotation.
					printf("in_rotate left at %d\n", (root->childL)->key);
					printf("\nroot->childL = %d\n", (root->childL)->key);
					rotate(root->childL, LEFT);
					printf("\nroot->childL = %d\n", (root->childL)->key);
					
					
					ADJUST_HEIGHT((root->childL)->childL);
					
					ADJUST_HEIGHT(root->childL);
				}
					
					
					
						
					printf("rotate right at %d\n", root->key);
					rotate(root, RIGHT);
					if(root == ROOT_MAIN)
					{
						//if rotation is done at the MAIN ROOT then update the global variable ROOT_MAIN
						ROOT_MAIN = root->parent;
					}
					root = root->parent;
					
					
					//update heights
					//first calculate height of root->childR [left child of the new root [aka the previous root] ]
					//(root->childR)->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childL), RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childR) );
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS((root->childR)->childR);
					max_height = MAX(height_left, height_right);
					(root->childR)->height = 1 + max_height;
					*/
					ADJUST_HEIGHT(root->childR);
					
					
					//now calculate height of root  [the new root]
					//root->height = 1 + MAX( RETURN_HEIGHT_IF_NODE_EXISTS(root->childL), RETURN_HEIGHT_IF_NODE_EXISTS(root->childR) );
					/*
					height_left = RETURN_HEIGHT_IF_NODE_EXISTS(root->childL);
					height_right = RETURN_HEIGHT_IF_NODE_EXISTS(root->childR);
					max_height = MAX(height_left, height_right);
					root->height = 1 + max_height;
					*/
					ADJUST_HEIGHT(root);
				
				
				//}
			}
		//}
			
	/*}
	else if(root->childL==NULL)
	{
		
	}
	else if(root->childR==NULL)
	{
		//right child does not exist
	}
	else
	{
		//should never come here
		printf("\n\n FATAL ERROR @2 \n\n");
		return -1;
	}
	*/
	
	return 0;							//successfully added a leaf
}

