#ifndef _TREE_H
#define _TREE_H

#define LEFT 1
#define RIGHT 2

#define MAX(x,y) (x<y)?(y):(x)

#define RETURN_HEIGHT_IF_NODE_EXISTS(x) (x==NULL)?-1:x->height

#define V(x) (x)?(x)->key:-1


// ADJUST_HEIGHT macro requires the variables height_left and height_right to be defined for the scope and ready to be used. 
#define ADJUST_HEIGHT(x) 	height_left = RETURN_HEIGHT_IF_NODE_EXISTS((x)->childL);   \
							height_right = RETURN_HEIGHT_IF_NODE_EXISTS((x)->childR);  \
							max_height = MAX(height_left, height_right);               \
							(x)->height = 1 + max_height

typedef struct node
{
	struct node *parent;
	struct node *childL, *childR;
	int key;
	//int balance;						//balance = right-left
	int height;
}node_t;


void treeToArray(node_t **arr, node_t *root, int offset, int max_array_length);
//node_t *createNode(node_t *parent, node_t *childL, node_t *childR, int key);
node_t *createNode(int key);
int rotate(node_t *root, int direction);
void dispTreeArray(/*node_t *root, */node_t **array,int max_array_length);

int attachLeaf(node_t *new, node_t *root);











#endif
