#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include "ant.h"

board_t *init_board(int m , int n, int direction, int ite, char *file_template){
	board_t *board = malloc(sizeof(*board));
	board->m = m;
	board->n = n;
	board->direction = direction;
	board->ite = ite;
	cell_t *cell_ptr;
        board->cells = malloc(m*sizeof(cell_ptr));
	int i;
	for(i = 0 ; i < m ; i++){
	board->cells[i] = malloc(n*sizeof(cell_t));	
	}	
	board->ant = &board->cells[n/2][m/2];
	board->ant_x = n/2;
	board->ant_y = m/2;
	board->file_template = file_template;
	return board;
}

void fill_by_percent (board_t *board , int percent){
	int i , j;
	for(i = 0 ; i < board->m ; i++){
		for(j = 0 ; j < board->n ; j++){
		int random = rand()%100;
		if(random < percent){
			board->cells[i][j].colour = 1;
		}else{
			board->cells[i][j].colour = 0;
		}
		}
	}
}

void fill_from_file (board_t *board , char *file){
	int i , j,n;
	char *s = malloc((board->n)*sizeof(char));
	FILE *f = fopen(file,"r");
	if (f == NULL) {
		printf("Nie udalo sie otworzyc pliku\n");
		exit(1);
	}
	for(i = 0 ; i < board->m ; i++){
		for(j = 0 ; j < board->n ; j++){
			board->cells[i][j].colour = fgetc(f);
		}
		fgetc(f);
	}

}

void fill_with_whites (board_t *board){
	int i,j;
	int m = board->m;
	int n = board->n;
	for(i = 0 ; i < m ; i++){
		for(j = 0 ; j < n ; j++){
			board->cells[i][j].colour = 0;
		}
	}
}

void turn_white (cell_t *cell){
	cell->colour = 0;
}

void turn_black (cell_t *cell){
	cell->colour = 1;
}

void turn_right(board_t *board){
	board->direction = ((board->direction)+1)%4;
}
	
void turn_left(board_t *board){
	board->direction = ((board->direction)-1)%4;
}

void print_board(board_t *board , FILE *f, int x){
	int i,j;
	int m = board->m;
	int n = board->n;
	int dir = board->direction;
		// górna krawędź
		fprintf(f,":%d\n",x);
		fprintf(f,"┌");
		for(i = 0 ; i < n ; i++){
			fprintf(f,"─");
		}
		fprintf(f,"┐\n");
		// ------
		// wypisywanie komórek
		for(i = 0 ; i < m ; i++){
			fprintf(f,"│");
			for(j = 0 ; j < n ; j++){
				if(&board->cells[i][j] == board->ant){
					switch(dir){
					case TOP:
						if(board->cells[i][j].colour == 0){
							fprintf(f,"△");
						}else{
							fprintf(f,"▲");
						}
						break;
					case RIGHT:
						if(board->cells[i][j].colour == 0){
                                                        fprintf(f,"▷");
                                                }else{
                                                        fprintf(f,"▶");
                                                }
                                                break;
					case BOTTOM:
						if(board->cells[i][j].colour == 0){
                                                        fprintf(f,"▽");
                                                }else{
                                                        fprintf(f,"▼");
                                                }
                                                break;
					case LEFT:
						if(board->cells[i][j].colour == 0){
                                                        fprintf(f,"◁");
                                                }else{
                                                        fprintf(f,"◀");
                                                break;
					}
				}
				}else{
				switch(board->cells[i][j].colour){
				case 0:
					fprintf(f," ");
					break;
				case 1:
					fprintf(f,"█");
					break;
				}
			}
			}
			fprintf(f,"│\n");
		}
		//------
		// dolna krawędź
		fprintf(f,"└");
		for(i = 0 ; i < n ; i++)
			fprintf(f,"─");
		fprintf(f,"┘\n");
		//------
}

void move_ant(board_t *board , int dir){
	int m = board->m;
	int n = board->n;
	switch (dir){
	case BOTTOM:
		if(board->ant_y < m-1){
		board->ant_y ++; 
		board->ant = &board->cells[board->ant_y][board->ant_x];
		}else{
		board->ant_y = 0;
		board->ant = &board->cells[board->ant_y][board->ant_x];
		}
		break;
	case TOP:
                if(board->ant_y > 0){
                board->ant_y --;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }else{
                board->ant_y = m-1;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }
		break;
	case RIGHT:
                if(board->ant_x < n-1){
                board->ant_x ++;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }else{
                board->ant_x = 0;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }
                break;
	case LEFT:
                if(board->ant_x > 0){
                board->ant_x --;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }else{
                board->ant_x = n-1;
                board->ant = &board->cells[board->ant_y][board->ant_x];
                }
                break;
	}
}


void solve_board(board_t *board){
	int m = board->m;
	int n = board->n;
	int dir = board->direction;
	int ite = board->ite;
	int i;
	for(i = 0 ; i < ite ; i++){
	switch(board->ant->colour){
		case 0:
		turn_right(board);
		turn_black(board->ant);
		break;
		case 1:
		turn_left(board);
		turn_white(board->ant);
		break;
	}
	move_ant(board , board->direction);
	char file_name[128];
	sprintf(file_name,"%s%d",board->file_template,i);
	FILE *f = fopen(file_name , "w");
	print_board (board , f , i);
	}
}

