/*
 ============================================================================
 Name        : ex13.c
 Author      : Kamae Ryo b9122014
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define OVERALL_SIZE 9
#define BOX_SIZE 3

void display(int *board){
	int i;
	for(i = 0;i < OVERALL_SIZE * OVERALL_SIZE;i++){
		printf("%d", board[i]);
		if(i % BOX_SIZE == BOX_SIZE - 1){
			printf(" ");
		}
		if(i % OVERALL_SIZE == OVERALL_SIZE - 1){
			printf("\n");
		}
	}
}

int canPut(int *board, int place, int number){
	int row = place / OVERALL_SIZE;
	int column = place % OVERALL_SIZE;
	int box = (row / BOX_SIZE) * BOX_SIZE * OVERALL_SIZE + (column / BOX_SIZE) * BOX_SIZE;
	int i;
	for(i = 0;i < OVERALL_SIZE;i++){
		if(board[row * OVERALL_SIZE + i] == number){
			return 0;
		}
		if(board[column + i * OVERALL_SIZE] == number){
			return 0;
		}
		if(board[box + (i / BOX_SIZE) * OVERALL_SIZE + (i % BOX_SIZE)] == number){
			return 0;
		}
	}
	return 1;
}

void solve(int *board, int place){
	if(place == OVERALL_SIZE * OVERALL_SIZE){
		display(board);
		printf("\n");
	}

	int newPlace;
	for(newPlace = place;newPlace < OVERALL_SIZE * OVERALL_SIZE;newPlace++){
		if(!board[newPlace]){
			break;
		}
	}

	int i;
	for(i = 1;i <= 9;i++){
		if(canPut(board, newPlace, i)){
			board[newPlace] = i;
			solve(board, newPlace + 1);
			board[newPlace] = 0;
		}
	}
}

int main() {
	int board[OVERALL_SIZE * OVERALL_SIZE] = {
	    1,0,0,0,0,7,0,9,0,
	    0,3,0,0,2,0,0,0,8,
	    0,0,9,6,0,0,5,0,0,
	    0,0,5,3,0,0,9,0,0,
	    0,1,0,0,8,0,0,0,2,
	    6,0,0,0,0,4,0,0,0,
	    3,0,0,0,0,0,0,1,0,
	    0,4,0,0,0,0,0,0,7,
	    0,0,7,0,0,0,3,0,0
	};
	solve(board, 0);
	return 0;
}
