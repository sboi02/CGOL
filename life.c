#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define COLS 105 
#define ROWS 105
#define ALIVE '*'
#define DEAD '.'
int getIndex(int x, int y){
    return y*COLS+x;
}
//prints whole grid (COLS*ROWS)
void printGrid(char *grid){
    for(int i = 0; i<ROWS; i++){
        for (int j=i*COLS; j<(i+1)*COLS; j++){
            printf("%c", grid[j]);
        }
        printf("\n");
    }
}
//sets whole grid to state
void setGrid(char *grid, char state){
    for(int i = 0; i<ROWS*COLS; i++){
        grid[i]=state;
    }
}
//sets cell to state
void setCell(char *grid, int x, int y, char state){
    grid[getIndex(x,y)]=state;     
    
}
//counts cells in given state around a given cell
int countCells(char *grid, int x, int y, char state){
    int nCells = 0;
    for(int x0=-1; x0<2; x0++){
        for(int y0=-1; y0<2; y0++){
            if (x0==0 && y0==0)
                continue;
            if ((x+x0>-1 && x+x0<COLS) && (y+y0>-1 && y+y0<ROWS) && grid[getIndex(x+x0,y+y0)] == state)
                nCells++;
        }     
    }
    return nCells;    
} 
//updates state of the grid according to CGoL rules
void updateState(char *oldGrid, char *newGrid){
    setGrid(newGrid, DEAD);
    for(int x=0; x<COLS; x++){
        for(int y=0; y<ROWS; y++){
            int nAlive = countCells(oldGrid, x,y, ALIVE);
            if (oldGrid[getIndex(x,y)]==ALIVE){
                switch (nAlive){
                    case 2:
                    case 3:
                        newGrid[getIndex(x,y)]=ALIVE;
                        break;
                }

            }else if (nAlive==3)
                newGrid[getIndex(x,y)]=ALIVE;
        }

    }        
}


int main(void){
    char oldGrid[ROWS*COLS];
    char newGrid[ROWS*COLS];
    char *old = oldGrid;
    char *new = newGrid;
    setGrid(old, DEAD);
    /*Glider
    setCell(old, 14, 5, ALIVE);
    setCell(old, 15, 5, ALIVE);
    setCell(old, 16, 5, ALIVE);
    setCell(old, 16, 4, ALIVE);
    setCell(old, 15, 3, ALIVE);
    */
    /*R-pentomino*/
    setCell(old, 42, 42, ALIVE);
    setCell(old, 43, 42, ALIVE);
    setCell(old, 42, 43, ALIVE);
    setCell(old, 42, 44, ALIVE);
    setCell(old, 41, 43, ALIVE);
    
    while(1){
        printf("\x1b[3J\x1b[H\x1b[2J");
        printGrid(old);
        updateState(old, new);
        char *tmp = old;
        old = new;
        new =tmp;
        usleep(100000);
    }
    return 0;
}
