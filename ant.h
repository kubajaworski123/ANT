#ifndef ANT_H
#define ANT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cell_struct{
	int colour;
} cell_t;	

typedef struct board_struct{
	int m;
	int n;
	cell_t *ant; 
	int direction;
	cell_t **cells;
	int ite;
	int ant_x;
	int ant_y;
	char *file_template;
} board_t;

//kierunki ustawienia mrówki
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

board_t *init_board(int m , int n, int direction, int ite, char *file_template);
void print_board(board_t *board , FILE *f, int x);
void fill_with_whites(board_t *board);
void turn_white(cell_t *cell);
void turn_black(cell_t *cell);
void turn_right(board_t *board);
void turn_left(board_t *board);
void migrate_ant(board_t *board);
void solve_board(board_t *board);
void move_ant(board_t *board , int direction);
void fill_by_percent(board_t *board , int percent);
void fill_from_file(board_t *board, char *file);

#endif
