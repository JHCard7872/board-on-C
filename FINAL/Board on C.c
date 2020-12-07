#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define WHITE 7
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6
#define BLACK 0

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void intro() {
	//printf("Board on C\n");
	printf("rod bacon\n");
	Sleep(300);
	for (int i = 4; i >= 0; i--) {
		Sleep(300);
		system("cls");
		printf("rod  acon");
		gotoxy(i, 1);
		printf("b");
	}
	Sleep(300);
	system("cls");
	printf(" rod acon");
	gotoxy(0, 1);
	printf("b");

	Sleep(300);
	system("cls");
	printf("brod acon");

	Sleep(300);
	system("cls");
	printf("brodacon");

	Sleep(300);
	system("cls");
	printf("b odacon");
	gotoxy(1, 1);
	printf("r");

	Sleep(300);
	system("cls");
	printf("bo dacon");
	gotoxy(2, 1);
	printf("r");

	Sleep(300);
	system("cls");
	printf("bordacon");

	Sleep(300);
	system("cls");
	printf("bord con");
	gotoxy(4, 1);
	printf("a");

	for (int i = 3; i >= 2; i--) {
		Sleep(300);
		system("cls");
		printf("bord con");
		gotoxy(i, 1);
		printf("a");
	}

	Sleep(300);
	system("cls");
	printf("bo rdcon");
	gotoxy(2, 1);
	printf("a");

	Sleep(300);
	system("cls");
	printf("boardcon");

	for (int i = 5; i <= 9; i++) {
		Sleep(300);
		system("cls");
		printf("board on");
		gotoxy(i, 1);
		printf("c");
	}

	Sleep(300);

	for (int i = 5; i > 0; i--) {
		system("cls");
		printf("board on c\n");
		printf("Starts in %d seconds", i);
		Sleep(1000);
	}
	system("cls");
	printf("board on c\n");
	printf("Game start!");
	Sleep(1000);
}

struct board { // ���弿 ����ü
	char name[16]; // �̸�
	int num; // ��ȣ
	int build; // �ǹ�����(1 >> ����� // 2 >> ����1�� // 3 >> ����2�� // 4 >> ����1�� // 5 >> ȣ��1��)
	int pass_villa1; // ���� 1���϶� �����
	int pass_villa2; // ���� 2���϶� �����
	int pass_building; // ���� 1���϶� �����
	int pass_hotel; // ȣ�� 1���϶� �����
	int value; // ����
	int pass_value; // �����
	int pass_value2; // ����� ó������ �������ִ� ����
	int sell_value; // �ȶ��� ����
	struct player* get_player;
};

struct player { // �÷��̾� ����ü
	int haveBoard; // �������ִ� ���� ����
	int color; // �÷��̾��� ��
	int money; // �����ݾ�
	int location; // ��ġ
	int count;
	struct board* player_board[20]; // �����ϰ��ִ� ���� ����ü�ּ�
};

struct board boardCell[36] = { // ���弿�� �ʱ�ȭ
		{"start", 0, 0, 0, 0, 0, 0, 0, 0,0, 0, NULL},
		{"Taiwan", 1, 0, 10000, 20000, 90000, 250000, 50000, 2000, 2000, 25000, NULL},
		{"Goldkey", 2, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"China", 3, 0, 20000, 40000, 180000, 450000, 80000, 4000,4000, 40000, NULL},
		{"Philippines", 4, 0, 20000, 40000, 180000, 450000, 80000, 4000,4000, 40000, NULL},
		{"Singapore", 5, 0, 30000, 60000, 270000, 550000, 100000, 6000,6000, 50000, NULL},
		{"Goldkey", 6, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Egypt", 7, 0, 30000, 60000, 270000, 550000, 100000, 6000,6000, 50000, NULL},
		{"Turkey", 8, 0, 40000, 80000, 300000, 600000, 120000, 8000,8000, 60000, NULL},
		{"Island", 9, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Greece", 10, 0, 50000, 100000, 450000, 750000, 140000, 10000,10000, 70000, NULL},
		{"Goldkey", 11, 0, 0, 0, 0, 0, 0, 0,0, 0, NULL},
		{"Denmark", 12, 0, 60000, 120000, 500000, 900000, 160000, 12000,12000, 80000, NULL},
		{"Sweden", 13, 0, 60000, 120000, 500000, 900000, 160000, 12000,12000, 80000, NULL},
		{"Switzerland", 14, 0, 70000, 140000, 500000, 950000, 180000, 14000,14000, 90000, NULL},
		{"Goldkey", 15, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Germany", 16, 0, 70000, 140000, 500000, 950000, 180000, 14000,14000, 90000, NULL},
		{"Canada", 17, 0, 80000, 160000, 550000, 1000000, 200000, 16000,16000, 100000, NULL},
		{"GetFund", 18, 0, 0, 0, 0, 0, 0, 0,0, 0, NULL},
		{"Argentina", 19, 0, 90000, 180000, 700000, 1050000, 220000, 18000,18000, 110000, NULL},
		{"Goldkey", 20, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Brazil", 21, 0, 100000, 200000, 750000, 1100000, 240000, 20000,20000, 120000, NULL},
		{"Australia", 22, 0, 100000, 200000, 750000, 1100000, 240000, 20000,20000, 120000, NULL},
		{"Hawai", 23, 0, 110000, 220000, 800000, 1150000, 260000, 22000,22000, 130000, NULL},
		{"Portugal", 24, 0, 110000, 220000, 800000, 1150000, 260000, 22000,22000, 130000, NULL},
		{"Goldkey", 25, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Spain", 26, 0, 120000, 240000, 850000, 1200000, 280000, 24000,24000, 140000, NULL},
		{"Travel", 27, 0, 0, 0, 0, 0, 0, 0, 0,0, NULL},
		{"Japan", 28, 0, 130000, 260000, 900000, 1270000, 300000, 26000,26000, 150000, NULL},
		{"France", 29, 0, 150000, 300000, 1000000, 1400000, 320000, 28000,28000, 160000, NULL},
		{"Italy", 30, 0, 150000, 300000, 1000000, 1400000, 320000, 28000,28000, 160000, NULL},
		{"Goldkey", 31, 0, 0, 0, 0, 0, 0, 0,0, 0, NULL},
		{"UK", 32, 0, 170000, 340000, 1100000, 1500000, 350000, 35000,35000, 175000, NULL},
		{"USA", 33, 0, 170000, 340000, 1100000, 1500000, 350000, 35000,35000, 175000, NULL},
		{"Fund", 34, 0, 0, 0, 0, 0, 0, 0,0, 0, NULL},
		{"Korea", 35, 0, 0, 0, 0, 0, 1000000, 2000000,2000000, 500000, NULL}
};

struct player play[4] = {
		{0, BLUE, 2000000, 0, 0, NULL},
		{0, RED, 2000000,0, 0, NULL},
		{0, GREEN, 2000000,0, 0, NULL},
		{0, YELLOW,2000000,0, 0, NULL}
};

char boardpan[41][255] = { // �������� ���ڿ�                                                                          /aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/
	"������  18 ������������  19 ������������  20 ������������  21 ������������  22 ������������  23 ������������  24 ������������  25 ������������  26 ������������  27 ��������    ����������������������������  ����������������������������", // 0
	"                                                                                                                   ��            ��  ��            ��", // 1 
	"��  GetFund �� Argentina��  Goldkey ��   Brazil �� Australia��   Hawai  �� Portugal ��  Goldkey ��   Spain  ��  Travel  ��    ��            ��  ��            ��", // 2
	"               220k                  240k       240k       260k       260k                  280k                   ��            ��  ��            ��", // 3
	"������  17 ��������  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ��������  28 ��������    ��            ��  ��            ��", // 4
	"                                                                                                                   ��            ��  ��            ��", // 5
	"��   Canada ��                                                                                       ��   Japan  ��    ����������������������������  ���������������������������� ", // 6
	"    200k                                                                                               300k        ",
	"������  16 ��������           player      ��ġ     �����ݾ�          ��������(�����)                     ������  29 ��������                                           ",//                  ����!", // blue �κ� e�κ���26
	"                                                                                                               ",
	"��  Germany ��                                                                                       ��   France ��                                                           ", // 10
	"    180k               Blue                                                                            320k                                                                           ",
	"������  15 ��������                                                                                       ������  30 ��������                                                                         ",
	"                                                                                                               ",
	"��  Goldkey ��                                                                                       ��   Italy  ��                                                           ",
	"                                                                                                       320k    ", // 15
	"������  14 ��������                                                                                       ������  31 ��������",
	"                       Red                                                                                     ",
	"��Switzeland��                                                                                       ��  Goldkey ��",
	"    180k                                                                                                       ",
	"������  13 ��������                                                                                       ������  32 ��������", //20
	"                                                                                                               ",
	"��   Sweden ��                                                                                       ��    UK    ��",
	"    160k               Green                                                                           350k    ",
	"������  12 ��������                                                                                       ������  33 ��������",
	"                                                                                                               ", // 25
	"��  Denmark ��                                                                                       ��    USA   ��",
	"    160k                                                                                               350k    ",
	"������  11 ��������                                                                                       ������  34 ��������",
	"                       Yellow                                                                                  ",
	"��  Goldkey ��                                                                                       ��   Fund   ��", // 30
	"                                                                                                               ",
	"������  10 ��������                                                                                       ������  35 ��������",
	"                                                                                                               ",
	"��   Greece ��                                                                                       ��   Korea  ��",
	"    140k                                                                                              1,000k   ", // 35
	"������   9  ����������   8  ����������   7  ����������   6   ��������   5  ����������   4  ����������   3 ������������   2  ����������   1  ����������   0  ������",
	"                                                                                                               ",
	"��   Island ��   Turkey ��   Egypt  ��  Goldkey �� singapore��Philippine��   China  ��  Goldkey ��   Taiwan ��   start  ��",
	"                120k       100k                  100k       80k        80k                   50k               ",
	"��  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��  ����  ��   ��   ��" //40
};

int fund = 0;

void print_board(void); // ������ ������ִ� �Լ�
void printcolor(int color); // �� �ٲ��ִ� �Լ�
void movePlayer(struct player* playerLocation, int playerNum); // �÷��̾��� ��ġ�� ���� ���ڿ� * ��ȭ
void printHaveBoard(int i, int j, int player, struct player* playerHaveBoard); // ����� �������ִ� �ǹ��� ����� ���
void printBuild(struct player* playerBoard); // �ǹ���ȣ ������ִ°�
int Dice_Move(struct player* player_locate, int* i, int k); // �ֻ��� ������
void Island(int* count);
void GoldenKey(struct player* player_); // Ȳ�� ����
void print_string(char* str, int number); // ���ڿ� ��½����ִ°�
void clear_string(void); // ���ڿ� ' '���� �ʱ�ȭ���ִ°�
void clear(int i, int j, int k);
void printPlayer(int k);
void printString(int i, int j, int k, char* name);
void buy(struct board* _boardCell, struct player* Player);
void build(struct board* _boardCell, struct player* Player);
void Pass(struct board* _boardCell, struct player* Player);
void print_clear(void);
void gameover(struct player* Player);
void Fund(struct player* p1);
void sell(struct board* _boardCell, struct player* Player);
void printBlue(void);
void printRed(void);
void printGreen(void);
void printYellow(void);
void printWin(void);


int main(void) {
	int k;
	system("mode con:cols=40 lines=2");
	system("pause");
	intro();
	system("mode con:cols=180 lines=80");
	char Gameover[] = "Game Over";
	srand((unsigned)time(NULL)); // ����
	int m = 0;
	print_board();

	while (1)
	{ // ������ ��� �ݺ�.
		k = 0; // k�� �̿��ؼ� �Ƹ� ���� ǥ��?
		int i = m % 4; // �÷��̾� ����
		int gameovercount = 0;
		for (int j = 0; j < 4; j++) // ���ӿ���
		{
			if (play[j].money <= 0)
			{
				gameover(&play[j]);
				play[j].color = BLACK;
				gameovercount++;
			}
		}
		if (play[i].money <= 0) { m++;  continue; }
		if (gameovercount >= 3) break;
		int ch = getchar(); // ����Ű �Է½� ����.
		print_clear();


		if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // �ֻ��� ������ // ���ϰ��� 0�� �ƴϸ� �ٽñ����� 0�̸� �� // �����̸� ���� 1 >> �ٽ� �ݺ�

			printBuild(&play[0]); // play0�� �ǹ� ����� ���
			printBuild(&play[1]);
			printBuild(&play[2]);
			printBuild(&play[3]);
			movePlayer(&play[0], 1); // �÷��̾� �̵��ϴ°� �������(���������)
			movePlayer(&play[1], 2);
			movePlayer(&play[2], 3);
			movePlayer(&play[3], 4);

			print_board(); // ������ ���
			if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
			if (boardCell[play[i].location].get_player != NULL)
			{
				build(boardCell, &play[i]);
			}
			buy(boardCell, &play[i]);
			if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
			print_clear;

			int ch = getchar(); // ���� �Է�

			if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // �ֻ��� ������ // ���ϰ��� 0�� �ƴϸ� �ٽñ����� 0�̸� �� // �����̸� ���� 1 >> �ٽ� �ݺ�

				printBuild(&play[0]); // play0�� �ǹ� ����� ���
				printBuild(&play[1]);
				printBuild(&play[2]);
				printBuild(&play[3]);
				movePlayer(&play[0], 1); // �÷��̾� �̵��ϴ°� �������(���������)
				movePlayer(&play[1], 2);
				movePlayer(&play[2], 3);
				movePlayer(&play[3], 4);

				print_board(); // ������ ���
				if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
				if (boardCell[play[i].location].get_player != NULL)
				{
					build(boardCell, &play[i]);
				}


				buy(boardCell, &play[i]);
				if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
				print_clear;
				int ch = getchar(); // ���� �Է�

				if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // �ֻ��� ������ // ���ϰ��� 0�� �ƴϸ� �ٽñ����� 0�̸� �� // �����̸� ���� 1 >> �ٽ� �ݺ�

					printBuild(&play[0]); // play0�� �ǹ� ����� ���
					printBuild(&play[1]);
					printBuild(&play[2]);
					printBuild(&play[3]);
					movePlayer(&play[0], 1); // �÷��̾� �̵��ϴ°� �������(���������)
					movePlayer(&play[1], 2);
					movePlayer(&play[2], 3);
					movePlayer(&play[3], 4);

					print_board();
					if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
					if (boardCell[play[i].location].get_player != NULL)
					{
						build(boardCell, &play[i]);
					}

					buy(boardCell, &play[i]);
					if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
					print_clear();
					int ch = getchar(); // ���� �Է�
				}
			}
		}

		printBuild(&play[0]); // play0�� �ǹ� ����� ���
		printBuild(&play[1]);
		printBuild(&play[2]);
		printBuild(&play[3]);
		movePlayer(&play[0], 1); // �÷��̾� �̵��ϴ°� �������(���������)
		movePlayer(&play[1], 2);
		movePlayer(&play[2], 3);
		movePlayer(&play[3], 4);

		print_board(); // ������ ���
		if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
		if (boardCell[play[i].location].get_player != NULL)
		{
			build(boardCell, &play[i]);
		}
		buy(boardCell, &play[i]);
		if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
		print_clear();
		m++;
	}
	system("cls");
	for (int n = 0; n < 4; n++)
	{
		if (play[n].money > 0)
		{
			if (n == 0) printBlue();
			else if (n == 1) printRed();
			else if (n == 2) printGreen();
			else printYellow();
		}
	}
	printWin();

}

void print_board(void) { // ������ ���
	if (play[0].haveBoard <= 4) // Blue ���� ���� >> printHaveBoard�Լ��κ� �ּ� ����. >> ����ؾ��� y���� ������ �ٸ��� ������ 4�� ���� ���� �Լ��� �������.
	{
		printHaveBoard(12, 30, play[0].haveBoard, &play[0]); // y������ 12��°, x������ 30��°�� ���ڿ� �������(���� �ǹ���)
	}
	else if (play[0].haveBoard <= 8)
	{
		printHaveBoard(12, 30, 4, &play[0]); // y������ 12����, x������ 30��°�� ���ڿ� �������.
		printHaveBoard(13, 23, play[0].haveBoard, &play[0]); // y�� 13����, x������ 23��°�� ���ڿ� ��� >> �̷������� �Ʒ��� ����
	}
	else if (play[0].haveBoard <= 12)
	{
		printHaveBoard(12, 30, 4, &play[0]);
		printHaveBoard(13, 23, 8, &play[0]);
		printHaveBoard(14, 25, play[0].haveBoard, &play[0]);
	}
	else if (play[0].haveBoard <= 16)
	{
		printHaveBoard(12, 30, 4, &play[0]);
		printHaveBoard(13, 23, 8, &play[0]);
		printHaveBoard(14, 25, 12, &play[0]);
		printHaveBoard(15, 23, play[0].haveBoard, &play[0]);
	}
	else
	{
		printHaveBoard(12, 30, 4, &play[0]);
		printHaveBoard(13, 23, 8, &play[0]);
		printHaveBoard(14, 25, 12, &play[0]);
		printHaveBoard(15, 23, 16, &play[0]);
		printHaveBoard(16, 30, play[0].haveBoard, &play[0]);
	}
	if (play[1].haveBoard <= 4) //------------------------------------------------- Red ���� ���� 
	{
		printHaveBoard(18, 25, play[1].haveBoard, &play[1]);
	}
	else if (play[1].haveBoard <= 8)
	{
		printHaveBoard(18, 25, 4, &play[1]);
		printHaveBoard(19, 23, play[1].haveBoard, &play[1]);
	}
	else if (play[1].haveBoard <= 12)
	{
		printHaveBoard(18, 25, 4, &play[1]);
		printHaveBoard(19, 23, 8, &play[1]);
		printHaveBoard(20, 30, play[1].haveBoard, &play[1]);
	}
	else if (play[1].haveBoard <= 16)
	{
		printHaveBoard(18, 25, 4, &play[1]);
		printHaveBoard(19, 23, 8, &play[1]);
		printHaveBoard(20, 30, 12, &play[1]);
		printHaveBoard(21, 23, play[1].haveBoard, &play[1]);
	}
	else
	{
		printHaveBoard(18, 25, 4, &play[1]);
		printHaveBoard(19, 23, 8, &play[1]);
		printHaveBoard(20, 30, 12, &play[1]);
		printHaveBoard(21, 23, 16, &play[1]);
		printHaveBoard(22, 25, play[1].haveBoard, &play[1]);
	}
	if (play[2].haveBoard <= 4) //----------------------------------------- Green ���� ����
	{
		printHaveBoard(24, 30, play[2].haveBoard, &play[2]);
	}
	else if (play[2].haveBoard <= 8)
	{
		printHaveBoard(24, 30, 4, &play[2]);
		printHaveBoard(25, 23, play[2].haveBoard, &play[2]);
	}
	else if (play[2].haveBoard <= 12)
	{
		printHaveBoard(24, 30, 4, &play[2]);
		printHaveBoard(25, 23, 8, &play[2]);
		printHaveBoard(26, 25, play[2].haveBoard, &play[2]);
	}
	else if (play[2].haveBoard <= 16)
	{
		printHaveBoard(24, 30, 4, &play[2]);
		printHaveBoard(25, 23, 8, &play[2]);
		printHaveBoard(26, 25, 12, &play[2]);
		printHaveBoard(27, 23, play[2].haveBoard, &play[2]);
	}
	else
	{
		printHaveBoard(24, 30, 4, &play[2]);
		printHaveBoard(25, 23, 8, &play[2]);
		printHaveBoard(26, 25, 12, &play[2]);
		printHaveBoard(27, 23, 16, &play[2]);
		printHaveBoard(28, 30, play[2].haveBoard, &play[2]);
	}
	if (play[3].haveBoard <= 4) // -----------------------------------------Yellow ���� ����
	{
		printHaveBoard(30, 25, play[3].haveBoard, &play[3]);
	}
	else if (play[3].haveBoard <= 8)
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, play[3].haveBoard, &play[3]);
	}
	else if (play[3].haveBoard <= 12)
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, 8, &play[3]);
		printHaveBoard(32, 30, play[3].haveBoard, &play[3]);
	}
	else if (play[3].haveBoard <= 16)
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, 8, &play[3]);
		printHaveBoard(32, 30, 12, &play[3]);
		printHaveBoard(33, 23, play[3].haveBoard, &play[3]);
	}
	else
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, 8, &play[3]);
		printHaveBoard(32, 30, 12, &play[3]);
		printHaveBoard(33, 23, 16, &play[3]);
		printHaveBoard(34, 25, play[3].haveBoard, &play[3]);
	}
	// ������� ��� �ǹ� ���.
	for (int i = 0; i < 41; i++) // ������� ������ ���(���κ� 10*10)
	{
		if (i % 4 == 1) // �÷��̾� ��ġ�� �˷��ִ� *�� ������ִ� �ڸ�
		{
			for (int j = 0; j < 250; j++)
			{
				if (j % 11 == 3 && j <= 114 && (i == 1 || i == 37)) { printcolor(play[0].color); printf("%c", boardpan[i][j]); } // �÷��̾� ��ġ �� ��µǴ� ��ġ�� ���� ���� ���
				else if (j % 11 == 4 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]);  printcolor(WHITE); }
				else if (j % 11 == 5 && j <= 114 && (i == 1 || i == 37)) { printcolor(play[1].color); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 6 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 7 && j <= 114 && (i == 1 || i == 37)) { printcolor(play[2].color); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 8 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 9 && j <= 114 && (i == 1 || i == 37)) { printcolor(play[3].color); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 10 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 3 || j == 102) { printcolor(BLUE); printf("%c", boardpan[i][j]); }
				else if (j == 4 || j == 103) { printf("%c", boardpan[i][j]);  printcolor(WHITE); }
				else if (j == 5 || j == 104) { printcolor(RED); printf("%c", boardpan[i][j]); }
				else if (j == 6 || j == 105) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 7 || j == 106) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j == 8 || j == 107) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 9 || j == 108) { printcolor(YELLOW); printf("%c", boardpan[i][j]); }
				else if (j == 10 || j == 109) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (i == 17 && j == 22) { printcolor(RED); printf("%c", boardpan[i][j]); } // Red ������ִ� �κ�(����������)
				else if (i == 17 && j == 27) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 17 && j >= 36 && j <= 65 && play[1].money > 0)
				{
					if (i == 17 && j == 36 && play[1].location > 9) { printf("%d", play[1].location); } // ��ġ ���
					else if (i == 17 && j == 38 && play[1].location > 9) { printf(""); }
					else if (i == 17 && j == 36 && play[1].location <= 9) { printf("%d", play[1].location); }
					else if (i == 17 && j == 45) { printf("%dk", play[1].money / 1000); } // ���� �ݾ� ���
					else if (i == 17 && j == 60)  printf("");
					else if (i == 17 && j == 62 && play[1].money > 9999 && play[1].money <= 99999) printf("");
					else if (i == 17 && j >= 62 && j <= 63 && play[1].money > 99999 && play[1].money <= 999999) { printf(""); }
					else if (i == 17 && j >= 62 && j <= 64 && play[1].money > 999999 && play[1].money <= 99999999) printf("");
					else if (i == 17 && j >= 62 && j <= 65 && play[1].money > 9999999 && play[1].money <= 999999999) printf("");
					else printf("%c", boardpan[i][j]);
				}
				else if (i == 17 && j >= 36 && j <= 39 && play[1].money <= 0) printf(" ");
				else if (i == 29 && j == 22) { printcolor(YELLOW); printf("%c", boardpan[i][j]); } // Green ������ִ� �κ�(�Ķ�������)
				else if (i == 29 && j == 29) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 29 && j >= 36 && j <= 65 && play[3].money > 0)
				{
					if (i == 29 && j == 36 && play[3].location > 9) { printf("%d", play[3].location); } // ��ġ ���
					else if (i == 29 && j == 38 && play[3].location > 9) { printf(""); }
					else if (i == 29 && j == 36 && play[3].location <= 9) { printf("%d", play[3].location); }
					else if (i == 29 && j == 45) { printf("%dk", play[3].money / 1000); } // ���� �ݾ� ���
					else if (i == 29 && j == 60)  printf("");
					else if (i == 29 && j == 62 && play[3].money > 9999 && play[3].money <= 99999) printf("");
					else if (i == 29 && j >= 62 && j <= 63 && play[3].money > 99999 && play[3].money <= 999999) { printf(""); }
					else if (i == 29 && j >= 62 && j <= 64 && play[3].money > 999999 && play[3].money <= 99999999) printf("");
					else if (i == 29 && j >= 62 && j <= 65 && play[3].money > 9999999 && play[3].money <= 999999999) printf("");
					else printf("%c", boardpan[i][j]);
				}
				else if (i == 29 && j >= 36 && j <= 39 && play[3].money <= 0) printf(" ");
				else printf("%c", boardpan[i][j]);
			}
		}

		else if (i == 10) // �� ������ �ֻ��� �غκ� �÷��̾� ��Ȳ �����ֱ� ����.
		{
			for (int j = 0; j < 180; j++)
			{
				if (j == 119 && (boardpan[10][120] == 'B')) { printcolor(BLUE); printf("%c", boardpan[i][j]); }
				else if (j == 119 && (boardpan[10][120] == 'R')) { printcolor(RED); printf("%c", boardpan[i][j]); }
				else if (j == 119 && (boardpan[10][120] == 'G')) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j == 119 && (boardpan[10][120] == 'Y')) { printcolor(YELLOW); printf("%c", boardpan[i][j]); }
				else if (j == 126) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i == 11) // Blue������ִ� �κ�(���� �ݾ�, �ǹ� ���(���弿�� �����ִ� �ǹ�))
		{
			for (int j = 0; j < 255; j++)
			{
				if (j == 22) { printcolor(BLUE); printf("%c", boardpan[i][j]); }
				else if (j == 27) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (j >= 36 && j <= 65 && play[0].money > 0)
				{
					if (j == 36 && play[0].location > 9) { printf("%d", play[0].location); } // ��ġ ���
					else if (j == 38 && play[0].location > 9) { printf(""); }
					else if (j == 36 && play[0].location <= 9) { printf("%d", play[0].location); }
					else if (j == 45) { printf("%dk", play[0].money / 1000); } // ���� �ݾ� ���
					else if (j == 60)  printf("");
					else if (j == 62 && play[0].money > 9999 && play[0].money <= 99999) printf("");
					else if (j >= 62 && j <= 63 && play[0].money > 99999 && play[0].money <= 999999) { printf(""); }
					else if (j >= 62 && j <= 64 && play[0].money > 999999 && play[0].money <= 99999999) printf("");
					else if (j >= 62 && j <= 65 && play[0].money > 9999999 && play[0].money <= 999999999) printf("");
					else printf("%c", boardpan[i][j]);
				}
				else if (j >= 80 && j <= 83 && play[3].money <= 0) printf(" ");
				else if (j >= 36 && j <= 39 && play[0].money <= 0) printf(" ");
				else if ((j == 1 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); } // ������� �ǹ� ���. �� �ǹ��� ���� �÷��̾��� ����ü�� ã�ư� �� ���
				else if (j == 2 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i == 23) // Green ������ִ� �κ�(���� �ݾ�, �ǹ� ���(���弿�� �����ִ� �ǹ�))
		{
			for (int j = 0; j < 180; j++)
			{
				if ((j == 1 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); } // ������� �ǹ� ���. �� �ǹ��� ���� �÷��̾��� ����ü�� ã�ư� �� ���
				else if (j == 2 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 21) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j == 29) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (j >= 36 && j <= 65 && play[2].money > 0)
				{
					if (j == 36 && play[2].location > 9) { printf("%d", play[2].location); } // ��ġ ���
					else if (j == 38 && play[2].location > 9) { printf(""); }
					else if (j == 36 && play[2].location <= 9) { printf("%d", play[2].location); }
					else if (j == 45) { printf("%dk", play[2].money / 1000); } // ���� �ݾ� ���
					else if (j == 60)  printf("");
					else if (j == 62 && play[2].money > 9999 && play[2].money <= 99999) printf("");
					else if (j >= 62 && j <= 63 && play[2].money > 99999 && play[2].money <= 999999) { printf(""); }
					else if (j >= 62 && j <= 64 && play[2].money > 999999 && play[2].money <= 99999999) printf("");
					else if (j >= 62 && j <= 65 && play[2].money > 9999999 && play[2].money <= 999999999) printf("");
					else printf("%c", boardpan[i][j]);
				}
				else if (j >= 36 && j <= 39 && play[2].money <= 0) printf(" ");
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i % 4 == 3) // �ǹ� ������ִ� �κ�.
		{
			for (int j = 0; j < 250; j++)
			{

				if (j % 11 == 1 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // �ǹ� ��ĥ�ϱ�(�պκ�)
				else if (j % 11 == 2 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // �ǹ� ��ĥ�ϱ�(�޺κ�)
				else if (j % 11 == 0 && j <= 114 && i == 3 && (boardCell[17 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 1 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // �ǹ� ��ĥ�ϱ�(�պκ�)
				else if (j % 11 == 2 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // �ǹ� ��ĥ�ϱ�(�޺κ�)
				else if (j % 11 == 0 && j <= 114 && i == 39 && (boardCell[10 - j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 1 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 2 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else printf("%c", boardpan[i][j]);
			}
		}

		else // ������ ���
		{
			for (int j = 0; j < 250; j++)
			{
				printf("%c", boardpan[i][j]);
			}
		}

		printf("\n");
	}
}

void movePlayer(struct player* playerLocation, int playerNum) { // �÷��̾��� ��ġ�� ���� '��'��ȣ�� ���ڿ��� ���������
	char buf[2] = "��";
	for (int i = 0; i < 10; i++) // �켱 ���� �ʱ�ȭ. (�̵��Ҷ� ����� �Ǹ� �ȵǱ� ����.)
	{
		boardpan[37][1 + 2 * playerNum + 11 * i] = ' ';
		boardpan[37][2 + 2 * playerNum + 11 * i] = ' ';
		boardpan[1][1 + 2 * playerNum + 11 * i] = ' ';
		boardpan[1][2 + 2 * playerNum + 11 * i] = ' ';
	}
	for (int i = 0; i < 8; i++)
	{
		boardpan[5 + 4 * i][1 + 2 * playerNum] = ' ';
		boardpan[5 + 4 * i][2 + 2 * playerNum] = ' ';
		boardpan[5 + 4 * i][100 + 2 * playerNum] = ' ';
		boardpan[5 + 4 * i][101 + 2 * playerNum] = ' ';
	}
	if (playerLocation->location >= 0 && playerLocation->location <= 9) // �÷��̾� ��ġ�� 0~9�϶� �ش��ϴ� ���ڿ�(��µǴ� ��ġ)
	{
		boardpan[37][(playerNum * 2 + 1) + 11 * (9 - playerLocation->location)] = buf[0];
		boardpan[37][(playerNum * 2 + 2) + 11 * (9 - playerLocation->location)] = buf[1];

	}
	else if (playerLocation->location >= 10 && playerLocation->location <= 17) // �÷��̾� ��ġ�� 10~17�϶� �ش��ϴ� ���ڿ��� ����� ����.
	{
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 1)] = buf[0];
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 2)] = buf[1];
	}
	else if (playerLocation->location >= 18 && playerLocation->location <= 27) // �÷��̾� ��ġ�� 18~27�϶� �ش��ϴ� ���ڿ��� ����� ����.
	{
		boardpan[1][(playerNum * 2 + 1) + (11 * (playerLocation->location - 18))] = buf[0];
		boardpan[1][(playerNum * 2 + 2) + (11 * (playerLocation->location - 18))] = buf[1];
	}
	else if (playerLocation->location >= 28 && playerLocation->location <= 35)// �÷��̾� ��ġ�� 28~35�϶� �ش��ϴ� ���ڿ��� ����� ����.
	{
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 99] = buf[0];
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 100] = buf[1];
	}

}

void printcolor(int color) { // �� �ٲ��ִ� �Լ�. // ���� ������ ���� ����.
	if (color == WHITE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	else if (color == BLUE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	else if (color == GREEN) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	else if (color == RED) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	else if (color == YELLOW) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	else if (color == BLACK) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);
}

/*���� �ǹ��� ����� ������ִ� �Լ�.
i�� ����� ���۵Ǵ� y��, j�� ����� ���۵Ǵ� x�� playerHaveBoard�� �÷��̾��� ����ü�� ã�ư� ������ �ǹ��� �˱� ���� ����, haveplayer�� ���� �ǹ� ����..
1�ٸ��� 4���� ������ֱ� ���� 4,8,12,16�϶��� ���� ��������.*/
void printHaveBoard(int i, int j, int haveplayer, struct player* playerHaveBoard) {
	char buf[16] = { 0 };
	int a = 0;
	if (haveplayer == 0) return 0; // ���� �ǹ��� ������� �ٷ� ����.
	if (haveplayer <= 4) a = 0;
	else if (haveplayer <= 8) a = 4;
	else if (haveplayer <= 12) a = 8;
	else if (haveplayer <= 16) a = 12;
	else if (haveplayer <= 20) a = 16;
	for (; a < haveplayer - 1; a++) // haveplayer��ŭ ���ڿ��� ����.
	{
		if (playerHaveBoard->player_board[a] == NULL) continue;
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++) // k=0���� player�� ������ �ִ� a��° �ǹ��� �̸���ŭ ���ڿ��� ����.
		{
			boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
			j++; // x���� ����ؼ� ����������.
		}
		boardpan[i][j] = '('; // '('����
		j++; // x�� ����
		for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++) // m=0���� �÷��̾ ������ �ִ� a��° �ǹ��� ������� ���̸�ŭ ���ڿ��� ����.
		{
			boardpan[i][j] = buf[m]; // ����� ����.
			j++; // x�� ����
		}
		boardpan[i][j] = 'k'; j++; // k����, x�� ����
		boardpan[i][j] = ')'; j++; // ')'����, x�� ����
		for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++) // ������ �ٸ�ŭ�� ������ְ� �������� ��ĭ���� ���.
		{
			boardpan[i][j] = ' ';
			j++;
		}
	}
	for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++) // ������ haveplayer��° ���.(���� ������)
	{
		boardpan[i][j] = playerHaveBoard->player_board[haveplayer - 1]->name[k];
		j++;
	}
	boardpan[i][j] = '(';
	j++;
	for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[haveplayer - 1]->pass_value / 1000, buf, 10)); m++)
	{
		boardpan[i][j] = buf[m];
		j++;
	}
	boardpan[i][j] = 'k'; j++;
	boardpan[i][j] = ')'; j++;
}


void printBuild(struct player* playerBuild) {

	char bufVilla[2] = "��";
	char bufBuilding[2] = "��";
	char bufHotel[2] = "��";
	char basebuild[2] = "��";
	char buf[2] = { 0 };



	for (int i = 0; i < playerBuild->haveBoard; i++) // ������ �ִ� �ǹ��� ��ŭ ���ڿ��� ����.
	{
		if (playerBuild->player_board[i]->build == 1) // �ǹ� 1�� �϶� >> Villa ���
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][1 + 11 * (9 - playerBuild->player_board[i]->num)] = basebuild[0];
				boardpan[39][2 + 11 * (9 - playerBuild->player_board[i]->num)] = basebuild[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = basebuild[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = basebuild[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][1 + (11 * (playerBuild->player_board[i]->num - 18))] = basebuild[0];
				boardpan[3][2 + (11 * (playerBuild->player_board[i]->num - 18))] = basebuild[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = basebuild[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = basebuild[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 2) // �ǹ� 1�� �϶� >> Villa ���
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[39][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufVilla[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[3][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufVilla[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufVilla[1];
			}
		}

		else if (playerBuild->player_board[i]->build == 3) // �ǹ� 2�� �϶� villa���
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[39][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
				boardpan[39][10 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[39][11 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][10] = bufVilla[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][11] = bufVilla[1];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufVilla[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][10 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[3][11 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
				boardpan[3][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[3][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][109] = bufVilla[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][110] = bufVilla[1];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufVilla[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufVilla[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 4) // 3�϶� ����
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufBuilding[0];
				boardpan[39][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufBuilding[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufBuilding[0];
				boardpan[3][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufBuilding[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufBuilding[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 5) // 4�϶� ȣ��
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[0];
				boardpan[39][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufHotel[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[0];
				boardpan[3][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufHotel[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufHotel[1];
			}
		}
	}
	
}

int Dice_Move(struct player* _player, int* i, int k) { // i >> ���ε��� ���� ī��Ʈ? k >> �÷��̾�
	char buf[2] = "��";
	char buf_hangul[18] = "�÷��̾� ���� ��ġ";
	char buf_double[5] = "����!";
	char buf_1[16] = { 0 };
	char buf_location[16] = { 0 };
	char island[10] = "���ε�����";
	char island2[17] = "��° �ֻ����Դϴ�";
	char buf_count[16];
	char escape[12] = "���ε� Ż��!";
	char doubleIsland[29] = "���� ���� 3��! ���ε��ΰ��ϴ�";
	int u = 18;
	char salary[] = "���� 200k!";
	for (int i = 0; i < 17; i++)
	{
		boardpan[11][124 + i] = ' ';
		boardpan[10][128 + i] = ' ';
	}
	for (int i = 0; i < 50; i++)
	{
		boardpan[12][138 + i] = ' '; // ���ε� ���°���� ���
	}

	for (int i = 0; i < 7; i++)
	{
		boardpan[8][137 + i] = ' ';
	}
	{
		clear(3, 119, 9); clear(1, 119, 9);	// ù��° �ֻ��� ��� �ʱ�ȭ
		clear(5, 119, 9); clear(2, 131, 7); clear(4, 165, 7);


		// ù���� �ֻ���
		clear(3, 119 + u, 9); clear(1, 119 + u, 9); // �ι�° �ֻ��� ��� �ʱ�ȭ
		clear(5, 119 + u, 9); clear(2, 131 + u, 7); clear(4, 165 + u, 7);

		clear(10, 119, 7); // �̸� ������ �κ� �ʱ�ȭ
		clear(14, 128, 10);
	}


	int d1 = rand() % 6 + 1;
	if (d1 == 1) { boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1]; } // �ֻ��� 1�϶�(�ֻ��� �� ����)
	else if (d1 == 2) // �ֻ��� 2�϶�
	{
		boardpan[3][120] = buf[0]; boardpan[3][121] = buf[1];
		boardpan[3][125] = buf[0]; boardpan[3][126] = buf[1];
	}
	else if (d1 == 3) // �ֻ��� 3�϶�
	{
		boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1];
		boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1];
		boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1];
	}
	else if (d1 == 4) // �ֻ��� 4�϶�
	{
		boardpan[2][131] = buf[0]; boardpan[2][132] = buf[1];
		boardpan[2][136] = buf[0]; boardpan[2][137] = buf[1];
		boardpan[4][165] = buf[0]; boardpan[4][166] = buf[1];
		boardpan[4][170] = buf[0]; boardpan[4][171] = buf[1];
	}
	else if (d1 == 5) // �ֻ��� 5�ϋ�
	{
		boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1]; boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1];
		boardpan[1][126] = buf[0]; boardpan[1][127] = buf[1]; boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1];
		boardpan[5][119] = buf[0]; boardpan[5][120] = buf[1];
	}
	else // �ֻ��� 6�϶�
	{
		boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1]; boardpan[1][126] = buf[0]; boardpan[1][127] = buf[1];
		boardpan[3][119] = buf[0]; boardpan[3][120] = buf[1]; boardpan[3][126] = buf[0]; boardpan[3][127] = buf[1];
		boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1]; boardpan[5][119] = buf[0]; boardpan[5][120] = buf[1];
	}
	int d2 = rand() % 6 + 1; // �ι��� �ֻ��� ������
	if (d2 == 1) { boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1]; } // 1�϶�
	else if (d2 == 2) // 2�϶�
	{
		boardpan[3][120 + u] = buf[0]; boardpan[3][121 + u] = buf[1];
		boardpan[3][125 + u] = buf[0]; boardpan[3][126 + u] = buf[1];
	}
	else if (d2 == 3) // 3�϶�
	{
		boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1];
	}
	else if (d2 == 4) // 4�϶�
	{
		boardpan[2][131 + u] = buf[0]; boardpan[2][132 + u] = buf[1]; boardpan[2][136 + u] = buf[0]; boardpan[2][137 + u] = buf[1];
		boardpan[4][165 + u] = buf[0]; boardpan[4][166 + u] = buf[1]; boardpan[4][170 + u] = buf[0]; boardpan[4][171 + u] = buf[1];
	}
	else if (d2 == 5) // 5�϶�
	{
		boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1];
		boardpan[1][126 + u] = buf[0]; boardpan[1][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1];
		boardpan[5][119 + u] = buf[0]; boardpan[5][120 + u] = buf[1];
	}
	else // 6�϶�
	{
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1]; boardpan[1][126 + u] = buf[0]; boardpan[1][127 + u] = buf[1];
		boardpan[3][119 + u] = buf[0]; boardpan[3][120 + u] = buf[1]; boardpan[3][126 + u] = buf[0]; boardpan[3][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1]; boardpan[5][119 + u] = buf[0]; boardpan[5][120 + u] = buf[1];
	}

	_itoa(d1 + d2, buf_1, 10); // buf_1�� d1+d2�� ���ڷ� ����.
	boardpan[8][144] = buf_1[0]; // ������ ����ϱ� ����
	boardpan[8][145] = buf_1[1]; // ���� ������ �κп� ���ڸ� ���ڷ� ����.

	if (_player->location == 27 && _player->money > 200000) { // ����
		printPlayer(k);
		printString(10, 128, 18, buf_hangul); // �÷��̾� ��ġ ���
		_itoa(_player->location, buf_location, 10);
		printString(10, 147, 2, buf_location); // ��ġ ���
		int target;
		system("cls");
		print_board();
		while (1) {
			printf("���ϴ� ��ġ�� �����Ͻÿ�.(�̿�� 200k) ");
			scanf("%d", &target);
			_player->location = target;
			if (target > 27 && target < 36) {
				_player->money -= 200000;
			}
			Sleep(1500);
			system("cls");
			if (_player->location == 2 || _player->location == 6 || _player->location == 11 || _player->location == 15 || _player->location == 20 || _player->location == 25 || _player->location == 31) {
				GoldenKey(_player);
			}
			if (_player->location == 18 || _player->location == 34)
			{
				Fund(_player);
			}
			int ch = getchar();
			if (getchar != 0)
			{
				return 0;
			}
		}
	}
	system("cls");
	if (_player->location == 9) { // �÷��̾� ��ġ�� ���ε��϶�
		_player->count++;
		if (_player->count == 3) printString(12, 138, 12, escape); // ���ε� Ż��! ���
		if (_player->count < 3) {

			if (d1 == d2) { // �����϶�
				printString(8, 137, 5, buf_double); // ����! ���

				_player->location += d1 + d2; // ��ġ ������Ʈ
				_player->count = 0; // player->count ������Ʈ
				printString(12, 138, 12, escape); // ���ε� Ż��! ���
				printPlayer(k);
				printString(10, 128, 18, buf_hangul); // �÷��̾� ��ġ ���
				_itoa(_player->location, buf_location, 10);
				printString(10, 147, 2, buf_location); // ��ġ ���
			}
			printPlayer(k);
			printString(10, 128, 18, buf_hangul);

			_itoa(_player->location, buf_location, 10); // ��ġ ������ִ°�(������ġ�� ���ڷ�)
			printString(10, 147, 2, buf_location);
			if (_player->location == 9)
			{
				printString(12, 138, 10, island);// ���ε����� ���
				printString(12, 150, 17, island2);
				_itoa(_player->count, buf_count, 10); // ���° ���
				boardpan[12][149] = buf_count[0]; // ���°���� ���� ���
			}
			return 0; // ������ �ƴϸ� �׳� ����
		}
		else if (_player->count >= 3) { // ���ε����� 3���̻� player->count =0���� �ʱ�ȭ
			_player->count = 0;
		}
	}

	if (d1 == d2) { // �����϶�
		*i += 1;
		printString(8, 137, 5, buf_double);
		//printf("���� %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) { // ������ 3���̻��ϰ��

			_player->location = 9; // ���ε���
			printString(12, 138, 29, doubleIsland);
			printPlayer(k);
			printString(10, 128, 18, buf_hangul);
			_itoa(_player->location, buf_location, 10); // ��ġ ������ִ°�(������ġ�� ���ڷ�)
			printString(10, 147, 2, buf_location);

			return 0; // ����
		}
	}
	_player->location += d1 + d2; // �����̸鼭 3���̻� ������ �ʾ����� ��ġ ������Ʈ
	if (_player->location >= 36) {
		_player->location %= 36;
		printString(14, 128, 10, salary);
		_player->money += 200000;
	}

	if (_player->location == 2 || _player->location == 6 || _player->location == 11 || _player->location == 15 || _player->location == 20 || _player->location == 25 || _player->location == 31) {
		GoldenKey(_player);
	}
	if (_player->location == 18 || _player->location == 34)
	{
		printPlayer(k);
		printString(10, 128, 18, buf_hangul);
		_itoa(_player->location, buf_location, 10); // ��ġ ������ִ°�(������ġ�� ���ڷ�)
		printString(10, 147, 2, buf_location);
		Fund(_player);
	}
	printPlayer(k);
	printString(10, 128, 18, buf_hangul);
	_itoa(_player->location, buf_location, 10); // ��ġ ������ִ°�(������ġ�� ���ڷ�)
	printString(10, 147, 2, buf_location);

	if (d1 == d2) { // ���� �����ϰ�� return 1
		return 1;
	}
	return 0; // �ƴҰ�� �׳� ����
}

void Island(int* count) {
	*count += 1;

}
void GoldenKey(struct player* player_) {
	char island[] = "���ε��� ���ϴ�.";
	char prize[] = "����� 1000k";
	char prize1[] = "����� 500k";
	char prize2[] = "����� 300k";
	char prize3[] = "����� 200k";
	char fine[] = "���� 200k";
	char fine2[] = "���� 300k";
	char fine3[] = "���� 500k";
	char trip[] = "���迩������ �̵�";
	char start[] = "������� �̵�";
	char goldkey[] = "Ȳ�ݿ��� ĭ�Դϴ�.";
	char salary[] = "���� 200k!";
	int r = rand() % 10;

	for (int i = 0; i < 17; i++)
	{
		boardpan[11][124 + i] = goldkey[i];
	}
	switch (r) { // ���� ���ڿ� �������.
	case 0:
		clear_string();
		print_string(island, 15);
		player_->location = 9;
		break;
	case 1:
		clear_string();
		print_string(prize, 12);
		player_->money += 1000000;
		break;
	case 2:
		clear_string();
		print_string(prize1, 11);
		player_->money += 500000;
		break;
	case 3:
		clear_string();
		print_string(prize2, 11);
		player_->money += 300000;
		break;
	case 4:
		clear_string();
		print_string(prize3, 11);
		player_->money += 200000;
		break;
	case 5:
		clear_string();
		print_string(fine, 9);
		player_->money -= 200000;
		break;
	case 6:
		clear_string();
		print_string(fine2, 9);
		player_->money -= 300000;
		break;
	case 7:
		clear_string();
		print_string(fine3, 9);
		player_->money -= 500000;
		break;
	case 8:
		clear_string();
		print_string(trip, 17);
		player_->location = 27;
		break;
	case 9:
		clear_string();
		print_string(start, 13);
		player_->location = 0;
		printString(14, 128, 10, salary);
		player_->money += 200000;
		break;
	}
}
void print_string(char* str, int number) {
	for (int i = 0; i < number; i++)
	{
		boardpan[12][138 + i] = str[i];
	}
}
void clear_string(void) {
	for (int i = 0; i < 55; i++) {
		boardpan[12][138 + i] = ' ';
	}
}

void clear(int i, int j, int k) {

	for (int a = 0; a < k; a++)
	{
		boardpan[i][j + a] = ' ';
	}
}

void printPlayer(int k) { // ���� �÷��̾����� ���
	char blue[4] = "Blue";
	char red[3] = "Red";
	char green[5] = "Green";
	char yellow[6] = "Yellow";
	if (k == 1) printString(10, 120, 4, blue);
	else if (k == 2) printString(10, 120, 3, red);
	else if (k == 3) printString(10, 120, 5, green);
	else if (k == 4) printString(10, 120, 6, yellow);
}

void printString(int i, int j, int k, char* buf) {
	for (int a = 0; a < k; a++)
	{
		boardpan[i][j + a] = buf[a];
	}
}
void sell(struct board* _boardCell, struct player* Player) {
	printf("���� �Ľðڽ��ϱ�? y or n\n");
	_kbhit();
	if (Player->money <= 0 && Player->haveBoard <= 0) return 0;
	if (_getch() == 'y')
	{
		while (1)
		{
			printf("�Ȱ� ���� ���� ��ȣ�� �Է��ϼ���(���: -1) : ");
			int number;
			scanf_s("%d", &number); getchar();
			if (number == -1) break;
			if ((_boardCell + number)->get_player == NULL || (_boardCell + number)->get_player->color != Player->color) continue;
			switch ((_boardCell + number)->build) {
			case 1:
				printf("�ǸŰ����� %dk�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n", (_boardCell + number)->value / 1000);
				_kbhit();
				if (_getch() == 'y')
				{
					Player->money += (_boardCell + number)->value;
					(_boardCell + number)->get_player = NULL;
					for (int i = 0; i < 20; i++) {
						if (Player->player_board[i]->num == (_boardCell + number)->num)
						{
							Player->player_board[i]->build = 0;
							for (int j = i; j < 20; j++)
							{
								if (Player->player_board[j+1] == NULL) break;
								Player->player_board[j] = Player->player_board[j + 1];
							}
							break;
						}
					}
					Player->haveBoard--;
					printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
					printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
				}
				else printf("�ǸŸ� ����Ͽ����ϴ�.\n");

				break;
			case 2:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("�ǸŰ����� 100k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 100000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("�ǸŰ����� 100k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 100000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("�ǸŰ����� 150k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 150000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("�ǸŰ����� 200k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 200000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				break;
			case 3:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("�ǸŰ����� 50k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 50000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
					Player->money += 50000;
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("�ǸŰ����� 100k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 100000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("�ǸŰ����� 150k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 150000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("�ǸŰ����� 200k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 200000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				break;
			case 4:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("�ǸŰ����� 150k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 150000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("�ǸŰ����� 300k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 300000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("�ǸŰ����� 450k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 450000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("�ǸŰ����� 600k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					_kbhit();
					if (_getch() == 'y')
					{
						Player->money += 600000;
						(_boardCell + number)->get_player = NULL;
						for (int i = 0; i < 20; i++) {
							if (Player->player_board[i]->num == (_boardCell + number)->num)
							{
								Player->player_board[i]->build = 0;
								for (int j = i; j < 20; j++)
								{
									if (Player->player_board[j + 1] == NULL) break;
									Player->player_board[j] = Player->player_board[j + 1];
								}
								break;
							}
						}
						Player->haveBoard--;
						printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					}
					else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				}
				break;
			case 5: if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
				Player->money += 250000;
			}
				  if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					  printf("�ǸŰ����� 500k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					  _kbhit();
					  if (_getch() == 'y')
					  {
						  Player->money += 500000;
						  (_boardCell + number)->get_player = NULL;
						  for (int i = 0; i < 20; i++) {
							  if (Player->player_board[i]->num == (_boardCell + number)->num)
							  {
								  Player->player_board[i]->build = 0;
								  for (int j = i; j < 20; j++)
								  {
									  if (Player->player_board[j + 1] == NULL) break;
									  Player->player_board[j] = Player->player_board[j + 1];
								  }
								  break;
							  }
						  }
						  Player->haveBoard--;
						  printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						  printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					  }
					  else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				  }
				  if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					  printf("�ǸŰ����� 750k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					  _kbhit();
					  if (_getch() == 'y')
					  {
						  Player->money += 750000;
						  (_boardCell + number)->get_player = NULL;
						  for (int i = 0; i < 20; i++) {
							  if (Player->player_board[i]->num == (_boardCell + number)->num)
							  {
								  Player->player_board[i]->build = 0;
								  for (int j = i; j < 20; j++)
								  {
									  if (Player->player_board[j + 1] == NULL) break;
									  Player->player_board[j] = Player->player_board[j + 1];
								  }
								  break;
							  }
						  }
						  Player->haveBoard--;
						  printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						  printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					  }
					  else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				  }
				  if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					  printf("�ǸŰ����� 1000k�Դϴ� ������ �Ľðڽ��ϱ�? y or n\n");
					  _kbhit();
					  if (_getch() == 'y')
					  {
						  Player->money += 1000000;
						  (_boardCell + number)->get_player = NULL;
						  for (int i = 0; i < 20; i++) {
							  if (Player->player_board[i]->num == (_boardCell + number)->num)
							  {
								  Player->player_board[i]->build = 0;
								  for (int j = i; j < 20; j++)
								  {
									  if (Player->player_board[j + 1] == NULL) break;
									  Player->player_board[j] = Player->player_board[j + 1];
								  }
								  break;
							  }
						  }
						  Player->haveBoard--;
						  printf("�� �ǸŸ� �Ϸ��Ͽ����ϴ�!\n");
						  printf("���� �ݾ��� %dk�Դϴ�.\n", Player->money / 1000);
					  }
					  else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
				  }
				  break;

			}
		}
	}
	else printf("�ǸŸ� ����Ͽ����ϴ�.\n");
}

void buy(struct board* _boardCell, struct player* Player) {//Player�� ���� ������ �÷��̾�.
	if ((_boardCell + Player->location)->get_player == NULL && (_boardCell + Player->location)->num != 0 && (_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6
		&& (_boardCell + Player->location)->num != 9 && (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15 && (_boardCell + Player->location)->num != 18
		&& (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25 && (_boardCell + Player->location)->num != 27 && (_boardCell + Player->location)->num != 31
		&& (_boardCell + Player->location)->num != 34) {//_boardCell�� boardCell[0]�� �ǹ���. �ű⿡ Player->location�� �����༭ [1],[2],[3],...[35]���� ���.
		int hit;
		printf("�� ���� ��ðڽ��ϱ�? y or n\n");
		_kbhit();
		hit = _getch();
		int hit1 = 0;
		if (hit == 'y') {
			if (Player->money < (_boardCell + Player->location)->value) {
				printf("���� ���ڶ��ϴ�.\n");
				if (Player->haveBoard >= 1)
				{
					sell(boardCell, Player);
					if (Player->money > (_boardCell + Player->location)->value) { buy(boardCell, Player); }

				}
			}
			else
			{
				printf("�� ���� ������ %dk�Դϴ�. ������ ��ðڽ��ϱ�? y or n\n", (_boardCell + Player->location)->value / 1000);
				_kbhit();
				hit1 = _getch();
				if (hit1 == 'y') {

					printf("�� ���Ÿ� �Ϸ��Ͽ����ϴ�!\n");
					Player->money -= (_boardCell + Player->location)->value;
					Player->player_board[Player->haveBoard] = &boardCell[Player->location];
					boardCell[Player->location].get_player = Player;
					Player->haveBoard++;
					(_boardCell + Player->location)->build++;

				}
			}
		}
	}
}

void build(struct board* _boardCell, struct player* Player) {

	if ((_boardCell + Player->location)->num == 0 || (_boardCell + Player->location)->num == 2 || (_boardCell + Player->location)->num == 6
		|| (_boardCell + Player->location)->num == 9 || (_boardCell + Player->location)->num == 11 || (_boardCell + Player->location)->num == 15 || (_boardCell + Player->location)->num == 18
		|| (_boardCell + Player->location)->num == 20 || (_boardCell + Player->location)->num == 25 || (_boardCell + Player->location)->num == 27 || (_boardCell + Player->location)->num == 31
		|| (_boardCell + Player->location)->num == 34)
	{
		return 0;
	}
	int select = 0;
	int select1 = 0;

	if ((_boardCell + Player->location)->get_player->color == Player->color && (_boardCell + Player->location)->num != 35) {//���� �������� �÷��̾�� �÷����ϴ� �÷��̾��� ������ ���ٸ�.
		if ((_boardCell + Player->location)->build >= 1 && (_boardCell + Player->location)->build < 4) {//�ƹ��͵� �� ������ ���� ��.
			printf("�ǹ��� ���׷��̵� �Ͻðڽ��ϱ�? y or n\n");
			_kbhit();
			select = _getch();
		}
	}

	if (select == 'y' && (_boardCell + Player->location)->build != 5) {
		switch ((_boardCell + Player->location)->build) {
		case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
			printf("������ ������ 50k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 50000) {
					printf("���� ���ڶ��ϴ�.\n");
					if (Player->haveBoard >= 1)
					{
						sell(boardCell, Player);
						build(boardCell, Player);
					}
				}
				else {
					(_boardCell + Player->location)->build++;
					Player->money -= 50000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 100k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 100000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 100000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 150k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 150000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 150000;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
				  printf("������ ������ 200k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 200000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 200000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  break;
		case 2:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
			printf("������ ������ 50k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 50000) {
					printf("���� ���ڶ��ϴ�.\n");
					if (Player->haveBoard >= 1)
					{
						sell(boardCell, Player);
						build(boardCell, Player);
					}
				}
				else {
					(_boardCell + Player->location)->build++;
					Player->money -= 50000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
					printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 100k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 100000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 100000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 150k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 150000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 150000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
				  printf("������ ������ 200k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 200000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 200000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  break;
		case 3:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
			printf("������ ������ 150k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 150000) {
					printf("���� ���ڶ��ϴ�.\n");
					if (Player->haveBoard >= 1)
					{
						sell(boardCell, Player);
						build(boardCell, Player);
					}
				}
				else {
					(_boardCell + Player->location)->build++;
					Player->money -= 150000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
					printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 300k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 300000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 300000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
				  printf("������ ������ 450k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 450000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 450000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
				  printf("������ ������ 600k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 600000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 600000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  break;
		case 4:if ((_boardCell + Player->location)->num > 0 && _boardCell->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
			printf("ȣ���� ������ 250k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 250000) {
					printf("���� ���ڶ��ϴ�.\n");
					if (Player->haveBoard >= 1)
					{
						sell(boardCell, Player);
						build(boardCell, Player);
					}
				}
				else {
					(_boardCell + Player->location)->build++;
					Player->money -= 250000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
					printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
				  printf("ȣ���� ������ 500k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 500000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 500000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
				  printf("ȣ���� ������ 750k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 750000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 750000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 35 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
				  printf("ȣ���� ������ 1000k�Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 1000000) {
						  printf("���� ���ڶ��ϴ�.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 1000000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
						  printf("�ǹ� ���׷��̵带 �Ϸ��Ͽ����ϴ�!\n");
					  }
				  }
			  }
			  break;
		}
	}
}

void Pass(struct board* _boardCell, struct player* Player) {

	if ((_boardCell + Player->location)->pass_value > Player->money) {
		printf("���� �����մϴ�.\n");
		if (Player->haveBoard >= 1)
		{
			sell(boardCell, Player); Pass(_boardCell, Player);
		}
		else if (Player->haveBoard <= 0)
		{
			printf("����� ����! -%dk\n", (_boardCell + Player->location)->pass_value / 1000);
			Player->money -= (_boardCell + Player->location)->pass_value;
			(_boardCell + Player->location)->get_player->money += (_boardCell + Player->location)->pass_value;
		}
	}
	if ((_boardCell + Player->location)->pass_value < Player->money)
	{
		printf("����� ����! -%dk\n", (_boardCell + Player->location)->pass_value / 1000);

		Player->money -= (_boardCell + Player->location)->pass_value;
		(_boardCell + Player->location)->get_player->money += (_boardCell + Player->location)->pass_value;
	}
}

void print_clear(void) {
	for (int j = 0; j < 10; j++)
	{
		clear(39, 1 + 11 * j, 2);
		clear(3, 1 + 11 * j, 2);
		clear(39, 10 + 11 * j, 2);
		clear(3, 10 + 11 * j, 2);
	}
	for (int j = 0; j < 8; j++)
	{
		clear(35 - 4 * j, 1, 2);
		clear(35 - 4 * j, 100, 2);
		clear(35 - 4 * j, 10, 2);
		clear(35 - 4 * j, 109, 2);
	}

	clear(12, 138, 25);
	clear(12, 30, 70); clear(13, 23, 70); clear(14, 25, 70); clear(15, 23, 70); clear(16, 30, 70);
	clear(18, 25, 70); clear(19, 23, 70); clear(20, 30, 70); clear(21, 23, 70); clear(22, 25, 70);
	clear(24, 30, 70); clear(25, 23, 70); clear(26, 25, 70); clear(27, 23, 70); clear(28, 30, 70);
	clear(30, 25, 70); clear(31, 23, 70); clear(32, 30, 70); clear(33, 23, 70); clear(34, 25, 70);
}

void gameover(struct player* Player) {

	char gmeover[] = "Game Over";
	int j = 0;
	if (Player->money < 0)
	{
		for (int i = 0; i < Player->haveBoard; i++)
		{
			if (Player->player_board[j]->get_player == NULL || Player->player_board[j]->get_player->color != Player->color) {
				i--;	j++;  continue;
			}
			Player->player_board[j]->build = 0;
			Player->player_board[j]->get_player = NULL;
			Player->player_board[j] = NULL;
			j++;
		}
		Player->haveBoard = 0;
		Player->location = 0;
		Player->money = 0;
		if (Player->color == BLUE)
		{
			printString(11, 70, 9, gmeover);
		}
		if (Player->color == RED)
		{
			printString(17, 70, 9, gmeover);
		}
		if (Player->color == GREEN)
		{
			printString(23, 70, 9, gmeover);
		}
		if (Player->color == YELLOW)
		{
			printString(29, 70, 9, gmeover);
		}
	}
}
void Fund(struct player* p1) {
	//18, 34

	char buf[16] = { 0 };
	char put[] = "k ����";
	char funding[] = "200k ����";
	_itoa(fund / 1000, buf, 10);
	if (p1->location == 18) {
		p1->money += fund;
		if (fund > 0) {
			printString(12, 138, 3, buf);
			printString(12, 141, 6, put);
			fund = 0;
		}
	}
	else if (p1->location == 34) {
		p1->money -= 200000;
		fund += 200000;
		printString(12, 138, 9, funding);
	}
	print_board();
	Sleep(1500);
	system("cls");
}

void printBlue(void) {
	printcolor(BLUE);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t########  ##       ##     ## ######## \n");
	printf("\t\t\t\t\t\t\t\t\t##     ## ##       ##     ## ##        \n");
	printf("\t\t\t\t\t\t\t\t\t##     ## ##       ##     ## ##        \n");
	printf("\t\t\t\t\t\t\t\t\t########  ##       ##     ## ######    \n");
	printf("\t\t\t\t\t\t\t\t\t##     ## ##       ##     ## ##        \n");
	printf("\t\t\t\t\t\t\t\t\t##     ## ##       ##     ## ##        \n");
	printf("\t\t\t\t\t\t\t\t\t########  ########  #######  ########  \n\n\n\n");


}

void printRed(void) {
	printcolor(RED);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t    ########  ######## ########  \n");
	printf("\t\t\t\t\t\t\t\t\t    ##     ## ##       ##     ## \n");
	printf("\t\t\t\t\t\t\t\t\t    ##     ## ##       ##     ## \n");
	printf("\t\t\t\t\t\t\t\t\t    ########  ######   ##     ## \n");
	printf("\t\t\t\t\t\t\t\t\t    ##   ##   ##       ##     ## \n");
	printf("\t\t\t\t\t\t\t\t\t    ##    ##  ##       ##     ## \n");
	printf("\t\t\t\t\t\t\t\t\t    ##     ## ######## ########  \n\n\n\n");
}

void printGreen(void) {
	printcolor(GREEN);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t     ######   ########  ######## ######## ##    ## \n");
	printf("\t\t\t\t\t\t\t\t    ##    ##  ##     ## ##       ##       ###   ## \n");
	printf("\t\t\t\t\t\t\t\t    ##        ##     ## ##       ##       ####  ## \n");
	printf("\t\t\t\t\t\t\t\t    ##   #### ########  ######   ######   ## ## ## \n");
	printf("\t\t\t\t\t\t\t\t    ##    ##  ##   ##   ##       ##       ##  #### \n");
	printf("\t\t\t\t\t\t\t\t    ##    ##  ##    ##  ##       ##       ##   ### \n");
	printf("\t\t\t\t\t\t\t\t     ######   ##     ## ######## ######## ##    ## \n\n\n\n");
}

void printYellow(void) {
	printcolor(YELLOW);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t ##    ## ######## ##       ##        #######  ##      ## \n");
	printf("\t\t\t\t\t\t\t\t  ##  ##  ##       ##       ##       ##     ## ##  ##  ##\n");
	printf("\t\t\t\t\t\t\t\t   ####   ##       ##       ##       ##     ## ##  ##  ##\n");
	printf("\t\t\t\t\t\t\t\t    ##    ######   ##       ##       ##     ## ##  ##  ##\n");
	printf("\t\t\t\t\t\t\t\t    ##    ##       ##       ##       ##     ## ##  ##  ##\n");
	printf("\t\t\t\t\t\t\t\t    ##    ##       ##       ##       ##     ## ##  ##  ##\n");
	printf("\t\t\t\t\t\t\t\t    ##    ######## ######## ########  #######   ###  ###\n\n\n\n");

}

void printWin(void) {

	printf("\t\t\t\t\t\t\t\t\t               #                 #    \n");
	printf("\t\t\t\t\t\t\t\t\t                                 #    \n");
	printf("\t\t\t\t\t\t\t\t\t   #     #   ###     # ####      #    \n");
	printf("\t\t\t\t\t\t\t\t\t   #  #  #     #     ##    #     #    \n");
	printf("\t\t\t\t\t\t\t\t\t   #  #  #     #     #     #     #    \n");
	printf("\t\t\t\t\t\t\t\t\t   #  #  #     #     #     #          \n");
	printf("\t\t\t\t\t\t\t\t\t    ## ##    #####   #     #     #    \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printcolor(WHITE);
}