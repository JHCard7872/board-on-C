#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define WHITE 7
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6



struct board { // 보드셀 구조체
	char name[16]; // 이름
	int num; // 번호
	int build; // 건물개수(1 >> 땅사기 // 2 >> 빌라1개 // 3 >> 빌라2개 // 4 >> 빌딩1개 // 5 >> 호텔1개)
	int pass_villa1; // 빌라 1개일때 통행료
	int pass_villa2; // 빌라 2개일때 통행료
	int pass_building; // 빌딩 1개일때 통행료
	int pass_hotel; // 호텔 1개일때 통행료
	int value; // 땅값
	int pass_value; // 통행료
	int pass_value2; // 통행료 처음가격 저장해주는 변수
	int sell_value; // 팔때의 가격
	struct player* get_player;
};

struct player { // 플레이어 구조체
	int haveBoard; // 가지고있는 땅의 개수
	int color; // 플레이어의 색
	int money; // 보유금액
	int location; // 위치
	int count;
	struct board* player_board[20]; // 보유하고있는 땅의 구조체주소
};

struct board boardCell[36] = { // 보드셀의 초기화
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

struct player play[4] = { 0 };

char boardpan[41][255] = { // 보드판의 문자열                                                                          /aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/
	"┏━━  18 ━━━┳━━  19 ━━━┳━━  20 ━━━┳━━  21 ━━━┳━━  22 ━━━┳━━  23 ━━━┳━━  24 ━━━┳━━  25 ━━━┳━━  26 ━━━┳━━  27 ━━━┓    ┏━━━━━━━━━━━━┓  ┏━━━━━━━━━━━━┓", // 0
	"                                                                                                                   ┃            ┃  ┃            ┃", // 1 
	"┃  GetFund ┃ Argentina┃  Goldkey ┃   Brazil ┃ Australia┃   Hawai  ┃ Portugal ┃  Goldkey ┃   Spain  ┃  Travel  ┃    ┃            ┃  ┃            ┃", // 2
	"               220k                  240k       240k       260k       260k                  280k                   ┃            ┃  ┃            ┃", // 3
	"┠━━  17 ━━━╋  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━╋━━  28 ━━━┫    ┃            ┃  ┃            ┃", // 4
	"                                                                                                                   ┃            ┃  ┃            ┃", // 5
	"┃   Canada ┃                                                                                       ┃   Japan  ┃    ┗━━━━━━━━━━━━┛  ┗━━━━━━━━━━━━┛ ", // 6
	"    200k                                                                                               300k        ",
	"┠━━  16 ━━━┫           player      위치     보유금액          보유국가(통행료)                     ┠━━  29 ━━━┫                                           ",//                  더블!", // blue 부분 e부분이26
	"                                                                                                               ",
	"┃  Germany ┃                                                                                       ┃   France ┃                                                           ", // 10
	"    180k               Blue                                                                            320k                                                                           ",
	"┠━━  15 ━━━┫                                                                                       ┠━━  30 ━━━┫",
	"                                                                                                               ",
	"┃  Goldkey ┃                                                                                       ┃   Italy  ┃",
	"                                                                                                       320k    ", // 15
	"┠━━  14 ━━━┫                                                                                       ┠━━  31 ━━━┫",
	"                       Red                                                                                     ",
	"┃Switzeland┃                                                                                       ┃  Goldkey ┃",
	"    180k                                                                                                       ",
	"┠━━  13 ━━━┫                                                                                       ┠━━  32 ━━━┫", //20
	"                                                                                                               ",
	"┃   Sweden ┃                                                                                       ┃    UK    ┃",
	"    160k               Green                                                                           350k    ",
	"┠━━  12 ━━━┫                                                                                       ┠━━  33 ━━━┫",
	"                                                                                                               ", // 25
	"┃  Denmark ┃                                                                                       ┃    USA   ┃",
	"    160k                                                                                               350k    ",
	"┠━━  11 ━━━┫                                                                                       ┠━━  34 ━━━┫",
	"                       Yellow                                                                                  ",
	"┃  Goldkey ┃                                                                                       ┃   Fund   ┃", // 30
	"                                                                                                               ",
	"┠━━  10 ━━━┫                                                                                       ┠━━  35 ━━━┫",
	"                                                                                                               ",
	"┃   Greece ┃                                                                                       ┃   Korea  ┃",
	"    140k                                                                                              1,000k   ", // 35
	"┠━━   9  ━━╋━━   8  ━━┳━━   7  ━━┳━━   6   ━┳━━   5  ━━┳━━   4  ━━┳━━   3 ━━━┳━━   2  ━━┳━━   1  ━━╋━━   0  ━━┫",
	"                                                                                                               ",
	"┃   Island ┃   Turkey ┃   Egypt  ┃  Goldkey ┃ singapore┃Philippine┃   China  ┃  Goldkey ┃   Taiwan ┃   start  ┃",
	"                120k       100k                  100k       80k        80k                   50k               ",
	"┗  ━   ━  ━┸  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━  ━┻  ━   ━   ┛" //40
};

void print_board(void); // 보드판 출력해주는 함수
void printcolor(int color); // 색 바꿔주는 함수
void movePlayer(struct player* playerLocation, int playerNum); // 플레이어의 위치에 따른 문자열 * 변화
void printHaveBoard(int i, int j, int player, struct player* playerHaveBoard); // 가운데에 가지고있는 건물및 통행료 출력
void printBuild(struct player* playerBoard); // 건물기호 출력해주는거
int Dice_Move(struct player* player_locate, int* i, int k); // 주사위 굴리기
void Island(int* count);

int main(void) {
	int k;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		play[i].location = 9;
	}
	for (int m = 0; m < 200; m++) {
		k = 0;
		int i = m % 4;
		int ch = getchar();
		system("cls");
		if (Dice_Move(&play[i], &k, i + 1) && ch != 0) {

			printBuild(&play[0]);
			printBuild(&play[1]);
			printBuild(&play[2]);
			printBuild(&play[3]);
			movePlayer(&play[0], 1);
			movePlayer(&play[1], 2);
			movePlayer(&play[2], 3);
			movePlayer(&play[3], 4);

			//y축 21칸 x축 81칸
			print_board();
			int ch = getchar();
			system("cls");
			// 나중에 플레이어 위치, 땅값 구현할것.
			if (Dice_Move(&play[i], &k, i + 1) && ch != 0) {

				printBuild(&play[0]);
				printBuild(&play[1]);
				printBuild(&play[2]);
				printBuild(&play[3]);
				movePlayer(&play[0], 1);
				movePlayer(&play[1], 2);
				movePlayer(&play[2], 3);
				movePlayer(&play[3], 4);

				//y축 21칸 x축 81칸
				print_board();
				// 나중에 플레이어 위치, 땅값 구현할것.
				int ch = getchar();
				system("cls");
				if (Dice_Move(&play[i], &k, i + 1) && ch != 0) {

					printBuild(&play[0]);
					printBuild(&play[1]);
					printBuild(&play[2]);
					printBuild(&play[3]);
					movePlayer(&play[0], 1);
					movePlayer(&play[1], 2);
					movePlayer(&play[2], 3);
					movePlayer(&play[3], 4);

					//y축 21칸 x축 81칸
					print_board();
					// 나중에 플레이어 위치, 땅값 구현할것.
				}
			}
		}

		printBuild(&play[0]);
		printBuild(&play[1]);
		printBuild(&play[2]);
		printBuild(&play[3]);
		movePlayer(&play[0], 1);
		movePlayer(&play[1], 2);
		movePlayer(&play[2], 3);
		movePlayer(&play[3], 4);

		//y축 21칸 x축 81칸
		print_board();
		// 나중에 플레이어 위치, 땅값 구현할것.
	}
}

void print_board(void) { // 보드판 출력10000
	if (play[0].haveBoard <= 4) // Blue 땅값 정보
	{
		printHaveBoard(12, 30, play[0].haveBoard, &play[0]);
	}
	else if (play[0].haveBoard <= 8)
	{
		printHaveBoard(12, 30, 4, &play[0]);
		printHaveBoard(13, 23, play[0].haveBoard, &play[0]);
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
	if (play[1].haveBoard <= 4) // Red 땅값 정보
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
		printHaveBoard(20, 30, play[0].haveBoard, &play[1]);
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
	if (play[2].haveBoard <= 4) // Green 땅값 정보
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
	if (play[3].haveBoard <= 4) // Yellow 땅값 정보
	{
		printHaveBoard(30, 25, play[3].haveBoard, &play[3]);
	}
	else if (play[3].haveBoard <= 8)
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, play[0].haveBoard, &play[3]);
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
		printHaveBoard(33, 23, play[0].haveBoard, &play[3]);
	}
	else
	{
		printHaveBoard(30, 25, 4, &play[3]);
		printHaveBoard(31, 23, 8, &play[3]);
		printHaveBoard(32, 30, 12, &play[3]);
		printHaveBoard(33, 23, 16, &play[3]);
		printHaveBoard(34, 25, play[3].haveBoard, &play[3]);
	}

	for (int i = 0; i < 41; i++)
	{
		if (i % 4 == 1) // 플레이어 위치를 알려주는 *를 출력해주는 자리
		{
			for (int j = 0; j < 250; j++)
			{
				if (j % 11 == 3 && j <= 114 && (i == 1 || i == 37)) { printcolor(BLUE); printf("%c", boardpan[i][j]); } // *가 출력되는 위치에 따라 색깔 출력
				else if (j % 11 == 4 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]);  printcolor(WHITE); }
				else if (j % 11 == 5 && j <= 114 && (i == 1 || i == 37)) { printcolor(RED); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 6 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 7 && j <= 114 && (i == 1 || i == 37)) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 8 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 9 && j <= 114 && (i == 1 || i == 37)) { printcolor(YELLOW); printf("%c", boardpan[i][j]); }
				else if (j % 11 == 10 && j <= 114 && (i == 1 || i == 37)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 3 || j == 102) { printcolor(BLUE); printf("%c", boardpan[i][j]); }
				else if (j == 4 || j == 103) { printf("%c", boardpan[i][j]);  printcolor(WHITE); }
				else if (j == 5 || j == 104) { printcolor(RED); printf("%c", boardpan[i][j]); }
				else if (j == 6 || j == 105) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 7 || j == 106) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j == 8 || j == 107) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 9 || j == 108) { printcolor(YELLOW); printf("%c", boardpan[i][j]); }
				else if (j == 10 || j == 109) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 1 && j <= 114 && i == 1 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(앞부분)
				else if (j % 11 == 2 && j <= 114 && i == 1 && (boardCell[18 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 1 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(뒷부분)
				else if (j % 11 == 0 && j <= 114 && i == 1 && (boardCell[18 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 1 && j <= 114 && i == 37 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(앞부분)
				else if (j % 11 == 2 && j <= 114 && i == 37 && (boardCell[9 - j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 37 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(뒷부분)
				else if (j % 11 == 0 && j <= 114 && i == 37 && (boardCell[9 - j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 1 && boardCell[(73 - i) / 4].get_player != NULL)) { printcolor(boardCell[(73 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 2 && boardCell[(73 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(73 - i) / 4].get_player != NULL)) { printcolor(boardCell[(73 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(73 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 33))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 33)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 33))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 33)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (i == 17 && j == 22) { printcolor(RED); printf("%c", boardpan[i][j]); } // Red 출력해주는 부분(빨간색으로)
				else if (i == 17 && j == 27) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 17 && j == 36 && play[1].location > 9) { printf("%d", play[1].location); } // 위치 출력
				else if (i == 17 && j == 38 && play[1].location > 9) { printf(""); }
				else if (i == 17 && j == 36 && play[1].location <= 9) { printf("%d", play[1].location); }
				else if (i == 17 && j == 45) { printf("%dk", play[1].money / 1000); } // 보유 금액 출력
				else if (i == 17 && j == 60)  printf("");
				else if (i == 17 && j == 62 && play[1].money > 9999 && play[1].money <= 99999) printf("");
				else if (i == 17 && j >= 62 && j <= 63 && play[1].money > 99999 && play[1].money <= 999999) { printf(""); }
				else if (i == 17 && j >= 62 && j <= 64 && play[1].money > 999999 && play[1].money <= 99999999) printf("");
				else if (i == 17 && j >= 62 && j <= 65 && play[1].money > 9999999 && play[1].money <= 999999999) printf("");
				else if (i == 29 && j == 22) { printcolor(YELLOW); printf("%c", boardpan[i][j]); } // Green 출력해주는 부분(파란색으로)
				else if (i == 29 && j == 29) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 29 && j == 36 && play[3].location > 9) { printf("%d", play[3].location); } // 위치 출력
				else if (i == 29 && j == 38 && play[3].location > 9) { printf(""); }
				else if (i == 29 && j == 36 && play[3].location <= 9) { printf("%d", play[3].location); }
				else if (i == 29 && j == 45) { printf("%dk", play[3].money / 1000); } // 보유 금액 출력
				else if (i == 29 && j == 60)  printf("");
				else if (i == 29 && j == 62 && play[3].money > 9999 && play[3].money <= 99999) printf("");
				else if (i == 29 && j >= 62 && j <= 63 && play[3].money > 99999 && play[3].money <= 999999) { printf(""); }
				else if (i == 29 && j >= 62 && j <= 64 && play[3].money > 999999 && play[3].money <= 99999999) printf("");
				else if (i == 29 && j >= 62 && j <= 65 && play[3].money > 9999999 && play[3].money <= 999999999) printf("");
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i == 10)
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
		else if (i == 11) // Blue출력해주는 부분
		{
			for (int j = 0; j < 255; j++)
			{
				if (j == 22) { printcolor(BLUE); printf("%c", boardpan[i][j]); }
				else if (j == 27) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (j == 36 && play[0].location > 9) { printf("%d", play[0].location); } // 위치 출력
				else if (j == 38 && play[0].location > 9) { printf(""); }
				else if (j == 36 && play[0].location <= 9) { printf("%d", play[0].location); }
				else if (j == 45) { printf("%dk", play[0].money / 1000); } // 보유 금액 출력
				else if (j == 60)  printf("");
				else if (j == 62 && play[0].money > 9999 && play[0].money <= 99999) printf("");
				else if (j >= 62 && j <= 63 && play[0].money > 99999 && play[0].money <= 999999) { printf(""); }
				else if (j >= 62 && j <= 64 && play[0].money > 999999 && play[0].money <= 99999999) printf("");
				else if (j >= 62 && j <= 65 && play[0].money > 9999999 && play[0].money <= 999999999) printf("");
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i == 23) // Green 출력해주는 부분
		{
			for (int j = 0; j < 110; j++)
			{
				if (j == 21) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
				else if (j == 29) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (j == 36 && play[2].location > 9) { printf("%d", play[2].location); } // 위치 출력
				else if (j == 38 && play[2].location > 9) { printf(""); }
				else if (j == 36 && play[2].location <= 9) { printf("%d", play[2].location); }
				else if (j == 45) { printf("%dk", play[2].money / 1000); } // 보유 금액 출력
				else if (j == 60)  printf("");
				else if (j == 62 && play[2].money > 9999 && play[2].money <= 99999) printf("");
				else if (j >= 62 && j <= 63 && play[2].money > 99999 && play[2].money <= 999999) { printf(""); }
				else if (j >= 62 && j <= 64 && play[2].money > 999999 && play[2].money <= 99999999) printf("");
				else if (j >= 62 && j <= 65 && play[2].money > 9999999 && play[2].money <= 999999999) printf("");
				else printf("%c", boardpan[i][j]);
			}
		}

		else
		{
			for (int j = 0; j < 250; j++)
			{
				printf("%c", boardpan[i][j]);
			}
		}

		printf("\n");
	}

	//"' '3* * * *" >> 1칸

}

void movePlayer(struct player* playerLocation, int playerNum) { // 플레이어의 위치에 따라 '*'기호를 문자열에 저장시켜줌
	char buf[2] = "★";
	for (int i = 0; i < 10; i++)
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
	if (playerLocation->location >= 0 && playerLocation->location <= 9)
	{
		boardpan[37][(playerNum * 2 + 1) + 11 * (9 - playerLocation->location)] = buf[0];
		boardpan[37][(playerNum * 2 + 2) + 11 * (9 - playerLocation->location)] = buf[1];

	}
	else if (playerLocation->location >= 10 && playerLocation->location <= 17)
	{
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 1)] = buf[0];
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 2)] = buf[1];
	}
	else if (playerLocation->location >= 18 && playerLocation->location <= 27)
	{
		boardpan[1][(playerNum * 2 + 1) + (11 * (playerLocation->location - 18))] = buf[0];
		boardpan[1][(playerNum * 2 + 2) + (11 * (playerLocation->location - 18))] = buf[1];
	}
	else if (playerLocation->location >= 28 && playerLocation->location <= 35)
	{
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 99] = buf[0];
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 100] = buf[1];
	}

}

void printcolor(int color) { // 색 바꿔주는 함수.
	if (color == WHITE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	else if (color == BLUE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	else if (color == GREEN) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	else if (color == RED) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	else if (color == YELLOW) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
}

void printHaveBoard(int i, int j, int haveplayer, struct player* playerHaveBoard) { // 아 줄이고싶다
	char buf[16] = { 0 };
	if (haveplayer == 0) return 0;
	if (haveplayer <= 4)
	{
		for (int a = 0; a < haveplayer - 1; a++)
		{
			for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++)
			{
				boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
				j++;
			}
			boardpan[i][j] = '(';
			j++;
			for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++)
			{
				boardpan[i][j] = buf[m];
				j++;
			}
			boardpan[i][j] = 'k'; j++;
			boardpan[i][j] = ')'; j++;
			for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++)
			{
				boardpan[i][j] = ' ';
				j++;
			}
		}
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++)
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
	else if (haveplayer <= 8)
	{
		for (int a = 4; a < haveplayer - 1; a++)
		{
			for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++)
			{
				boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
				j++;
			}
			boardpan[i][j] = '(';
			j++;
			for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++)
			{
				boardpan[i][j] = buf[m];
				j++;
			}
			boardpan[i][j] = 'k'; j++;
			boardpan[i][j] = ')'; j++;
			for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++)
			{
				boardpan[i][j] = ' ';
				j++;
			}
		}
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++)
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
	else if (haveplayer <= 12)
	{
		for (int a = 8; a < haveplayer - 1; a++)
		{
			for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++)
			{
				boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
				j++;
			}
			boardpan[i][j] = '(';
			j++;
			for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++)
			{
				boardpan[i][j] = buf[m];
				j++;
			}
			boardpan[i][j] = 'k'; j++;
			boardpan[i][j] = ')'; j++;
			for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++)
			{
				boardpan[i][j] = ' ';
				j++;
			}
		}
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++)
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
	else if (haveplayer <= 16)
	{
		for (int a = 12; a < haveplayer - 1; a++)
		{
			for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++)
			{
				boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
				j++;
			}
			boardpan[i][j] = '(';
			j++;
			for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++)
			{
				boardpan[i][j] = buf[m];
				j++;
			}
			boardpan[i][j] = 'k'; j++;
			boardpan[i][j] = ')'; j++;
			for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++)
			{
				boardpan[i][j] = ' ';
				j++;
			}

		}
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++)
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
	else if (haveplayer <= 20)
	{
		for (int a = 16; a < haveplayer - 1; a++)
		{
			for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++)
			{
				boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
				j++;
			}
			boardpan[i][j] = '(';
			j++;
			for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++)
			{
				boardpan[i][j] = buf[m];
				j++;
			}
			boardpan[i][j] = 'k'; j++;
			boardpan[i][j] = ')'; j++;
			for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++)
			{
				boardpan[i][j] = ' ';
				j++;
			}
		}


		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++)
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

}

void printBuild(struct player* playerBuild) {

	char bufVilla[2] = "♠";
	char bufBuilding[2] = "♣";
	char bufHotel[2] = "♥";

	for (int i = 0; i < playerBuild->haveBoard; i++)
	{
		if (playerBuild->player_board[i]->build == 1)
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[37][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[37][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufVilla[0];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[1][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[1][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufVilla[0];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufVilla[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 2)
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[37][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[37][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
				boardpan[37][10 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[0];
				boardpan[37][11 + 11 * (9 - playerBuild->player_board[i]->num)] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][10] = bufVilla[0];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][11] = bufVilla[1];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufVilla[0];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[1][10 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[1][11 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
				boardpan[1][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[0];
				boardpan[1][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufVilla[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][109] = bufVilla[0];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][110] = bufVilla[1];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufVilla[0];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufVilla[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 3)
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[37][1 + 11 * (9 - playerBuild->player_board[i]->num)] = bufBuilding[0];
				boardpan[37][2 + 11 * (9 - playerBuild->player_board[i]->num)] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][1] = bufBuilding[0];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][2] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[1][1 + (11 * (playerBuild->player_board[i]->num - 18))] = bufBuilding[0];
				boardpan[1][2 + (11 * (playerBuild->player_board[i]->num - 18))] = bufBuilding[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][100] = bufBuilding[0];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][101] = bufBuilding[1];
			}
		}
		else if (playerBuild->player_board[i]->build == 4)
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[37][10 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[0];
				boardpan[37][11 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][10] = bufHotel[0];
				boardpan[33 - ((playerBuild->player_board[i]->num - 10) * 4)][11] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[1][10 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[0];
				boardpan[1][11 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][109] = bufHotel[0];
				boardpan[33 - ((35 - playerBuild->player_board[i]->num) * 4)][110] = bufHotel[1];
			}
		}
	}
}

int Dice_Move(struct player* _player, int* i, int k) { // i >> 무인도를 위한 카운트? k >> 플레이어
	char buf[2] = "★";
	char buf_hangul[18] = "플레이어 현재 위치";
	char buf_double[5] = "더블!";
	char buf_1[16] = { 0 };
	char buf_location[16] = { 0 };
	char island[10] = "무인도에서";
	char island2[17] = "번째 주사위입니다";
	char buf_count[16];
	char escape[12] = "무인도 탈출!";
	char doubleIsland[29] = "더블 연속 3번! 무인도로갑니다";
	int d1 = rand() % 6 + 1;
	int u = 18;
	for (int i = 0; i < 12; i++)
	{
		boardpan[11][124+i] =' ';
	}
	boardpan[11][131] = ' ';
	for (int i = 0; i < 10; i++)
	{
		boardpan[11][124 + i] = ' ';
	}
	for (int i = 0; i < 17; i++)
	{
		boardpan[11][137 + i] = ' ';
	}
	boardpan[11][136] = ' ';
	for (int b = 0; b < 18; b++)
	{
		boardpan[10][128 + b] = ' ';
	}

	for (int i = 0; i < 5; i++)
	{
		boardpan[8][137 + i] = ' ';
	}
	for (int i = 0; i < 2; i++)
	{
		boardpan[8][142 + i] = ' ';
	}
	{
		boardpan[3][122] = ' ';
		boardpan[3][123] = ' ';
		boardpan[3][120] = ' ';
		boardpan[3][121] = ' ';
		boardpan[3][125] = ' ';
		boardpan[3][126] = ' ';
		boardpan[1][119] = ' ';
		boardpan[1][120] = ' ';
		boardpan[5][126] = ' ';
		boardpan[5][127] = ' ';
		boardpan[2][131] = ' ';
		boardpan[2][132] = ' ';
		boardpan[2][136] = ' ';
		boardpan[2][137] = ' ';
		boardpan[4][165] = ' ';
		boardpan[4][166] = ' ';
		boardpan[4][170] = ' ';
		boardpan[4][171] = ' ';
		boardpan[1][126] = ' ';
		boardpan[1][127] = ' ';
		boardpan[5][119] = ' ';
		boardpan[5][120] = ' ';
		boardpan[3][119] = ' ';
		boardpan[3][120] = ' ';
		boardpan[3][126] = ' ';
		boardpan[3][127] = ' ';
		// 첫번쨰 주사위
		boardpan[3][122 + u] = ' ';
		boardpan[3][123 + u] = ' ';
		boardpan[3][120 + u] = ' ';
		boardpan[3][121 + u] = ' ';
		boardpan[3][125 + u] = ' ';
		boardpan[3][126 + u] = ' ';
		boardpan[1][119 + u] = ' ';
		boardpan[1][120 + u] = ' ';
		boardpan[5][126 + u] = ' ';
		boardpan[5][127 + u] = ' ';
		boardpan[2][131 + u] = ' ';
		boardpan[2][132 + u] = ' ';
		boardpan[2][136 + u] = ' ';
		boardpan[2][137 + u] = ' ';
		boardpan[4][165 + u] = ' ';
		boardpan[4][166 + u] = ' ';
		boardpan[4][170 + u] = ' ';
		boardpan[4][171 + u] = ' ';
		boardpan[1][126 + u] = ' ';
		boardpan[1][127 + u] = ' ';
		boardpan[5][119 + u] = ' ';
		boardpan[5][120 + u] = ' ';
		boardpan[3][119 + u] = ' ';
		boardpan[3][120 + u] = ' ';
		boardpan[3][126 + u] = ' ';
		boardpan[3][127 + u] = ' ';
		boardpan[10][119] = ' ';
		boardpan[10][120] = ' ';
		boardpan[10][121] = ' ';
		boardpan[10][122] = ' ';
		boardpan[10][123] = ' ';
		boardpan[10][124] = ' ';
		boardpan[10][125] = ' ';
	}
	if (d1 == 1)
	{
		boardpan[3][122] = buf[0];
		boardpan[3][123] = buf[1];
	}
	else if (d1 == 2)
	{
		boardpan[3][120] = buf[0];
		boardpan[3][121] = buf[1];
		boardpan[3][125] = buf[0];
		boardpan[3][126] = buf[1];
	}
	else if (d1 == 3)
	{
		boardpan[3][122] = buf[0];
		boardpan[3][123] = buf[1];
		boardpan[1][119] = buf[0];
		boardpan[1][120] = buf[1];
		boardpan[5][126] = buf[0];
		boardpan[5][127] = buf[1];
	}
	else if (d1 == 4)
	{
		boardpan[2][131] = buf[0];
		boardpan[2][132] = buf[1];
		boardpan[2][136] = buf[0];
		boardpan[2][137] = buf[1];
		boardpan[4][165] = buf[0];
		boardpan[4][166] = buf[1];
		boardpan[4][170] = buf[0];
		boardpan[4][171] = buf[1];
	}
	else if (d1 == 5)
	{
		boardpan[3][122] = buf[0];
		boardpan[3][123] = buf[1];
		boardpan[1][119] = buf[0];
		boardpan[1][120] = buf[1];
		boardpan[1][126] = buf[0];
		boardpan[1][127] = buf[1];
		boardpan[5][126] = buf[0];
		boardpan[5][127] = buf[1];
		boardpan[5][119] = buf[0];
		boardpan[5][120] = buf[1];
	}
	else
	{
		boardpan[1][119] = buf[0];
		boardpan[1][120] = buf[1];
		boardpan[1][126] = buf[0];
		boardpan[1][127] = buf[1];
		boardpan[3][119] = buf[0];
		boardpan[3][120] = buf[1];
		boardpan[3][126] = buf[0];
		boardpan[3][127] = buf[1];
		boardpan[5][126] = buf[0];
		boardpan[5][127] = buf[1];
		boardpan[5][119] = buf[0];
		boardpan[5][120] = buf[1];
	}
	int d2 = rand() % 6 + 1;
	if (d2 == 1)
	{
		boardpan[3][122 + u] = buf[0];
		boardpan[3][123 + u] = buf[1];
	}
	else if (d2 == 2)
	{
		boardpan[3][120 + u] = buf[0];
		boardpan[3][121 + u] = buf[1];
		boardpan[3][125 + u] = buf[0];
		boardpan[3][126 + u] = buf[1];
	}
	else if (d2 == 3)
	{
		boardpan[3][122 + u] = buf[0];
		boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0];
		boardpan[1][120 + u] = buf[1];
		boardpan[5][126 + u] = buf[0];
		boardpan[5][127 + u] = buf[1];
	}
	else if (d2 == 4)
	{
		boardpan[2][131 + u] = buf[0];
		boardpan[2][132 + u] = buf[1];
		boardpan[2][136 + u] = buf[0];
		boardpan[2][137 + u] = buf[1];
		boardpan[4][165 + u] = buf[0];
		boardpan[4][166 + u] = buf[1];
		boardpan[4][170 + u] = buf[0];
		boardpan[4][171 + u] = buf[1];
	}
	else if (d2 == 5)
	{
		boardpan[3][122 + u] = buf[0];
		boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0];
		boardpan[1][120 + u] = buf[1];
		boardpan[1][126 + u] = buf[0];
		boardpan[1][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0];
		boardpan[5][127 + u] = buf[1];
		boardpan[5][119 + u] = buf[0];
		boardpan[5][120 + u] = buf[1];
	}
	else
	{
		boardpan[1][119 + u] = buf[0];
		boardpan[1][120 + u] = buf[1];
		boardpan[1][126 + u] = buf[0];
		boardpan[1][127 + u] = buf[1];
		boardpan[3][119 + u] = buf[0];
		boardpan[3][120 + u] = buf[1];
		boardpan[3][126 + u] = buf[0];
		boardpan[3][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0];
		boardpan[5][127 + u] = buf[1];
		boardpan[5][119 + u] = buf[0];
		boardpan[5][120 + u] = buf[1];
	}
	_itoa(d1 + d2, buf_1, 10);
	boardpan[8][144] = buf_1[0];
	boardpan[8][145] = buf_1[1];

	if (_player->location == 9) { // 플레이어 위치가 무인도일때
		_player->count++;
		if (_player->count == 3)
		{
			for (int i = 0; i < 12; i++)
			{
				boardpan[11][124 + i] = escape[i];
			}
		}
		if (_player->count < 3) {

			if (d1 == d2) { // 더블일때
				for (int i = 0; i < 5; i++)
				{
					boardpan[8][137 + i] = buf_double[i];
				}
				_player->location += d1 + d2; // 위치 업데이트
				_player->count = 0; // player->count 업데이트
				for (int i = 0; i < 12; i++)
				{
					boardpan[11][124+i] = escape[i];
				}
				if (k == 1)
				{
					boardpan[10][120] = 'B';
					boardpan[10][121] = 'l';
					boardpan[10][122] = 'u';
					boardpan[10][123] = 'e';
				}
				else if (k == 2)
				{
					boardpan[10][120] = 'R';
					boardpan[10][121] = 'e';
					boardpan[10][122] = 'd';
				}
				else if (k == 3)
				{
					boardpan[10][120] = 'G';
					boardpan[10][121] = 'r';
					boardpan[10][122] = 'e';
					boardpan[10][123] = 'e';
					boardpan[10][124] = 'n';
				}
				else if (k == 4)
				{
					boardpan[10][120] = 'Y';
					boardpan[10][121] = 'e';
					boardpan[10][122] = 'l';
					boardpan[10][123] = 'l';
					boardpan[10][124] = 'o';
					boardpan[10][125] = 'w';
				}
				for (int i = 0; i < 18; i++)
				{
					boardpan[10][128 + i] = buf_hangul[i];
				}
				_itoa(_player->location, buf_location, 10);
				for (int i = 0; i < 2; i++)
				{
					boardpan[10][147 + i] = buf_location[i];
				}

			}
			if (k == 1)
			{
				boardpan[10][120] = 'B';
				boardpan[10][121] = 'l';
				boardpan[10][122] = 'u';
				boardpan[10][123] = 'e';
			}
			else if (k == 2)
			{
				boardpan[10][120] = 'R';
				boardpan[10][121] = 'e';
				boardpan[10][122] = 'd';
			}
			else if (k == 3)
			{
				boardpan[10][120] = 'G';
				boardpan[10][121] = 'r';
				boardpan[10][122] = 'e';
				boardpan[10][123] = 'e';
				boardpan[10][124] = 'n';
			}
			else if (k == 4)
			{
				boardpan[10][120] = 'Y';
				boardpan[10][121] = 'e';
				boardpan[10][122] = 'l';
				boardpan[10][123] = 'l';
				boardpan[10][124] = 'o';
				boardpan[10][125] = 'w';
			}
			for (int b = 0; b < 18; b++) // 플레이어 현재 위치 출력해주는거
			{
				boardpan[10][128 + b] = buf_hangul[b];
			}
			
			_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
			for (int i = 0; i < 2; i++)
			{
				boardpan[10][147 + i] = buf_location[i];
			}
			if (_player->location == 9)
			{
				for (int i = 0; i < 10; i++)
				{
					boardpan[11][124 + i] = island[i]; // 무인도 몇번째에서 출력
				}
				for (int i = 0; i < 17; i++)
				{
					boardpan[11][136 + i] = island2[i]; // 무인도 번째입니다 출력
				}
				_itoa(_player->count, buf_count, 10);
				boardpan[11][135] = buf_count[0]; // 몇번째인지 숫자 출력
			}
			return 0; // 더블이 아니면 그냥 종료
		}
		else if (_player->count >= 3) { // 무인도에서 3번이상 더블일경우 player->count =0으로 초기화
			_player->count = 0;
		}
	}

	if (d1 == d2) { // 더블일때
		*i += 1;
		for (int i = 0; i < 5; i++)
		{
			boardpan[8][137 + i] = buf_double[i]; // 더블! 출력
		}
		//printf("더블 %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) { // 더블이 3번이상일경우

			_player->location = 9; // 무인도행
			for (int i = 0; i < 29; i++)
			{
				boardpan[11][124+i] = doubleIsland[i];
			}
			if (k == 1)
			{
				boardpan[10][120] = 'B';
				boardpan[10][121] = 'l';
				boardpan[10][122] = 'u';
				boardpan[10][123] = 'e';
			}
			else if (k == 2)
			{
				boardpan[10][120] = 'R';
				boardpan[10][121] = 'e';
				boardpan[10][122] = 'd';
			}
			else if (k == 3)
			{
				boardpan[10][120] = 'G';
				boardpan[10][121] = 'r';
				boardpan[10][122] = 'e';
				boardpan[10][123] = 'e';
				boardpan[10][124] = 'n';
			}
			else if (k == 4)
			{
				boardpan[10][120] = 'Y';
				boardpan[10][121] = 'e';
				boardpan[10][122] = 'l';
				boardpan[10][123] = 'l';
				boardpan[10][124] = 'o';
				boardpan[10][125] = 'w';
			}
			for (int b = 0; b < 18; b++) // 플레이어 현재 위치 출력해주는거
			{
				boardpan[10][128 + b] = buf_hangul[b];
			}

			_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
			for (int i = 0; i < 2; i++)
			{
				boardpan[10][147 + i] = buf_location[i];
			}

			return 0; // 종료
		}
	}
	if (k == 1)
	{
		boardpan[10][120] = 'B';
		boardpan[10][121] = 'l';
		boardpan[10][122] = 'u';
		boardpan[10][123] = 'e';
	}
	else if (k == 2)
	{
		boardpan[10][120] = 'R';
		boardpan[10][121] = 'e';
		boardpan[10][122] = 'd';
	}
	else if (k == 3)
	{
		boardpan[10][120] = 'G';
		boardpan[10][121] = 'r';
		boardpan[10][122] = 'e';
		boardpan[10][123] = 'e';
		boardpan[10][124] = 'n';
	}
	else if (k == 4)
	{
		boardpan[10][120] = 'Y';
		boardpan[10][121] = 'e';
		boardpan[10][122] = 'l';
		boardpan[10][123] = 'l';
		boardpan[10][124] = 'o';
		boardpan[10][125] = 'w';
	}
	for (int b = 0; b < 18; b++)
	{
		boardpan[10][128 + b] = buf_hangul[b];
	}
	_player->location += d1 + d2; // 더블이면서 3번이상 나오지 않았으면 위치 업데이트
	if (_player->location > 36) {
		_player->location %= 36;
	}
	_itoa(_player->location, buf_location, 10);
	for (int i = 0; i < 2; i++)
	{
		boardpan[10][147 + i] = buf_location[i];
	}

	if (d1 == d2) { // 만약 더블일경우 return 1
		return 1;
	}
	return 0; // 아닐경우 그냥 종료
}

void Island(int* count) {
	*count += 1;

}