#include "cell.h"
#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

void ProcessOptions(int,char**);
int printNameFlag = 0;
int createMazeFlag = 0;
int solveMazeFlag = 0;
int drawMazeFlag = 0; 
int seedFlag = 0;
int rows = 0;
int cols = 0;
int seed = 1;
char *createdFileName;
char *mazeToSolveFileName;
char *solvedFileName;
char *drawFileName;



int main (int argc, char **argv)
{
	ProcessOptions(argc, argv);
//make sure seed is working	

    if (printNameFlag)
    {
        fprintf(stdout,"Written by John Kempf");
        exit(0);
    }
    //if (seedFlag)
    if (createMazeFlag)
    {
        createMaze(rows,cols,createdFileName,seed);
    }
    if (solveMazeFlag)
    {
        solveMaze(loadMaze(mazeToSolveFileName),solvedFileName);
    }
    if (drawMazeFlag)
    {
        drawMaze(loadMaze(drawFileName));
    }

    return 0;
}



void ProcessOptions(int argc, char **argv)
{
    int start,argIndex;
    int argsUsed;
    char *arg;
    //char *fileName;
    //char *fileName2;

    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return;

        argsUsed = 0;
        start = argIndex;

        /* advance argIndex to point to the first argument to the option */
        if (argv[start][2] == '\0')
            {
            arg = argv[start+1];
            ++argIndex;
            }
        else
            {
            /* first arg is connected to option, so don't advance */
            arg = argv[start]+2;
            }

        switch (argv[start][1])
            {
   				case 'v':
   					printNameFlag = 1;
   					break;

            	case 'c':
                    createMazeFlag = 1;
                	rows = atoi(arg);
                	cols = atoi(argv[argIndex+1]);
                	createdFileName = argv[argIndex+2];
                	argsUsed = 3;
                	break;

            	case 's':						//fix this
                	solveMazeFlag = 1;
                    mazeToSolveFileName = arg;	
                	solvedFileName = argv[argIndex+1];
                	argsUsed = 2;
                	break;

                case 'r':
                    seedFlag = 1;
                	seed = atoi(arg);
                	argsUsed = 1;
                	break;

            	case 'd':
                    drawMazeFlag = 1;
                	drawFileName = arg;
                	argsUsed = 1;
                	break;
            default:
                fprintf(stderr,"option %s not understood\n",argv[start]);
                exit(-1);
            }
        	argIndex += argsUsed;
        }
}



