    #ifndef __MAZE_INCLUDED__
    #define __MAZE_INCLUDED__

    #include <stdio.h>
    #include "cell.h"
    #include "da.h"
    #include "queue.h"

    typedef struct maze MAZE;

    extern MAZE *newMAZE(int rows, int columns);
    extern void createMaze(int rows,int columns, char *fileName,int seed);
    extern void drawMaze(MAZE *maze);
    extern void freeMaze(MAZE *maze);
    extern void saveMaze(MAZE *maze, char *fileName);
    extern MAZE *loadMaze(char *fileName);
    extern void buildMaze(MAZE *maze,int seed);
    extern void DFS(MAZE *maze,int row, int column,int seed);
    extern void BFS(MAZE *maze, int currentCellRow, int currentCellColumn);
    extern void solveMaze(MAZE *maze, char *fileName);
    extern DA *getAdjListDFS(MAZE *maze,int row,int column);
    extern DA *getAdjListBFS(MAZE *maze,int row,int column);
    extern void emptyQueue(QUEUE *queue);





#endif