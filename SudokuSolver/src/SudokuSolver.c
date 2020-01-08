/*
 ============================================================================
 Name        : SudokuSolver.c
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
//		if(i % BOX_SIZE == BOX_SIZE - 1){
//			printf(" ");
//		}
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

int solve(int *board, int place){
	if(place == OVERALL_SIZE * OVERALL_SIZE){
		return 1;
		// display(board);
		// printf("\n");
	}

	int newPlace;
	for(newPlace = place;newPlace < OVERALL_SIZE * OVERALL_SIZE;newPlace++){
		if(!board[newPlace]){
			break;
		}
	}

	int i;
	for(i = 1;i <= OVERALL_SIZE;i++){
		if(canPut(board, newPlace, i)){
			board[newPlace] = i;
			if(solve(board, newPlace + 1)){
				return 1;
			}
			// solve(board, newPlace + 1);
			board[newPlace] = 0;
		}
	}
	return 0;
}

int main() {
	char input[OVERALL_SIZE][OVERALL_SIZE];
	int i;
	for(i = 0;i < OVERALL_SIZE;i++){
		scanf("%s", input[i]);
	}
	printf("\n");
	int board[OVERALL_SIZE * OVERALL_SIZE];
	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE;i++){
		board[i] = input[i / OVERALL_SIZE][i % OVERALL_SIZE] - '0';
	}
	if(solve(board, 0)){
		display(board);
		printf("This problem can be solved.\n");
	}else{
		printf("This problem can NOT be solved.\n");
	}
	// solve(board, 0);
	return 0;
}

/*
075090000
902100030
006040001
010023000
060000080
500900002
000500270
001000809
000060040

175396428
942178536
386245791
817623954
269451387
534987612
698514273
451732869
723869145
This problem can be solved.
*/
