#ifndef _TREAPS_H
#define _TREAPS_H

#define LEFT 1
#define RIGHT 2


#define V(x) (x)?(x)->key_tree:-1


typedef struct node
{
	struct node *parent;
	struct node *childL, *childR;
	int key_heap, key_tree;
	
	//int height;
}node_t;



node_t *createNode(int key_heap, int key_tree);


int attachLeaf(node_t *new, node_t *root);
void treeToArray(node_t **arr, node_t *root, int offset, int max_array_length);
void dispTreeArray(/*node_t *root, */node_t **array, int max_array_length);


void deleteNode(node_t *root, int deallocate_memory);












#endif
