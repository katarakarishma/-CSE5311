#include <stdio.h>
#include <stdlib.h>

#include <tree.h>


#define ARRAY_SIZE 20

int main(void)
{
	node_t n1, n2, n3, n4;
	
	node_t *disp_array[ARRAY_SIZE];
	
	
	//n1.parent = NULL;
	n1.childL = &n2;
	n1.childR = &n3;
	n1.key = 1;
	
	//n2.parent = &n1;
	n2.key = 2;
	n2.childL = NULL;
	n2.childR = NULL;
	
	//n3.parent = &n1;
	n3.key = 3;
	n3.childL = NULL;
	n3.childR = NULL;
	
	int i;
	for(i=0; i<ARRAY_SIZE; i++)
	{
		disp_array[i] = NULL;
	}
	treeToArray(disp_array, &n1, 1, ARRAY_SIZE);
	
	
	//printf("\n\n");
	/*for(i=0;i<ARRAY_SIZE;i++)
	{
		if(array[i]!=NULL)
		{
			printf("%2d  ", array[i]->key);
		}
		else
		{
			printf("** ");
		}
	}*/
	dispTreeArray(&n1, disp_array, ARRAY_SIZE);
	printf("\n");
	
	rotate(&n1, LEFT);
	
	
	/*for(index=0;index<ARRAY_SIZE;index++)
	{
		array[index] = NULL;
	}
	treeToArray(array, &n2, 1, ARRAY_SIZE);
	
	printf("\n\n");
	for(i=0;i<ARRAY_SIZE;i++)
	{
		if(array[i]!=NULL)
		{
			printf("%2d  ", array[i]->key);
		}
		else
		{
			printf("** ");
		}
	}
	printf("\n");
	*/
	for(i=0; i<ARRAY_SIZE; i++)
	{
		disp_array[i] = NULL;
	}
	treeToArray(disp_array, &n3, 1, ARRAY_SIZE);
	dispTreeArray(&n3, disp_array, ARRAY_SIZE);
	printf("\n\n");
	node_t *new = createNode(4);
	if(new)
	{
		n2.childR = new;
	}
	for(i=0; i<ARRAY_SIZE; i++)
	{
		disp_array[i] = NULL;
	}
	treeToArray(disp_array, &n3, 1, ARRAY_SIZE);
	dispTreeArray(&n3, disp_array, ARRAY_SIZE);
	
	return 0;
}


