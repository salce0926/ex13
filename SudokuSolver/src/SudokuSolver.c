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

void display(int *board)//表示用の関数
{
	int i;
	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE; i++)
	{
		printf("%d", board[i]);//一文字づつ出力
		if(i % OVERALL_SIZE == OVERALL_SIZE - 1)//9文字で改行
		{
			printf("\n");
		}
	}
}

int canPut(int *board, int place, int number)//指定した場所に指定した数字を置けるか調べる関数
{
	//placeで指定された場所から行、列、箱を特定する
	int row 	= place / OVERALL_SIZE;
	int column 	= place % OVERALL_SIZE;
	int box 	= ((row / BOX_SIZE) * BOX_SIZE * OVERALL_SIZE) + ((column / BOX_SIZE) * BOX_SIZE);

	int i;
	for(i = 0; i < OVERALL_SIZE; i++)
	{
		if(board[(row * OVERALL_SIZE) + i] == number)//同じ行に同じ数字がある場合falseを返す
		{
			return 0;
		}
		if(board[column + (i * OVERALL_SIZE)] == number)//同じ列に同じ数字がある場合falseを返す
		{
			return 0;
		}
		if(board[box + ((i / BOX_SIZE) * OVERALL_SIZE) + (i % BOX_SIZE)] == number)//同じ箱に同じ数字がある場合falseを返す
		{
			return 0;
		}
	}
	return 1;//ここまで来られるということは置けるのでtrueを返す
}

int solve(int *board, int place)//実際に解くための再帰関数
{
	//この関数は、1~9をひたすら当てはめながら次のマスへと進んでいく関数である。
	//闇雲に置いていると無駄な処理が多くなるため、canPut関数によって既に置けない数字を省いている。
	//どの数字も置けなくなった場合そのマスを0に戻し、１つ前に戻る(バックトラック)

	if(place == OVERALL_SIZE * OVERALL_SIZE)//9*9の最後まで終わったなら解けているのでtrueを返す
	{
		return 1;
	}

	int newPlace;
	for(newPlace = place; newPlace < OVERALL_SIZE * OVERALL_SIZE; newPlace++)//まだ埋まっていないマスを探す
	{
		if(!board[newPlace])//0であるマスでforから抜ける
		{
			break;
		}
	}

	int i;
	for(i = 1; i <= OVERALL_SIZE; i++)//newPlaceに入る数字を実際に入れてみる
	{
		if(canPut(board, newPlace, i))//iをnewPlaceに置けるか調べる
		{
			board[newPlace] = i;//置けるので、置いてみる
			if(solve(board, newPlace + 1))//そのままplaceを次に進める
			{
				return 1;//上手くいったらtrueを返す
			}
			board[newPlace] = 0;//上手くいかなかったら0に戻して次を試す
		}
	}
	return 0;//どの数も置けなかったのでfalseを返す
}

int check(int *board)
{
	int count[3] = {0, 0, 0};
	int i, j, k;
	for(i = 0; i < OVERALL_SIZE; i++)
	{
		for(j = 0; j < OVERALL_SIZE; j++)
		{
			for(k = 0; k < OVERALL_SIZE; k++)
			{
				if(board[(i * OVERALL_SIZE) + k] == j + 1)
				{
					count[0]++;
				}
				if(board[i + (k * OVERALL_SIZE)] == j + 1)
				{
					count[1]++;
				}
				if(board[((i / BOX_SIZE) * BOX_SIZE * OVERALL_SIZE) + ((i % BOX_SIZE) * BOX_SIZE) + ((k / BOX_SIZE) * OVERALL_SIZE) + (k % BOX_SIZE)] == j + 1)
				{
					count[2]++;
				}
			}
			for(k = 0; k < 3; k++)
			{
				if(count[k] >= 2)
				{
					char pattern[] = "column";
					if(k == 0)
					{
						pattern[0] = 'r';
						pattern[2] = 'w';
						pattern[3] = '\0';
					}
					else if(k == 2)
					{
						pattern[0] = 'b';
						pattern[2] = 'x';
						pattern[3] = '\0';
					}
					printf("Number is already duplicated.\n");
					printf("pattern: %s\nplace: %d\nnumber: %d\n", pattern, i, j + 1);
					return 0;
				}
				count[k] = 0;
			}
		}
	}
	return 1;
}

int input(int *board)//入力用の関数
{
	char problem[OVERALL_SIZE][OVERALL_SIZE];//ユーザーの入力を格納する配列
	int i, j;
	for(i = 0; i < OVERALL_SIZE; i++)//1行ずつ受け取る
	{
		scanf("%s", problem[i]);
	}
	printf("\n");
	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE; i++)
	{
		board[i] = problem[i / OVERALL_SIZE][i % OVERALL_SIZE] - '0';//文字列を数値に変換する
	}
//	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE; i++)//現時点で問題として成立しているかを確認する(現在実装中で、以下のコードは無能)
//	{
//		int check = 0;
//		for(j = 1; j <= OVERALL_SIZE; j++)//checkはi番目のマスにいくつの数字が置けるかを格納する変数
//		{
//			check += canPut(board, i, j);
//		}
//		if(check == 0)
//		{
//			return 0;//ここに入る場合、どの数字も置けないマスが既に存在しているのでfalseを返す
//		}
//	}
	return 1;
}


int main() 
{
	int board[OVERALL_SIZE * OVERALL_SIZE];//解いた結果を格納する配列
	if(input(board) && check(board) && solve(board, 0))//解ける問題かどうかの確認(実際に解いてみる)
	{
		display(board);
		printf("This problem can be solved.\n");
	}
	else
	{
		printf("This problem can NOT be solved.\n");
	}
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
