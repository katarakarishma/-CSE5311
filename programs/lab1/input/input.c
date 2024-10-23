#include <stdio.h>
#include <stdlib.h>


typedef struct point
{
	int x;
	int y;
}point_t;



int main(void)
{
	FILE *f = fopen("input1K.dat", "r");
	
	if(!f)
	{
		printf("cannot open file.\n");
		exit(1);
	}
	char c;
	int i;
	int lines;
	fscanf(f, "%d\n", &lines);
	
	point_t *data = (point_t *)malloc(lines*sizeof(point_t));
	if(!data)
	{
		printf("cannot allocate memory\n");
		exit(1);
	}
	
	
	for(i=0; i<lines; i++)
	{
		//fscanf(f, "%c", &c);
		//printf("%d : %c   %d\n", i, c, c);
		
		fscanf(f, "%d %d\n", &(data[i].x), &(data[i].y));
		printf("%d : %d   %d\n", i, data[i].x, data[i].y);
	}
	
}
