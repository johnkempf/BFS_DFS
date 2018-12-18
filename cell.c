#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct cell
{
	int value;				//default -1 till the maze begins solving.
	//int location[2];		//-1 for unused otherwise holds row,column.
	int rightWall;
	int bottomWall;
	//int wall[4]; 			//1 for a wall, 0 for a hole. [top,right,bottom,left]
	int visited;			//0 for unvisisted 1 for visited
	int row;
	int column;
};	


CELL *newCELL(int row,int column)
{
	CELL *p =  malloc(sizeof(CELL));
	if (p == 0) { fprintf(stderr, "out of memory\n"); exit(1); }
	p->value = -1;	
	p->rightWall = 1;
	p->bottomWall = 1;			
	p->visited = 0;
	p->row = row;
	p->column = column;

	return p;
}

int getRightWall(CELL *cell)
{
	return cell->rightWall;
}

int getBottomWall(CELL *cell)
{
	return cell->bottomWall;
}

void setRightWall(CELL *cell,int value)
{
	//int temp = cell->wall[1];
	cell->rightWall = value;
	return; //temp;
}

void setBottomWall(CELL *cell, int value)
{
	//int temp = cell->wall[2];
	cell->bottomWall = value;
	return; // temp;
}

int isVisited(CELL *cell)
{
	return cell->visited;
}

void setVisited(CELL *cell, int value)
{
	cell->visited = value;
	return;
}

int getCellRow(CELL *cell)
{
	return cell->row;
}

int getCellColumn(CELL *cell)
{
	return cell->column;
}

int getCellValue(CELL *cell)
{
	return cell->value;
}

void setCellValue(CELL *cell, int value)
{
	cell->value = value;
	return;
}

int hasValue(CELL *cell)
{
	if (cell->value == -1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}