#include "ant.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

int main (int argc , char** argv){
	srand(time(NULL));
	int option;
	int m , n , i , d ;
	int p = 0;
	char *f;
	char *l;
	//board_t *board = init_board(m , n , d , i , f);
	while((option = getopt(argc, argv , "-m:n:i:f:d:p:l:xyz")) != -1){

		switch(option){
		case('m'):
	        m = atoi(optarg);		
		break;
		
		case('n'):
		n = atoi(optarg);
		break;

		case('i'):
		i = atoi(optarg);
		break;

		case('f'):
		f = optarg;
		break;
		
		case('d'):
		d = atoi(optarg);
		break;

		case('p'):
		p = atoi(optarg);
		break;

		case('l'):
		l = optarg;
		break;
		
		case('x'):
		board_t *board = init_board(m , n , d , i , f);
		fill_with_whites(board);
		solve_board(board);
		break;

		case('y'):
		board_t *boardd = init_board(m , n , d , i , f);
		fill_by_percent(boardd , p);
		solve_board(boardd);
		break;		

		case('z'):
		board_t *boarddd = init_board(m,n,d,i,f);
	        fill_from_file(boarddd , l);
		printf("wsdf");
		solve_board(boarddd);
		break;	
		}

	}
	
	printf("argumenty to: %d %d %d %s %d %d %s\n" , m , n , i ,f ,d ,p ,l);	
	/*
	int m = 10;
	int n = 10;
	int i = 5;
	int d = TOP;
	char *f = malloc(sizeof(char)*128);
	strcpy(f , "stdout");
	board_t *board = init_board(m , n , d , i , f);
	fill_with_whites(board);
	solve_board(board);
	*/	
	
	return 0;
}
