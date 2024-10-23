#include <stdio.h>
#include <stdlib.h>

#include <treaps.h>

#define SIZEOF(x) sizeof(x)/sizeof(x[0])

extern node_t *ROOT_MAIN;


int main(void)
{
	int i;
	int data_heap[] = {1, 5, 3};
	int data_tree[] = {'a', 'b', 'c'};
	
	node_t *disp_array[50];
	for(i=0; i<SIZEOF(disp_array); i++)
	{
		disp_array[i] = NULL;
	}
	
	ROOT_MAIN = NULL;
	node_t *new=NULL;
	
	for(i=0; i<SIZEOF(data_tree); i++)
	{
		new = createNode(data_heap[i], data_tree[i]);
		if(!new)
		{
			printf("cannot create node");
			exit(1);
		}
		if(ROOT_MAIN==NULL)
		{
			//only first pass comes here
			//ROOT_ = new;
			ROOT_MAIN = new;
		}
		else
		{
			attachLeaf(new, ROOT_MAIN);
		}
		printf("\n\n");
	}
	
	
	treeToArray(disp_array, ROOT_MAIN, 1, SIZEOF(disp_array));
	dispTreeArray(disp_array, SIZEOF(disp_array));
	printf("\n\n");
	
	
	deleteNode(ROOT_MAIN, 1);
	
	for(i=0; i<SIZEOF(disp_array); i++)
	{
		disp_array[i] = NULL;
	}
	treeToArray(disp_array, ROOT_MAIN, 1, SIZEOF(disp_array));
	dispTreeArray(disp_array, SIZEOF(disp_array));
	printf("\n\n");
	
	
	return 0;
}
