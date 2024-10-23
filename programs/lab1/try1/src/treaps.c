#include <stdio.h>
#include <stdlib.h>

#include <treaps.h>

/*
#define NOP = 0
#define ATTACHED_TO_LEFT 1
#define ATTACHED_TO_RIGHT 2
#define ERROR 3
*/

node_t *ROOT_MAIN;

int closest1x, closest2x, closest1y, closest2y;
int max_nodes_count=0, current_nodes_count=0;
int rotations_left_count=0, rotations_right_count=0;


node_t *createNode(int key_heap, int key_tree)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	if(new)
	{
		new->key_heap = key_heap;
		new->key_tree = key_tree;
		new->childL   = NULL;
		new->childR   = NULL;
		new->parent   = NULL;
		new->tag      = DO_NOTHING;
		//new->balance= 0;
		//new->height = 0;
		current_nodes_count++;
		if(current_nodes_count > max_nodes_count)
		{
			max_nodes_count = current_nodes_count;
		}
	}
	return new;
}


void treeToArray(node_t **arr, node_t *root, int offset, int max_array_length)
{
	arr[offset] = root;
	
	
	if(root && ( (offset<<1)+1 < max_array_length) )
	{
		////printf("%2d ", root->key);
		treeToArray(arr, root->childL, offset<<1, max_array_length);
		treeToArray(arr, root->childR, (offset<<1) + 1, max_array_length);
	

	}
	else
	{

	}
	
}


void dispTreeArray(/*node_t *root, */node_t **array, int max_array_length)
{
	int index=0;
	
	for(index=0;index<max_array_length;index++)
	{
		if(array[index]!=NULL)
		{
			//printf("%d|%.2d,%.2d ", index, array[index]->key_heap, array[index]->key_tree);
		}
		else
		{
			//printf("%d|____ ", index);
		}
	}
}


int rotate(node_t *root, int direction)
{
	
	if(direction == RIGHT)
	{
		node_t *root_l, *root_l_r;
		if(root->childL == NULL)
		{
			//printf("canot rotate right. left child must exist.\n");
			return -1;
		}
		
		rotations_right_count++;
		
		root_l = root->childL;
		root_l_r = root_l->childR;
 
		// Perform rotation
		root->childL = root_l_r;                 /*//printf("%d->childL = %d\n", V(root), 	V(root_l_r))*/;
		if(root_l_r){root_l_r->parent = root;    /*//printf("%d->parent = %d\n", V(root_l_r), V(root));*/}     
		root_l->childR = root;			 /*//printf("%d->childR = %d\n", V(root_l), V(root))*/;
		root_l->parent = root->parent;           /*//printf("%d->parent = %d\n", V(root_l), V((root->parent)))*/;
		root->parent = root_l;			 /*//printf("%d->parent = %d\n", V(root), V(root_l))*/;
		if(root_l->parent)
		{
			if((root_l->parent)->childL == root){(root_l->parent)->childL = root_l;   /*//printf("X%d->childL = %d\n", V(((root_l->parent))), V(root_l));*/}
			if((root_l->parent)->childR == root){(root_l->parent)->childR = root_l;   /*//printf("Y%d->childR = %d\n", V(((root_l->parent))), V(root_l));*/}
		}
	}
	else
	{
		node_t *root_r, *root_r_l;
		if(root->childR == NULL)
		{
			//printf("cannot rotate. right child must exist.\n");
			return -1;
		}
		
		rotations_left_count++;
		
		root_r = root->childR;
		root_r_l = root_r->childL;
		
		//Perform rotation
		root->childR = root_r_l;		 /*//printf("%d->childR = %d\n", V(root), 	V(root_r_l))*/;
		if(root_r_l){root_r_l->parent = root;    /*//printf("%d->parent = %d\n", V(root_r_l), V(root));*/}
		root_r->childL = root;			 /*//printf("%d->childL = %d\n", V(root_r), V(root))*/;
		root_r->parent = root->parent;           /*//printf("%d->parent = %d\n", V(root_r), V((root->parent)))*/;
		root->parent = root_r;			 /*//printf("%d->parent = %d\n", V(root), V(root_r))*/;
		if(root_r->parent)
		{
			if((root_r->parent)->childL == root){(root_r->parent)->childL = root_r;   /*//printf("X%d->childL = %d\n", V(((root_r->parent))), V(root_r));*/}
			if((root_r->parent)->childR == root){(root_r->parent)->childR = root_r;   /*//printf("Y%d->childR = %d\n", V(((root_r->parent))), V(root_r));*/}
		}
	}
	/*else
	{
		if(root->childR == NULL)
		{
			//printf("canot rotate left. right child must exist.");
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



int attachLeaf(node_t *new, node_t *root)
{
	//int operation_performed = NOP;
	if(root)
	{
		//printf("%d %d %d\n", new->key_tree, root->key_tree, ROOT_MAIN->key_tree);
		if(new->key_tree <= root->key_tree)
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
				//printf("%d attached to left of %d\n", new->key_tree, root->key_tree);
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
				//printf("%d attached to right of %d\n", new->key_tree, root->key_tree);
			}
		}
	}
	else
	{
		//should never come here
		//printf("\n\n FATAL ERROR @1 \n\n");
		return -1;
	}
	
	
	////##################################################################
	////Beyond this point we are pulling out of the recurssion.
	////Balance the tree.
	////##################################################################
	
	//check need of rotation.
	//FOR TREAPS, child must be greater than parent
	
	
	if(root->childL)
	{
		if(root->key_heap > (root->childL)->key_heap)
		{
			//rotate right at root
			//printf("rotate right at %d\n", root->key_tree);
			rotate(root, RIGHT);
			root = root->parent;
		}
	}
	else if(root->childR)
	{
		if(root->key_heap > (root->childR)->key_heap)
		{
			//rotate left at root
			//printf("rotate left at %d\n", root->key_tree);
			rotate(root, LEFT);
			root = root->parent;
		}
	}
	
	
	
	
	
	return 0;							//successfully added a leaf
}

void deleteNode(node_t *root, int deallocate_memory)
{
	while(1) //the condition to break out of this loop is mentioned later
	{
		if(root->childL==NULL && root->childR!=NULL)
		{
			//only left child doesnt exist. rotate left.
			//printf("rotate left at %d\n", root->key_tree);
			rotate(root, LEFT);
			if(root == ROOT_MAIN)
			{
				ROOT_MAIN = root->parent;
			}
		}
		else if(root->childL!=NULL && root->childR==NULL)
		{
			//only right child doesnt exist. rotate right.
			//printf("rotate right at %d\n", root->key_tree);
			rotate(root, RIGHT);
			if(root == ROOT_MAIN)
			{
				ROOT_MAIN = root->parent;
			}
		}
		else if(root->childL!=NULL && root->childR!=NULL)
		{
			//both children exist.
			if((root->childL)->key_heap > (root->childR)->key_heap)
			{
				//left child is greater than right child. rotate left
				//printf("rotate left at %d\n", root->key_tree);
				rotate(root, LEFT);
				if(root == ROOT_MAIN)
				{
					ROOT_MAIN = root->parent;
				}
			}
			else
			{
				//right child is greater than left child. rotate right
				//printf("rotate right at %d\n", root->key_tree);
				rotate(root, RIGHT);
				if(root == ROOT_MAIN)
				{
					ROOT_MAIN = root->parent;
				}
			}
		}
		else
		{
			//no children exist. delete node.
			if(root->parent)
			{
				
			if((root->parent)->childL == root)
			{
				(root->parent)->childL = NULL;
			}
			if((root->parent)->childR == root)
			{
				(root->parent)->childR = NULL;
			}
			if(deallocate_memory)
			{
				free(root);
			}
			
			}
			else
			{
				//printf("WTF  %d\n", root->key_tree);
				//sleep(1);
			}
		
			current_nodes_count--;
			break;
		}
	}
}

int getDist_sq(node_t *n1, node_t *n2)
{
	int dx = n1->key_heap - n2->key_heap;
	int dy = n1->key_tree - n2->key_tree;
	return ( (dx*dx)+(dy*dy) );
}
void checkForRemovals(node_t *root, node_t *newest_node, int *dmin_sq)
{
	int d_sq = getDist_sq(root, newest_node);
	//printf("checking ... %d and %d : %d ? %d\n", root->key_tree, newest_node->key_tree, d_sq, *dmin_sq);
	//printf("decission: %d\n", (newest_node->key_heap-root->key_heap)*(newest_node->key_heap-root->key_heap));
	//if( d_sq>(*dmin_sq) && root!=newest_node)
	if( ( (newest_node->key_heap-root->key_heap)*(newest_node->key_heap-root->key_heap) )>(*dmin_sq) && root!=newest_node)
	{
		root->tag = REMOVE;
		//printf("%d marked for removal\n", root->key_tree);
		
	}
	else
	{
		//if(root!=newest_node)
		if( d_sq<(*dmin_sq) && root!=newest_node)
		{
			*dmin_sq = d_sq;
			closest1x = root->key_heap;
			closest1y = root->key_tree;
			closest2x = newest_node->key_heap;
			closest2y = newest_node->key_tree;
		}
	}
	
	if(root->childL)
	{
		checkForRemovals(root->childL, newest_node, dmin_sq);
	}
	if(root->childR)
	{
		checkForRemovals(root->childR, newest_node, dmin_sq);
	}
	

}

node_t *removeNodes(node_t *root)
{
	//printf("\nremoveNodes at %d\n", root->key_tree);
	if(root->tag == REMOVE)
	{
		//deleteNode(root, 0);
		return root;
	}
	else
	{
		if(root->childL)
		{
			node_t *ret = removeNodes(root->childL);
			if(ret)
			{
				return ret;
			}
		}
		if(root->childR)
		{
			node_t *ret = removeNodes(root->childR);
			if(ret)
			{
				return ret;
			}
		}
		return NULL;
	}
	return NULL;
}



