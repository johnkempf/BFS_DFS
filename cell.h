    #ifndef __CELL_INCLUDED__
    #define __CELL_INCLUDED__

    #include <stdio.h>

    typedef struct cell CELL;

    extern CELL *newCELL(int row, int column);
    extern int getRightWall(CELL *cell);
    extern int getBottomWall(CELL *cell);
    extern void setRightWall(CELL *cell, int value);
    extern void setBottomWall(CELL *cell, int value);
    extern int isVisited(CELL *cell);
    extern void setVisited(CELL *cell, int value);
    extern int getCellRow(CELL *cell);
    extern int getCellColumn(CELL *cell);
    extern int getCellValue(CELL *cell);
    extern void setCellValue(CELL *cell, int value);
    extern int hasValue(CELL *cell);




    //extern int getRightWall(CELL*);
    /*extern void  setSTACKdisplay(STACK *,void (*)(void *,FILE *));
    extern void  setSTACKfree(STACK *,void (*)(void *));
    extern void  push(STACK *items,void *value);
    extern void *pop(STACK *items);
    extern void *peekSTACK(STACK *items);
    extern void  displaySTACK(STACK *items,FILE *fp);
    extern int   debugSTACK(STACK *items,int level);
    extern void  freeSTACK(STACK *items);
    extern int   sizeSTACK(STACK *items);*/

#endif