#include "maze.h"
#include "cell.h"
#include "da.h"
#include "stack.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


long int random(void);
void srandom(unsigned int seed);

struct maze
{
	CELL ***store;		//store[0][0]->value
	int rows;
	int columns;
};


MAZE *newMAZE(int rows, int columns)
{
	MAZE *p = malloc(sizeof(MAZE));
	if (p == 0) { fprintf(stderr, "out of memory\n"); exit(1); }

	p->rows = rows;
	p->columns = columns;

	p->store = malloc(sizeof(CELL **) * rows);
	int i,j;

	for(i=0; i < rows; i++)
	{
		p->store[i] = malloc(sizeof(CELL *) * columns);
		
		for(j=0; j < columns; j++)
		{
			p->store[i][j] = newCELL(i,j);
		}
	}

	return p;
}

void createMaze(int rows,int columns, char *fileName,int seed)
{
	MAZE *p = malloc(sizeof(MAZE));
	if (p == 0) { fprintf(stderr, "out of memory\n"); exit(1); }

	p->rows = rows;
	p->columns = columns;

	p->store = malloc(sizeof(CELL **) * rows);
	int i,j;

	for(i=0; i < rows; i++)
	{
		p->store[i] = malloc(sizeof(CELL *) * columns);
		
		for(j=0; j < columns; j++)
		{
			p->store[i][j] = newCELL(i,j);
		}
	}

	buildMaze(p,seed);
	saveMaze(p,fileName);
	freeMaze(p);
	return;
}

void saveMaze(MAZE *maze, char *fileName)
{
	FILE *f = fopen(fileName,"w");

	fprintf(f,"%d,%d\n",maze->rows,maze->columns);    //save columns and rows

	int i,j;

	for(i=0; i<maze->rows; i++)
	{
		for(j=0; j<maze->columns; j++)
		{
			fprintf(f,"%d,%d,%d\n",getRightWall(maze->store[i][j]),getBottomWall(maze->store[i][j]),getCellValue(maze->store[i][j]));
		}
	}

	fclose(f);
	return;
}

MAZE *loadMaze(char *fileName)
{
	FILE *f = fopen(fileName,"r");
	int arg1,arg2,arg3,i,j;
	
	fscanf(f,"%d,%d",&arg1,&arg2);
	MAZE *temp = newMAZE(arg1,arg2);

	for (i=0; i < temp->rows; i++)
	{
		for (j=0; j < temp->columns; j++)
		{
			fscanf(f,"%d,%d,%d",&arg1,&arg2,&arg3);
			setRightWall(temp->store[i][j],arg1);
			setBottomWall(temp->store[i][j],arg2);
			setCellValue(temp->store[i][j],arg3);
		}
	}

	fclose(f);
	return temp;
}



void drawMaze(MAZE *maze)
{
	int i,j;

	for (i=0; i <= (maze->columns * 4); i++)
	{
		fprintf(stdout,"-");
	}
	fprintf(stdout,"\n");


	for(i=0; i < maze->rows; i++)
	{
		if (i == 0){fprintf(stdout," ");}
		else {fprintf(stdout, "|");}

		for(j=0; j < maze->columns; j++)
		{			
			if(getRightWall(maze->store[i][j]))
			{
				if (i == maze->rows-1 && j == maze->columns-1)
				{
					if (hasValue(maze->store[i][j]))
					{
						fprintf(stdout," ");
						fprintf(stdout,"%d  ",getCellValue(maze->store[i][j]));
					}
					else
					{
						fprintf(stdout,"    ");
					}
				}
				else
				{
					if (hasValue(maze->store[i][j]))
					{
						fprintf(stdout," ");
						fprintf(stdout,"%d |",getCellValue(maze->store[i][j]));
					}
					else
					{
						fprintf(stdout,"   |");
					}
				}
			}
			else
			{
				if (hasValue(maze->store[i][j]))
				{
					fprintf(stdout," ");
					fprintf(stdout,"%d  ",getCellValue(maze->store[i][j]));
				}
				else
				{
					fprintf(stdout,"    ");
				}
			}
		}

		fprintf(stdout,"\n-");

		for(j=0; j<maze->columns; j++)
		{		
			if (getBottomWall(maze->store[i][j]))
			{
				fprintf(stdout,"----");
			}
			else
			{
				fprintf(stdout,"   -");
			}
		}

		fprintf(stdout,"\n");
	}
	freeMaze(maze);
	return;
}


void buildMaze(MAZE *maze, int seed)
{
	DFS(maze,0,0,seed);
	return;
}


void freeMaze(MAZE *maze)
{
	int i,j;

	for(i=0; i < maze->rows; i++)
	{		
		for(j=0; j < maze->columns; j++)
		{
			free(maze->store[i][j]);
		}
		free(maze->store[i]);
	}

	free(maze->store);
	free(maze);

	return;
}


void DFS(MAZE *maze,int currentCellRow, int currentCellColumn, int seed)
{
	srandom(seed);

	int nextCellRow,nextCellColumn;
	DA *arr;
	STACK *vertices = newSTACK();

	push(vertices,maze->store[currentCellRow][currentCellColumn]);

	while(sizeSTACK(vertices) > 0)
	{	
		arr = getAdjListDFS(maze,currentCellRow,currentCellColumn); //probably need to free

		if (sizeDA(arr) == 0)	//no more paths from this vertice
		{
			setVisited(maze->store[currentCellRow][currentCellColumn],1);
			pop(vertices);

			if (sizeSTACK(vertices) > 0)
			{
				currentCellRow = getCellRow(peekSTACK(vertices));
				currentCellColumn = getCellColumn(peekSTACK(vertices));
				freeDA(arr);
				arr = getAdjListDFS(maze,currentCellRow,currentCellColumn); 
			}
		}
		else
		{
			int index = random() % sizeDA(arr);
			nextCellRow = getCellRow(getDA(arr,index));
			nextCellColumn = getCellColumn(getDA(arr,index));

			if (nextCellRow > currentCellRow)		//remove bottom wall and go to cell below
			{
				setBottomWall(maze->store[currentCellRow][currentCellColumn],0);
				setVisited(maze->store[currentCellRow][currentCellColumn],1);
				currentCellRow = nextCellRow;
				currentCellColumn = nextCellColumn;
				push(vertices,maze->store[currentCellRow][currentCellColumn]);
			}
			else if (nextCellColumn > currentCellColumn)	//remove right wall and go to the cell to the right
			{
				setRightWall(maze->store[currentCellRow][currentCellColumn],0);
				setVisited(maze->store[currentCellRow][currentCellColumn],1);
				currentCellRow = nextCellRow;
				currentCellColumn = nextCellColumn;
				push(vertices,maze->store[currentCellRow][currentCellColumn]);
			}	
			else if (currentCellRow > nextCellRow)		//go to the cell above and remove bottom wall
			{
				setVisited(maze->store[currentCellRow][currentCellColumn],1);
				setBottomWall(maze->store[nextCellRow][nextCellColumn],0);
				currentCellRow = nextCellRow;
				currentCellColumn = nextCellColumn;
				push(vertices,maze->store[currentCellRow][currentCellColumn]);
			}
			else if (currentCellColumn > nextCellColumn)	//go to the cell to the left and remove right wall
			{
				setVisited(maze->store[currentCellRow][currentCellColumn],1);
				setRightWall(maze->store[nextCellRow][nextCellColumn],0);
				currentCellRow = nextCellRow;
				currentCellColumn = nextCellColumn;
				push(vertices,maze->store[currentCellRow][currentCellColumn]);
			}
			//fprintf(stdout,"random index:%d, cell grabbed: %d,%d\n",index,nextCellRow,nextCellColumn);
		}
		
		freeDA(arr);
	}

	freeSTACK(vertices);
	//free(vertices);
	return;
}

DA *getAdjListDFS(MAZE *maze,int row,int column)
{
	DA *arr = newDA();

	if(row-1 >= 0 && !isVisited(maze->store[row-1][column])) //if cell above is valid add to adjacency list
	{
		insertDA(arr,sizeDA(arr),maze->store[row-1][column]);
	}
	if(column-1 >= 0 && !isVisited(maze->store[row][column-1])) //if cell to the left is valid add to adjacency list
	{
		insertDA(arr,sizeDA(arr),maze->store[row][column-1]);
	}
	if(column+1 < maze->columns && !isVisited(maze->store[row][column+1])) //if cell to the right is valid add to adjacency list
	{	
		insertDA(arr,sizeDA(arr),maze->store[row][column+1]);
	}
	if(row+1 < maze->rows && !isVisited(maze->store[row+1][column])) //if cell is below
	{
		insertDA(arr,sizeDA(arr),maze->store[row+1][column]);
	}
	return arr;
}

DA *getAdjListBFS(MAZE *maze,int row,int column)
{
	DA *arr = newDA();

	if(row-1 >= 0 && !hasValue(maze->store[row-1][column])) //if cell above is valid add to adjacency list
	{
		insertDA(arr,sizeDA(arr),maze->store[row-1][column]);
	}
	if(column-1 >= 0 && !hasValue(maze->store[row][column-1])) //if cell to the left is valid add to adjacency list
	{
		insertDA(arr,sizeDA(arr),maze->store[row][column-1]);
	}
	if(column+1 < maze->columns && !hasValue(maze->store[row][column+1])) //if cell to the right is valid add to adjacency list
	{	
		insertDA(arr,sizeDA(arr),maze->store[row][column+1]);
	}
	if(row+1 < maze->rows && !hasValue(maze->store[row+1][column])) //if cell is below
	{
		insertDA(arr,sizeDA(arr),maze->store[row+1][column]);
	}
	return arr;
}


void solveMaze(MAZE *maze, char *fileName)
{
	BFS(maze,0,0);
	//fprintf(stdout,"%s\n\n",fileName);
	saveMaze(maze,fileName);
	freeMaze(maze);
	return;
}


void BFS(MAZE *maze, int currentCellRow, int currentCellColumn)
{
	int i;
	DA *arr;

	QUEUE *vertices = newQUEUE();
	setCellValue(maze->store[currentCellRow][currentCellColumn],0);
	enqueue(vertices,maze->store[currentCellRow][currentCellColumn]);

	while(sizeQUEUE(vertices) > 0)
	{
		CELL *cell = peekQUEUE(vertices);
		currentCellRow = getCellRow(cell);
		currentCellColumn = getCellColumn(cell);

		//got to the exit/
		

		arr = getAdjListBFS(maze,currentCellRow,currentCellColumn);

		for(i=0; i<sizeDA(arr); i++)
		{
			//check bottom wall and enqueue cell below if theres no wall or value
			if (getCellRow(getDA(arr,i)) > currentCellRow && !(getBottomWall(cell)) && !(hasValue(getDA(arr,i))))
			{
				setCellValue(getDA(arr,i),(getCellValue(cell)+1)%10);
				enqueue(vertices,getDA(arr,i));
			}
			//check top wall and enque cell above if theres no wall or value
			else if (getCellRow(getDA(arr,i)) < currentCellRow && !(getBottomWall(getDA(arr,i))) && !(hasValue(getDA(arr,i))))
			{
				setCellValue(getDA(arr,i),(getCellValue(cell)+1)%10);
				enqueue(vertices,getDA(arr,i));
			}

			//check right wall and add cell to the right
			else if (getCellColumn(getDA(arr,i)) > currentCellColumn && !(getRightWall(cell)) && !(hasValue(getDA(arr,i))))
			{
				setCellValue(getDA(arr,i),(getCellValue(cell)+1)%10);
				enqueue(vertices,getDA(arr,i));
			}

			//check left wall and add cell to the left
			else if (getCellColumn(getDA(arr,i)) < currentCellColumn && !(getRightWall(getDA(arr,i))) && !(hasValue(getDA(arr,i))))
			{
				setCellValue(getDA(arr,i),(getCellValue(cell)+1)%10);
				enqueue(vertices,getDA(arr,i));
			}
		}

		if(currentCellRow == maze->rows-1 && currentCellColumn == maze->columns-1)
		{
			/*if (getCellValue(maze->store[currentCellRow][currentCellColumn-1]) < getCellValue(maze->store[currentCellRow-1][currentCellColumn]) && !(getRightWall(maze->store[currentCellRow][currentCellColumn-1])))
			{
				setCellValue(cell,(getCellValue(maze->store[currentCellRow][currentCellColumn-1])+1)%10);
			}
			else
			{
				setCellValue(cell,(getCellValue(maze->store[currentCellRow-1][currentCellColumn])+1)%10);
			}*/
			dequeue(vertices);
			freeDA(arr);
			break;
		}

		dequeue(vertices);
		freeDA(arr);
	}

	emptyQueue(vertices);
	return;
}


void emptyQueue(QUEUE *vertices)
{
	while(sizeQUEUE(vertices) > 0)
	{
		CELL *cell = dequeue(vertices);
		setCellValue(cell,-1);
	}
	freeQUEUE(vertices);
	//free(vertices);
	return;
}