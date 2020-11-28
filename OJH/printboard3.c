#include <stdio.h>
#include <windows.h>

#define WHITE 7
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6



struct board { // ���弿 ����ü
	char name[16];
	int num;
	int build;
	int value;
	int pass_value;
	int sell_value;
	struct player* get_player;
};

struct player { // �÷��̾� ����ü
	int color;
	int money;
	int location;
	struct board* player_board[20];
};

struct board boardCell[36] = { // ���弿�� �ʱ�ȭ
		{"start", 0, 0, 0, 0, 0, NULL},
		{"Taiwan", 1, 0, 50000, 2000, 25000, NULL},
		{"Goldkey", 2, 0, 0, 0, 0, NULL},
		{"China", 3, 0, 80000, 4000, 40000, NULL},
		{"Philippines", 4, 0, 80000, 4000, 40000, NULL},
		{"Singapore", 5, 0, 100000, 6000, 50000, NULL},
		{"Goldkey", 6, 0, 0, 0, 0, NULL},
		{"Egypt", 7, 0, 100000, 6000, 50000, NULL},
		{"Turkey", 8, 0, 120000, 8000, 60000, NULL},
		{"Island", 9, 0, 0, 0, 0, NULL},
		{"Greece", 10, 0, 140000, 10000, 70000, NULL},
		{"Goldkey", 11, 0, 0, 0, 0, NULL},
		{"Denmark", 12, 0, 160000, 12000, 80000, NULL},
		{"Sweden", 13, 0, 160000, 12000, 80000, NULL},
		{"Switzerland", 14, 0, 180000, 14000, 90000, NULL},
		{"Goldkey", 15, 0, 0, 0, 0, NULL},
		{"Germany", 16, 0, 180000, 14000, 90000, NULL},
		{"Canada", 17, 0, 200000, 16000, 100000, NULL},
		{"GetFund", 18, 0, 0, 0, 0, NULL},
		{"Argentina", 19, 0, 220000, 18000, 110000, NULL},
		{"Goldkey", 20, 0, 0, 0, 0, NULL},
		{"Brazil", 21, 0, 240000, 20000, 120000, NULL},
		{"Australia", 22, 0, 240000, 20000, 120000, NULL},
		{"Hawai", 23, 0, 260000, 22000, 130000, NULL},
		{"Portugal", 24, 0, 260000, 22000, 130000, NULL},
		{"Goldkey", 25, 0, 0, 0, 0, NULL},
		{"Spain", 26, 0, 280000, 24000, 140000, NULL},
		{"Travel", 27, 0, 0, 0, 0, NULL},
		{"Japan", 28, 0, 300000, 26000, 150000, NULL},
		{"France", 29, 0, 320000, 28000, 160000, NULL},
		{"Italy", 30, 0, 320000, 28000, 160000, NULL},
		{"Goldkey", 31, 0, 0, 0, 0, NULL},
		{"UK", 32, 0, 350000, 35000, 175000, NULL},
		{"USA", 33, 0, 350000, 35000, 175000, NULL},
		{"Fund", 34, 0, 0, 0, 0, NULL},
		{"Korea", 35, 0, 1000000, 2000000, 500000, NULL}
};

struct player play[4] = { 0 };

char boardpan[41][143] = { // �������� ���ڿ�
	"��    18    ��    19    ��    20    ��    21    ��    22    ��    23    ��    24    ��    25    ��    26    ��    27    ��",
	"                                                                                                               ",
	"��  GetFund �� Argentina��  Goldkey ��   Brazil �� Australia��   Hawai  �� Portugal ��  Goldkey ��   Spain  ��  Travel  ��",
	"              220,000               240,000    240,000    260,000    260,000               280,000             ",
	"��    17    ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��    28    ��",
	"                                                                                                               ",
	"��   Canada ��                                                                                       ��   Japan  ��",
	"   200,000                                                                                            300,000  ",
	"��    16    ��                                                                                       ��    29    ��",
	"                                                                                                               ",
	"��  Germany ��                                                                                       ��   France ��",
	"   180,000                                                                                            320,000  ",
	"��    15    ��                                                                                       ��    30    ��",
	"                                                                                                               ",
	"��  Goldkey ��                                                                                       ��   Italy  ��",
	"                                                                                                      320,000  ",
	"��    14    ��                                                                                       ��    31    ��",
	"                                                                                                               ",
	"��Switzeland��                                                                                       ��  Goldkey ��",
	"   180,000                                                                                                    ",
	"��    13    ��                                                                                       ��    32    ��",
	"                                                                                                               ",
	"��   Sweden ��                                                                                       ��    UK    ��",
	"   160,000                                                                                            350,000  ",
	"��    12    ��                                                                                       ��    33    ��",
	"                                                                                                               ",
	"��  Denmark ��                                                                                       ��    USA   ��",
	"   160,000                                                                                            350,000  ",
	"��    11    ��                                                                                       ��    34    ��",
	"                                                                                                               ",
	"��  Goldkey ��                                                                                       ��   Fund   ��",
	"                                                                                                               ",
	"��    10    ��                                                                                       ��    35    ��",
	"                                                                                                               ",
	"��   Greece ��                                                                                       ��   Korea  ��",
	"   140,000                                                                                           1,000,000 ",
	"��     9    ��     8    ��     7    ��     6    ��     5    ��     4    ��     3    ��     2    ��     1    ��     0    ��",
	"                                                                                                               ",
	"��   Island ��   Turkey ��   Egypt  ��  Goldkey �� singapore��Philippine��   China  ��  Goldkey ��   Taiwan ��   start  ��",
	"               120,000   100,000               100,000     80,000     80,000                50,000             ",
	"��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��  ��   ��   ��"
};

void print_board(void); // ������ ������ִ� �Լ�
void printcolor(int color); // �� �ٲ��ִ� �Լ�
void movePlayer(struct player* playerLocation, int playerNum); // �÷��̾��� ��ġ�� ���� ���ڿ� * ��ȭ

int main(void) {

	play[0].location = 3;
	play[1].location = 0;
	play[2].location = 0;
	play[3].location = 0;
	play[0].player_board[0] = &boardCell[3];

	movePlayer(&play[0], 1);
	movePlayer(&play[1], 2);
	movePlayer(&play[2], 3);
	movePlayer(&play[3], 4);

	//y�� 21ĭ x�� 81ĭ
	print_board();
	// ���߿� �÷��̾� ��ġ, ���� �����Ұ�.
}

void print_board(void) { // ������ ���

	for (int i = 0; i < 41; i++)
	{
		if (i % 4 == 1) // �÷��̾� ��ġ�� �˷��ִ� *�� ������ִ� �ڸ�
		{
			for (int j = 0; j < 110; j++)
			{
				if (j % 11 == 3) { printcolor(BLUE); printf("%c", boardpan[i][j]);  printcolor(WHITE); } // *�� ��µǴ� ��ġ�� ���� ���� ���
				else if (j % 11 == 5) { printcolor(RED); printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 7) { printcolor(GREEN); printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 9) { printcolor(YELLOW); printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else printf("%c", boardpan[i][j]);
			}

			if (i == 5)
			{
				printf("\tplayer     ��ġ       �����ݾ�              ���� ��(�����)      ");
			}
		}
		else if (i == 7)
		{
			printf("%s\t", boardpan[i]);
			printcolor(BLUE);
			printf("Blue");
			printcolor(WHITE);
			printf("         %d         %d            ", play[0].location,play[0].money);
			printf("%s(%d)", play[0].player_board[0]->name,play[0].player_board[0]->pass_value);
		}
		else printf("%s", boardpan[i]);

		printf("\n");
	}

	//"' '3* * * *" >> 1ĭ

}
void movePlayer(struct player* playerLocation, int playerNum) { // �÷��̾��� ��ġ�� ���� '*'��ȣ�� ���ڿ��� ���������

	if (playerLocation->location >= 0 && playerLocation->location <= 9)
	{
		boardpan[37][(playerNum * 2 + 1) + 11 * (9 - playerLocation->location)] = '*';
	}
	else if (playerLocation->location >= 10 && playerLocation->location <= 17)
	{
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 1)] = '*';
	}
	else if (playerLocation->location >= 18 && playerLocation->location <= 27)
	{
		boardpan[1][(playerNum * 2 + 1) + (11 * (playerLocation->location - 18))] = '*';
	}
	else if (playerLocation->location >= 28 && playerLocation->location <= 35)
	{
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 99] = '*';
	}

}

void printcolor(int color) { // �� �ٲ��ִ� �Լ�.
	if (color == WHITE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	else if (color == BLUE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	else if (color == GREEN) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	else if (color == RED) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	else if (color == YELLOW) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
}