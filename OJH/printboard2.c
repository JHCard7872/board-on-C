#include <stdio.h>
#include <windows.h>

#define WHITE 7
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6

struct board {
	char name[16];
	int num;
	int build;
	int value;
	int pass_value;
	char player;
	int sell_value;
	struct board* get_player;
};


void print_board(void);
void printcolor(int color);

int main(void) {

	//y축 21칸 x축 81칸
	print_board();
	// 나중에 플레이어 위치, 땅값 구현할것.
}

char board[5][10][36] = { 0, };


char boardpan[50][100];
void board_update(char*** boards) {
	int a = 0;
	for (int i = 9; i > 0; i--) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 10; k++) {
				boardpan[45 + j][i * 10 + k] = boards[j][k][a];
			}
		}
		a++;
	}
	for (int i = 9; i > 0; i--) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 10; k++) {
				boardpan[i * 5 + j][90 + k] = boards[j][k][a];
			}
		}
		a++;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 10; k++) {
				boardpan[j][i * 10 + k] = boards[j][k][a];
			}
		}
		a++;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 10; k++) {
				boardpan[i * 5 + j][90 + k] = boards[j][k][a];
			}
		}
		a++;
	}
}
/*
void print_board(void) {
	char boardpan[31][160] = {
	"┏    18    ┳    19    ┳    20    ┳    21    ┳    22    ┳    23    ┳    24    ┳    25    ┳    26    ┳    27    ┓",
	"┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃",
	"  000000000  000000000  000000000  000000000  000000000  000000000  000000000  000000000  000000000    price   ",
	"┠    17    ╋  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ╋    28    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    16    ┫                                                                                       ┠    29    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    15    ┫                                                                                       ┠    30    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    14    ┫                                                                                       ┠    31    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    13    ┫                                                                                       ┠    32    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    12    ┫                                                                                       ┠    33    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    11    ┫                                                                                       ┠    34    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠    10    ┫                                                                                       ┠    35    ┫",
	"┃  country ┃                                                                                       ┃  country ┃",
	"  000000000                                                                                          000000000 ",
	"┠     9    ╋     8    ┳     7    ┳     6    ┳     5    ┳     4    ┳     3    ┳     2    ┳     1    ╋     0    ┫",
	"┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃  country ┃",
	"  000000000  000000000  000000000  000000000  000000000  000000000  000000000  000000000  000000000    price   ",
	"┗  ─   ─   ┸  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┻  ─   ─   ┛"
	};
	for (int i = 0; i < 30; i = i + 3)
	{
		printf("%s\n", boardpan[i]);
		if (i == 0)
		{
			for (int j = 0; j < 10; j++)
			{
				printf("   "); printcolor(BLUE); printf("%c ", '*'); printcolor(RED); printf("%c ", '*'); printcolor(GREEN); printf("%c ", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
			}

		}
		else if (i > 0 && i < 27)
		{
			printf("   "); printcolor(BLUE); printf("%c ", '*'); printcolor(RED); printf("%c ", '*'); printcolor(GREEN); printf("%c ", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
			printf("                                                                                        ");
			printf("   "); printcolor(BLUE); printf("%c ", '*'); printcolor(RED); printf("%c ", '*'); printcolor(GREEN); printf("%c ", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				printf("   "); printcolor(BLUE); printf("%c ", '*'); printcolor(RED); printf("%c ", '*'); printcolor(GREEN); printf("%c ", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
			}
		}
		printf("\n");
		printf("%s\n", boardpan[i + 1]);
		printf("%s\n", boardpan[i + 2]);
	}
	printf("%s\n", boardpan[30]);

}
*/

void printcolor(int color) {
	if (color == WHITE)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else if (color == BLUE)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	}
	else if (color == GREEN)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	}
	else if (color == RED)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	}
	else if (color == YELLOW)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	}
}