#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <treaps.h>

#define SIZEOF(z) sizeof(z)/sizeof(z[0])

extern node_t *ROOT_MAIN;

extern int closest1x, closest2x, closest1y, closest2y;
extern int max_nodes_count, current_nodes_count;
extern int rotations_left_count, rotations_right_count;

typedef struct point
{
	int x;
	int y;
}point_t;


int compare(point_t *p1, point_t *p2)
//int compare(void *a, void *b)
{
//	point_t *p1 = a;
//	point_t *p2 = b;

/*
	if(p1->x < p2->x)
	{
		return -1;
	}
	else if(p1->x > p2->x)
	{
		return 1;
	}
	else
	{
		return 0;
	}
*/
	return (p1->x - p2->x);
}





int main(void)
{
	/*
	point_t data[] = {	
						//x=heap, y=tree
						{.x = 0, .y = 1},
						{.x = 0, .y = 5},
						{.x = 1, .y = 1},
						{.x = 1, .y = 2},
						{.x = 2, .y = 3}, 
					};
	*/
	
	
	clock_t start, end;
	double qsort_time, sweep_time;
	int Dmin_sq = 0x7FFFFFFF;        //max integer
	
	
	int i;
	node_t *disp_array[50];
	for(i=0; i<SIZEOF(disp_array); i++)
	{
		disp_array[i] = NULL;
	}
	
	ROOT_MAIN = NULL;
	node_t *new=NULL;
	
		
	//GET input
	//##################################################################
	
	
	//FILE *f = fopen("input1K.dat", "r");
	//FILE *f = fopen("input10K.dat", "r");
	FILE *f = fopen("input1M.dat", "r");
	//FILE *f = fopen("testinput.dat", "r");
	if(!f)
	{
		printf("cannot open file.\n");
		
		exit(1);
	}
	
	
	int lines;
	fscanf(f, "%d\n", &lines);
	
	point_t *data_random = (point_t *)malloc(lines*sizeof(point_t));
	if(!data_random)
	{
		printf("cannot allocate memory\n");
		exit(1);
	}
	
	point_t *data = (point_t *)malloc(lines*sizeof(point_t));
	if(!data_random)
	{
		printf("cannot allocate memory\n");
		exit(1);
	}
	
	
	for(i=0; i<lines; i++)
	{
		//fscanf(f, "%c", &c);
		//printf("%d : %c   %d\n", i, c, c);
		
		fscanf(f, "%d %d\n", &(data_random[i].x), &(data_random[i].y));
		//printf("%d : %d   %d\n", i, data[i].x, data[i].y);
	}
	
	//##################################################################
	
	start = clock();
	qsort(data_random, lines, sizeof(point_t), compare);
	end = clock();
	
	qsort_time = (end-start)/(double)CLOCKS_PER_SEC;
	
/*
	for(i=0;i<lines; i++)
	{
		printf("%d %d\n", data_random[i].x, data_random[i].y);
	}
*/
	
	int not_duplicate_index=0;
	
	for(i=0;i<lines-1; i++)
	{
	/*
		if(data_random[i].x==data_random[i+1].x && data_random[i].y==data_random[i+1].y)
		{
			//duplicate points detected
			//printf("dupli");
			continue;
			
		}
		*///else
		{
			//not duplicate
			data[not_duplicate_index].x = data_random[i].x;
			data[not_duplicate_index].y = data_random[i].y;
			not_duplicate_index++;
		}
	}
	
	lines = ++not_duplicate_index;
	printf("LINES = %d\n", lines);	
	
	
	start = clock();
	for(i=0; i<lines; i++)
	{
		
		new = createNode(data[i].x, data[i].y);
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
			continue;
		}
		else
		{
			attachLeaf(new, ROOT_MAIN);
		}
		
		checkForRemovals(ROOT_MAIN, new, &Dmin_sq);
		node_t *ret;
		do
		{
			ret = removeNodes(ROOT_MAIN);
			if(ret)
			{
				deleteNode(ret, 1);
			}
		}
		while(ret);
		
		
		
		//printf("\n\n");
	}
	end = clock();
	
	sweep_time = (end-start)/(double)CLOCKS_PER_SEC;
	
	treeToArray(disp_array, ROOT_MAIN, 1, SIZEOF(disp_array));
	dispTreeArray(disp_array, SIZEOF(disp_array));
	printf("\n\n----------------------------------\n\n");
	printf("Left Rotations: %d\n", rotations_left_count);
	printf("Right Rotations: %d\n", rotations_right_count);
	printf("Max Nodes: %d\n", max_nodes_count);
	//printf("Current Nodes: %d\n", current_nodes_count);
	printf("\nClosest Points: (%d, %d) (%d, %d)\n", closest1x, closest1y, closest2x, closest2y);
	printf("Closest Distance squared: %d\n", Dmin_sq);
	printf("qsort time = %f s\n", qsort_time);
	printf("sweep time = %f s\n", sweep_time);
	
	return 0;
}
