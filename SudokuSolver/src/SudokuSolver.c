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

void errorMessage(int i, int j, int k)//数字の重複についての指摘を出力
{
	char pattern[] = "column";
	if(k == 0)//どこで重複しているかを判別
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
}

int check(int *board)
{
	int count[3] = {0, 0, 0};
	int i, j, k;
	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE; i++)
	{
		if(!(0 <= board[i] && board[i] <= 9))//範囲外の入力もしくは情報の不足を判別
		{
			printf("Please follow the input format.\n");
			return 0;
		}
	}

	for(i = 0; i < OVERALL_SIZE; i++)//入力時点での数字の重複がないかを走査
	{
		for(j = 0; j < OVERALL_SIZE; j++)
		{
			for(k = 0; k < OVERALL_SIZE; k++)
			{
				if(board[(i * OVERALL_SIZE) + k] == j + 1)//列についての確認
				{
					count[0]++;
				}
				if(board[i + (k * OVERALL_SIZE)] == j + 1)//行についての確認
				{
					count[1]++;
				}
				if(board[((i / BOX_SIZE) * BOX_SIZE * OVERALL_SIZE) + ((i % BOX_SIZE) * BOX_SIZE) + ((k / BOX_SIZE) * OVERALL_SIZE) + (k % BOX_SIZE)] == j + 1)//箱についての確認
				{
					count[2]++;
				}
			}
			for(k = 0; k < 3; k++)
			{
				if(count[k] >= 2)//同じ数字が2つ以上ある場合指摘
				{
					errorMessage(i, j, k);
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
	printf("075090000\n");
	printf("902100030\n");
	printf("006040001\n");
	printf("010023000\n");
	printf("060000080\n");
	printf("500900002\n");
	printf("000500270\n");
	printf("001000809\n");
	printf("000060040\n");
	printf("This is the input format.\n\n");

	printf("Please input and press enter.\n");
	char problem[OVERALL_SIZE][OVERALL_SIZE];//ユーザーの入力を格納する配列
	int i;
	for(i = 0; i < OVERALL_SIZE; i++)//1行ずつ受け取る
	{
		scanf("%s", problem[i]);
	}
	printf("\n");
	for(i = 0; i < OVERALL_SIZE * OVERALL_SIZE; i++)
	{
		board[i] = problem[i / OVERALL_SIZE][i % OVERALL_SIZE] - '0';//文字列を数値に変換する
	}
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