/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 10 Sepetember, 2018
Program description: In chess, a knight can move to a cell that is horizontally 2 cells and vertically 1 cell away, or
vertically 2 cells and horizontally 1 cell away (see Fig. Q4.). Thus, eight moves are possible
for a knight in general.
Given an m × n chess-like board, and a knight at position (i, j) (where 0 ≤ i < m and
0 ≤ j < n), compute the probability that the knight remains on the board after a given
number (say k) of steps, assuming that, at each step, all eight moves are equally likely. Note
that, once the knight moves off the board, it can never return to the board.

Run using : gcc -g -Wall cs1807-assign1-prog4.c -o prog4 -lm


Acknowledgements:
USE `gcc -g -Wall cs1807-assign-prog4.c -o prog4 -lm` to compile this code
------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


int knight_movements(int x, int y, int moves, int** visited_chess_board, int ROWS, int COLS){
    // printf("%d, %d , moves = %d\n", x, y, moves);
    if (moves >= 0){
            if (moves == 0){
                visited_chess_board[x][y] += 1;
            }
            // i - 2 , y + 1
            if ((x - 2 >= 0) && (x - 2 < ROWS) && (y + 1 >= 0) && (y + 1 < COLS)){
                knight_movements(x - 2, y + 1, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i - 2 , y - 1
            if ((x - 2 >= 0) && (x - 2 < ROWS) && (y - 1 >= 0) && (y - 1 < COLS)){
                knight_movements(x - 2, y - 1, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i - 1 , y + 2
            if ((x - 1 >= 0) && (x - 1 < ROWS) && (y + 2 >= 0) && (y + 2 < COLS)){
                knight_movements(x - 1, y + 2, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i - 1 , y - 2
            if ((x - 1 >= 0) && (x - 1 < ROWS) && (y - 2 >= 0) && (y - 2 < COLS)){
                knight_movements(x - 1, y - 2, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i + 1 , y + 2
            if ((x + 1 >= 0) && (x + 1 < ROWS) && (y + 2 >= 0) && (y + 2 < COLS)){
                knight_movements(x + 1, y + 2, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i + 1 , y - 2
            if ((x + 1 >= 0) && (x + 1 < ROWS) && (y - 2 >= 0) && (y - 2 < COLS)){
                knight_movements(x + 1, y - 2, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i + 2, y + 1
            if ((x + 2 >= 0) && (x + 2 < ROWS) && (y + 1 >= 0) && (y + 1 < COLS)){
                knight_movements(x + 2, y + 1, moves - 1, visited_chess_board, ROWS, COLS);
            }
            // i + 2, y - 1
            if ((x + 2 >= 0) && (x + 2 < ROWS) && (y - 1 >= 0) && (y - 1 < COLS)){
                knight_movements(x + 2, y - 1, moves - 1, visited_chess_board, ROWS, COLS);
            }
    }
    return 0;
}

int main(){
    int moves, initialX, initialY, ROWS, COLS;
    scanf("%d %d %d %d %d", &ROWS, &COLS, &initialX, &initialY, &moves);
    int i,j;

    int **visited_chess_board = CALLOC(int *, ROWS);
    for(i = 0; i < ROWS; i++)
    {
        visited_chess_board[i] = CALLOC(int, COLS);
    }

    knight_movements(initialX, initialY, moves, visited_chess_board, ROWS, COLS);

    int count = 0;

    for(i=0;i<ROWS;i++){
        for(j=0;j<COLS;j++){
            // printf("%d ", visited_chess_board[i][j]);
            if (visited_chess_board[i][j] > 0){
                count += visited_chess_board[i][j];
            }
        }
        // printf("\n");
    }

    // printf("count : %d total: %f\n", count, pow(8,moves));
    double result = (count/pow(8,moves));

    printf("%0.6f\n", result);
    return 0;
}