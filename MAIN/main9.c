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
	"┠━━  15 ━━━┫                                                                                       ┠━━  30 ━━━┫                                                                         ",
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
void GoldenKey(struct player* player_); // 황금 열쇠
void print_string(char* str, int number); // 문자열 출력시켜주는거
void clear_string(void); // 문자열 ' '으로 초기화해주는거
void clear(int i, int j, int k);
void printPlayer(int k);
void printString(int i, int j, int k, char* name);
void sell(struct board* _boardCell, struct player* Player)//_boardCell은 보드 구조체의 주소, Player는 현재 차례인 플레이어 구조체의 주소.
void buy(struct board* _boardCell, struct player* Player)
void build(struct board* _boardCell, struct player* Player)

int main(void) {
	int k;
	srand((unsigned)time(NULL)); // 랜덤

	for (int m = 0; m < 200; m++) { // 보드판 출력 반복.
		k = 0; // k값 이용해서 아마 더블 표현?
		int i = m % 4; // 플레이어 구분
		int ch = getchar(); // 엔터키 입력시 시작.
		play[0].haveBoard = 9;
		play[1].haveBoard = 9;
		play[2].haveBoard = 9;
		play[3].haveBoard = 9;
		play[0].color = BLUE;
		play[1].color = RED;
		play[2].color = GREEN;
		play[3].color = YELLOW;
		for (int i = 0; i < 9; i++)
		{
			play[0].player_board[i] = &boardCell[i];
			play[1].player_board[i] = &boardCell[i + 9];
			play[2].player_board[i] = &boardCell[i + 18];
			play[3].player_board[i] = &boardCell[i + 27];
			boardCell[i].get_player = &play[0];
			boardCell[i+9].get_player = &play[1];
			boardCell[i+18].get_player = &play[2];
			boardCell[i+27].get_player = &play[3];
			boardCell[i].build = 2;
			boardCell[i+9].build = 2;
			boardCell[i+18].build = 2;
			boardCell[i+27].build = 2;
		}

		if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // 주사위 굴리기 // 리턴값이 0이 아니면 다시굴리기 0이면 끝 // 더블이면 리턴 1 >> 다시 반복

			printBuild(&play[0]); // play0의 건물 가운데에 출력
			printBuild(&play[1]); 
			printBuild(&play[2]);
			printBuild(&play[3]);
			movePlayer(&play[0], 1); // 플레이어 이동하는거 출력해줌(별모양으로)
			movePlayer(&play[1], 2);
			movePlayer(&play[2], 3);
			movePlayer(&play[3], 4);

			print_board(); // 보드판 출력
			int ch = getchar(); // 엔터 입력

			if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // 주사위 굴리기 // 리턴값이 0이 아니면 다시굴리기 0이면 끝 // 더블이면 리턴 1 >> 다시 반복

				printBuild(&play[0]); // play0의 건물 가운데에 출력
				printBuild(&play[1]);
				printBuild(&play[2]);
				printBuild(&play[3]);
				movePlayer(&play[0], 1); // 플레이어 이동하는거 출력해줌(별모양으로)
				movePlayer(&play[1], 2);
				movePlayer(&play[2], 3);
				movePlayer(&play[3], 4);

				print_board(); // 보드판 출력
				int ch = getchar(); // 엔터 입력

				if (Dice_Move(&play[i], &k, i + 1) && ch != 0) { // 주사위 굴리기 // 리턴값이 0이 아니면 다시굴리기 0이면 끝 // 더블이면 리턴 1 >> 다시 반복

					printBuild(&play[0]); // play0의 건물 가운데에 출력
					printBuild(&play[1]);
					printBuild(&play[2]);
					printBuild(&play[3]);
					movePlayer(&play[0], 1); // 플레이어 이동하는거 출력해줌(별모양으로)
					movePlayer(&play[1], 2);
					movePlayer(&play[2], 3);
					movePlayer(&play[3], 4);

					print_board();
					int ch = getchar(); // 엔터 입력
				}
			}
		}

		printBuild(&play[0]); // play0의 건물 가운데에 출력
		printBuild(&play[1]);
		printBuild(&play[2]);
		printBuild(&play[3]);
		movePlayer(&play[0], 1); // 플레이어 이동하는거 출력해줌(별모양으로)
		movePlayer(&play[1], 2);
		movePlayer(&play[2], 3);
		movePlayer(&play[3], 4);

		print_board(); // 보드판 출력
	}
}

void print_board(void) { // 보드판 출력
	if (play[0].haveBoard <= 4) // Blue 땅값 정보 >> printHaveBoard함수부분 주석 참고. >> 출력해야할 y축이 색마다 다르기 때문에 4개 전부 각각 함수를 사용해줌.
	{
		printHaveBoard(12, 30, play[0].haveBoard, &play[0]); // y축으로 12번째, x축으로 30번째에 문자열 출력해줌(보유 건물들)
	}
	else if (play[0].haveBoard <= 8)
	{
		printHaveBoard(12, 30, 4, &play[0]); // y축으로 12번쨰, x축으로 30번째에 문자열 출력해줌.
		printHaveBoard(13, 23, play[0].haveBoard, &play[0]); // y축 13번쨰, x축으로 23번째에 문자열 출력 >> 이런식으로 아래에 적용
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
	if (play[1].haveBoard <= 4) //------------------------------------------------- Red 땅값 정보 
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
	if (play[2].haveBoard <= 4) //----------------------------------------- Green 땅값 정보
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
	if (play[3].haveBoard <= 4) // -----------------------------------------Yellow 땅값 정보
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
	 // 여기까지 가운데 건물 출력.
	for (int i = 0; i < 41; i++) // 여기부터 보드판 출력(옆부분 10*10)
	{
		if (i % 4 == 1) // 플레이어 위치를 알려주는 *를 출력해주는 자리
		{
			for (int j = 0; j < 250; j++)
			{
				if (j % 11 == 3 && j <= 114 && (i == 1 || i == 37)) { printcolor(BLUE); printf("%c", boardpan[i][j]); } // 플레이어 위치 가 출력되는 위치에 따라 색깔 출력
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

		else if (i == 10) // 맨 오른쪽 주사위 밑부분 플레이어 현황 보여주기 위함.
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
		else if (i == 11) // Blue출력해주는 부분(보유 금액, 건물 출력(보드셀에 색깔있는 건물))
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
				else if ((j == 1 && boardCell[(73 - i) / 4].get_player != NULL)) { printcolor(boardCell[(73 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); } // 여기부터 건물 출력. 그 건물의 보유 플레이어의 구조체로 찾아가 색 출력
				else if (j == 2 && boardCell[(73 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(73 - i) / 4].get_player != NULL)) { printcolor(boardCell[(73 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(73 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else printf("%c", boardpan[i][j]);
			}
		}
		else if (i == 23) // Green 출력해주는 부분(보유 금액, 건물 출력(보드셀에 색깔있는 건물))
		{
			for (int j = 0; j < 180; j++)
			{
				if ((j == 1 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); } // 여기부터 건물 출력. 그 건물의 보유 플레이어의 구조체로 찾아가 색 출력
				else if (j == 2 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 10 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 11 && boardCell[(77 - i) / 4].get_player != NULL) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 100 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 101 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if ((j == 109 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35))) { printcolor(boardCell[(27 + (i / 4))].get_player->color); printf("%c", boardpan[i][j]); }
				else if (j == 110 && boardCell[27 + (i / 4)].get_player != NULL && (i >= 5 && i <= 35)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j == 21) { printcolor(GREEN); printf("%c", boardpan[i][j]); }
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
		else if (i % 4 == 3) // 건물 출력해주는 부분.
		{
			for (int j = 0; j < 250; j++)
			{

				if (j % 11 == 1 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(앞부분)
				else if (j % 11 == 2 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 3 && (boardCell[18 + j / 11].get_player != NULL)) { printcolor(boardCell[18 + j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(뒷부분)
				else if (j % 11 == 0 && j <= 114 && i == 3 && (boardCell[17 + j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 1 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(앞부분)
				else if (j % 11 == 2 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printf("%c", boardpan[i][j]); printcolor(WHITE); }
				else if (j % 11 == 10 && j <= 114 && i == 39 && (boardCell[9 - j / 11].get_player != NULL)) { printcolor(boardCell[9 - j / 11].get_player->color); printf("%c", boardpan[i][j]); } // 건물 색칠하기(뒷부분)
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

		else // 나머지 출력
		{
			for (int j = 0; j < 250; j++)
			{
				printf("%c", boardpan[i][j]);
			}
		}

		printf("\n");
	}
}

void movePlayer(struct player* playerLocation, int playerNum) { // 플레이어의 위치에 따라 '★'기호를 문자열에 저장시켜줌
	char buf[2] = "★";
	for (int i = 0; i < 10; i++) // 우선 전부 초기화. (이동할때 출력이 되면 안되기 떄문.)
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
	if (playerLocation->location >= 0 && playerLocation->location <= 9) // 플레이어 위치가 0~9일때 해당하는 문자열(출력되는 위치)
	{
		boardpan[37][(playerNum * 2 + 1) + 11 * (9 - playerLocation->location)] = buf[0];
		boardpan[37][(playerNum * 2 + 2) + 11 * (9 - playerLocation->location)] = buf[1];

	}
	else if (playerLocation->location >= 10 && playerLocation->location <= 17) // 플레이어 위치가 10~17일때 해당하는 문자열에 별모양 저장.
	{
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 1)] = buf[0];
		boardpan[33 - ((playerLocation->location - 10) * 4)][(playerNum * 2 + 2)] = buf[1];
	}
	else if (playerLocation->location >= 18 && playerLocation->location <= 27) // 플레이어 위치가 18~27일때 해당하는 문자열에 별모양 저장.
	{
		boardpan[1][(playerNum * 2 + 1) + (11 * (playerLocation->location - 18))] = buf[0];
		boardpan[1][(playerNum * 2 + 2) + (11 * (playerLocation->location - 18))] = buf[1];
	}
	else if (playerLocation->location >= 28 && playerLocation->location <= 35)// 플레이어 위치가 28~35일때 해당하는 문자열에 별모양 저장.
	{
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 99] = buf[0];
		boardpan[33 - ((35 - playerLocation->location) * 4)][(playerNum * 2 + 1) + 100] = buf[1];
	}

}

void printcolor(int color) { // 색 바꿔주는 함수. // 맨위 정의한 값들 참고.
	if (color == WHITE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	else if (color == BLUE) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	else if (color == GREEN) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	else if (color == RED) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	else if (color == YELLOW) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
}

/*보유 건물을 가운데에 출력해주는 함수.
i는 출력이 시작되는 y축, j는 출력이 시작되는 x축 playerHaveBoard는 플레이어의 구조체로 찾아가 보유한 건물을 알기 위한 변수, haveplayer는 보유 건물 개수..
1줄마다 4개씩 출력해주기 위해 4,8,12,16일때를 각각 정의해줌.*/
void printHaveBoard(int i, int j, int haveplayer, struct player* playerHaveBoard) {
	char buf[16] = { 0 };
	int a = 0;
	if (haveplayer == 0) return 0; // 보유 건물이 없을경우 바로 리턴.
	if (haveplayer <= 4) a = 0;
	else if (haveplayer <= 8) a = 4;
	else if (haveplayer <= 12) a = 8;
	else if (haveplayer <= 16) a = 12;
	else if (haveplayer <= 20) a = 16;
	for (; a < haveplayer - 1; a++) // haveplayer만큼 문자열에 저장.
	{
		for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[a]->name); k++) // k=0부터 player가 가지고 있는 a번째 건물의 이름만큼 문자열에 저장.
		{
			boardpan[i][j] = playerHaveBoard->player_board[a]->name[k];
			j++; // x축은 계속해서 증가시켜줌.
		}
		boardpan[i][j] = '('; // '('저장
		j++; // x축 증가
		for (unsigned int m = 0; m < strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)); m++) // m=0부터 플레이어가 가지고 있는 a번째 건물의 통행료의 길이만큼 문자열에 저장.
		{
			boardpan[i][j] = buf[m]; // 통행료 저장.
			j++; // x축 증가
		}
		boardpan[i][j] = 'k'; j++; // k저장, x축 증가
		boardpan[i][j] = ')'; j++; // ')'저장, x축 증가
		for (unsigned int n = 0; n < 15 - (strlen(_itoa(playerHaveBoard->player_board[a]->pass_value / 1000, buf, 10)) + strlen(playerHaveBoard->player_board[a]->name)); n++) // 정해진 줄만큼만 출력해주고 나머지는 빈칸으로 출력.
		{
			boardpan[i][j] = ' ';
			j++;
		}
	}
	for (unsigned int k = 0; k < strlen(playerHaveBoard->player_board[haveplayer - 1]->name); k++) // 마지막 haveplayer번째 출력.(위와 동일함)
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

	char bufVilla[2] = "♠";
	char bufBuilding[2] = "♣";
	char bufHotel[2] = "♥";
	char buf[2] = { 0 };


	for (int i = 0; i < playerBuild->haveBoard; i++) // 가지고 있는 건물수 만큼 문자열에 저장.
	{
		if (playerBuild->player_board[i]->build == 1) // 건물 1개 일때 >> Villa 출력
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
		else if (playerBuild->player_board[i]->build == 2) // 건물 2개 일때 villa출력
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
		else if (playerBuild->player_board[i]->build == 3) // 3일때 빌딩
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
		else if (playerBuild->player_board[i]->build == 4) // 4일때 호텔
		{
			if (playerBuild->player_board[i]->num >= 0 && playerBuild->player_board[i]->num <= 9)
			{
				boardpan[39][10 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[0];
				boardpan[39][11 + 11 * (9 - playerBuild->player_board[i]->num)] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 10 && playerBuild->player_board[i]->num <= 17)
			{
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][10] = bufHotel[0];
				boardpan[35 - ((playerBuild->player_board[i]->num - 10) * 4)][11] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 18 && playerBuild->player_board[i]->num <= 27)
			{
				boardpan[3][10 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[0];
				boardpan[3][11 + (11 * (playerBuild->player_board[i]->num - 18))] = bufHotel[1];
			}
			else if (playerBuild->player_board[i]->num >= 28 && playerBuild->player_board[i]->num <= 35)
			{
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][109] = bufHotel[0];
				boardpan[35 - ((35 - playerBuild->player_board[i]->num) * 4)][110] = bufHotel[1];
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
	int u = 18;
	for (int i = 0; i < 17; i++)
	{
		boardpan[11][124 + i] = ' ';
		boardpan[10][128 + i] = ' ';
	}
	for (int i = 0; i < 50; i++)
	{
		boardpan[12][138 + i] = ' '; // 무인도 몇번째에서 출력
	}

	for (int i = 0; i < 7; i++)
	{
		boardpan[8][137 + i] = ' ';
	}
	{
		clear(3, 119, 9); clear(1, 119, 9);	// 첫번째 주사위 가운데 초기화
		clear(5, 119, 9); clear(2, 131, 7); clear(4, 165, 7);
		
		
		// 첫번쨰 주사위
		clear(3, 119 + u, 9); clear(1, 119 + u, 9); // 두번째 주사위 가운데 초기화
		clear(5, 119 + u, 9); clear(2, 131 + u, 7); clear(4, 165 + u, 7);
		
		clear(10, 119, 7); // 이름 나오는 부분 초기화
	
	}

	int d1 = rand() % 6 + 1;
	if (d1 == 1) { boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1]; } // 주사위 1일때(주사위 눈 저장)
	else if (d1 == 2) // 주사위 2일때
	{
		boardpan[3][120] = buf[0]; boardpan[3][121] = buf[1];
		boardpan[3][125] = buf[0]; boardpan[3][126] = buf[1];
	}
	else if (d1 == 3) // 주사위 3일때
	{
		boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1];
		boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1]; 
		boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1];
	}
	else if (d1 == 4) // 주사위 4일때
	{
		boardpan[2][131] = buf[0]; boardpan[2][132] = buf[1];
		boardpan[2][136] = buf[0]; boardpan[2][137] = buf[1];
		boardpan[4][165] = buf[0]; boardpan[4][166] = buf[1];
		boardpan[4][170] = buf[0]; boardpan[4][171] = buf[1];
	}
	else if (d1 == 5) // 주사위 5일떄
	{
		boardpan[3][122] = buf[0]; boardpan[3][123] = buf[1]; boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1]; 
		boardpan[1][126] = buf[0]; boardpan[1][127] = buf[1]; boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1]; 
		boardpan[5][119] = buf[0]; boardpan[5][120] = buf[1];
	}
	else // 주사위 6일때
	{
		boardpan[1][119] = buf[0]; boardpan[1][120] = buf[1]; boardpan[1][126] = buf[0]; boardpan[1][127] = buf[1];
		boardpan[3][119] = buf[0]; boardpan[3][120] = buf[1]; boardpan[3][126] = buf[0]; boardpan[3][127] = buf[1];
		boardpan[5][126] = buf[0]; boardpan[5][127] = buf[1]; boardpan[5][119] = buf[0]; boardpan[5][120] = buf[1];
	}
	int d2 = rand() % 6 + 1; // 두번쨰 주사위 굴리기
	if (d2 == 1) {boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1];} // 1일때
	else if (d2 == 2) // 2일때
	{
		boardpan[3][120 + u] = buf[0]; boardpan[3][121 + u] = buf[1];
		boardpan[3][125 + u] = buf[0]; boardpan[3][126 + u] = buf[1];
	}
	else if (d2 == 3) // 3일때
	{
		boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1];
	}
	else if (d2 == 4) // 4일때
	{
		boardpan[2][131 + u] = buf[0]; boardpan[2][132 + u] = buf[1]; boardpan[2][136 + u] = buf[0]; boardpan[2][137 + u] = buf[1];
		boardpan[4][165 + u] = buf[0]; boardpan[4][166 + u] = buf[1]; boardpan[4][170 + u] = buf[0]; boardpan[4][171 + u] = buf[1];
	}
	else if (d2 == 5) // 5일때
	{
		boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1];
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1];
		boardpan[1][126 + u] = buf[0]; boardpan[1][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1];
		boardpan[5][119 + u] = buf[0]; boardpan[5][120 + u] = buf[1];
	}
	else // 6일때
	{
		boardpan[1][119 + u] = buf[0]; boardpan[1][120 + u] = buf[1]; boardpan[1][126 + u] = buf[0]; boardpan[1][127 + u] = buf[1];
		boardpan[3][119 + u] = buf[0]; boardpan[3][120 + u] = buf[1]; boardpan[3][126 + u] = buf[0]; boardpan[3][127 + u] = buf[1];
		boardpan[5][126 + u] = buf[0]; boardpan[5][127 + u] = buf[1]; boardpan[5][119 + u] = buf[0]; boardpan[5][120 + u] = buf[1];
	}

	_itoa(d1 + d2, buf_1, 10); // buf_1에 d1+d2를 문자로 저장.
	boardpan[8][144] = buf_1[0]; // 몇인지 출력하기 위해
	boardpan[8][145] = buf_1[1]; // 숫자 나오는 부분에 숫자를 문자로 저장.

	if (_player->location == 27 && _player->money > 20000) { // 여행
		int target;
		printf("원하는 위치를 선택하시오(숫자)");
		scanf("%d", &target);
		_player->location = target;
		if (target > 27 && target < 36) {
			_player->money -= 20000;
		}
		system("cls");
		return 0;
	}
	system("cls");
	if (_player->location == 9) { // 플레이어 위치가 무인도일때
		_player->count++;
		if (_player->count == 3) printString(12, 138, 12, escape); // 무인도 탈출! 출력
		if (_player->count < 3) {

			if (d1 == d2) { // 더블일때
				printString(8, 137, 5, buf_double); // 더블! 출력
				
				_player->location += d1 + d2; // 위치 업데이트
				_player->count = 0; // player->count 업데이트
				printString(12, 138, 12, escape); // 무인도 탈출! 출력
				printPlayer(k);
				printString(10, 128,18, buf_hangul); // 플레이어 위치 출력
				_itoa(_player->location, buf_location, 10);
				printString(10, 147, 2, buf_location); // 위치 출력

			}
			printPlayer(k);
			printString(10, 128, 18, buf_hangul);

			_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
			printString(10, 147, 2, buf_location);
			if (_player->location == 9)
			{
				printString(12, 138, 10, island);// 무인도에서 출력
				printString(12, 150, 17, island2);
				_itoa(_player->count, buf_count, 10); // 몇번째 출력
				boardpan[12][149] = buf_count[0]; // 몇번째인지 숫자 출력
			}
			return 0; // 더블이 아니면 그냥 종료
		}
		else if (_player->count >= 3) { // 무인도에서 3번이상 더블일경우 player->count =0으로 초기화
			_player->count = 0;
			_player->money += 200000;
		}
	}

	if (d1 == d2) { // 더블일때
		*i += 1;
		printString(8, 137, 5, buf_double);
		//printf("더블 %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) { // 더블이 3번이상일경우

			_player->location = 9; // 무인도행
			printString(12, 138, 29, doubleIsland);
			printPlayer(k);
			printString(10, 128, 18, buf_hangul);
			_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
			printString(10, 147, 2, buf_location);

			return 0; // 종료
		}
	}
	_player->location += d1 + d2; // 더블이면서 3번이상 나오지 않았으면 위치 업데이트
	if (_player->location > 36) {
		_player->location %= 36;
	}

	if (_player->location == 2 || _player->location == 6 || _player->location == 11 || _player->location == 15 || _player->location == 20 || _player->location == 25 || _player->location == 31) {
		GoldenKey(_player);
	}
	printPlayer(k);
	printString(10, 128, 18, buf_hangul);
	_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
	printString(10, 147, 2, buf_location);

	if (d1 == d2) { // 만약 더블일경우 return 1
		return 1;
	}
	return 0; // 아닐경우 그냥 종료
}

void Island(int* count) {
	*count += 1;

}
void GoldenKey(struct player* player_) {
	char island[] = "무인도로 갑니다.";
	char prize[] = "보상금 100만원";
	char prize1[] = "보상금 50만원";
	char prize2[] = "보상금 30만원";
	char prize3[] = "보상금 20만원";
	char fine[] = "벌금 20만원";
	char fine2[] = "벌금 30만원";
	char fine3[] = "벌금 50만원";
	char trip[] = "세계여행으로 이동";
	char start[] = "출발지로 이동";
	char goldkey[] = "황금열쇠 칸입니다.";
	int r = rand() % 10;
	printf("%d번째 카드\n", r);
	for (int i = 0; i < 17; i++)
	{
		boardpan[11][124 + i] = goldkey[i];
	}
	switch (r) { // 위의 문자열 출력해줌.
	case 0:
		clear_string();
		print_string(island, 15);
		player_->location == 9;
		break;
	case 1:
		clear_string();
		print_string(prize, 14);
		player_->money += 1000000;
		break;
	case 2:
		clear_string();
		print_string(prize1, 13);
		player_->money += 500000;
		break;
	case 3:
		clear_string();
		print_string(prize2, 13);
		player_->money += 300000;
		break;
	case 4:
		clear_string();
		print_string(prize3, 13);
		player_->money += 200000;
		break;
	case 5:
		clear_string();
		print_string(fine, 11);
		player_->money -= 200000;
		break;
	case 6:
		clear_string();
		print_string(fine2, 11);
		player_->money -= 300000;
		break;
	case 7:
		clear_string();
		print_string(fine3, 11);
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
		boardpan[i][j+a] = ' ';
	}
}

void printPlayer(int k) { // 무슨 플레이어인지 출력
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
	printf("어떤 땅을 파시겠습니까? 땅의 번호를 입력하세요 : ");
	int number;
	scanf_s("%d", &number);
	switch ((_boardCell + number)->build) {
	case 1: Player->money += (_boardCell + number)->value;
		break;
	case 2: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 50000;
	}
	if (_boardCell + number)->num > 9 && _boardCell + number)->num < 18) {
	Player->money += 100000;
	}
	if (_boardCell + number)->num > 18 && _boardCell + number)->num < 27) {
	Player->money += 150000;
	}
	if (_boardCell + number)->num > 27 && _boardCell + number)->num < 36) {
	Player->money += 200000;
	}
	break;
	case 3: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 50000;
	}
	if (_boardCell + number)->num > 9 && _boardCell + number)->num < 18) {
	Player->money += 100000;
	}
	if (_boardCell + number)->num > 18 && _boardCell + number)->num < 27) {
	Player->money += 150000;
	}
	if (_boardCell + number)->num > 27 && _boardCell + number)->num < 36) {
	Player->money += 200000;
	}
	break;
	case 4: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 150000;
	}
	if (_boardCell + number)->num > 9 && _boardCell + number)->num < 18) {
	Player->money += 300000;
	}
	if (_boardCell + number)->num > 18 && _boardCell + number)->num < 27) {
	Player->money += 450000;
	}
	if (_boardCell + number)->num > 27 && _boardCell + number)->num < 36) {
	Player->money += 600000;
	}
	break;
	case 5: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 250000;
	}
	if (_boardCell + number)->num > 9 && _boardCell + number)->num < 18) {
	Player->money += 500000;
	}
	if (_boardCell + number)->num > 18 && _boardCell + number)->num < 27) {
	Player->money += 750000;
	}
	if (_boardCell + number)->num > 27 && _boardCell + number)->num < 36) {
	Player->money += 1000000;
	}
	break;
	}
	(_boardCell + number)->get_player->color = 0;
	Player->haveboard--;
}

void buy(struct board* _boardCell, struct player* Player) {//Player는 현재 차례인 플레이어.
	if ((_boardCell + Player->location)->get_player->color == 0 && (_boardCell + Player->location) != 0 && (_boardCell + Player->location) != 2 && (_boardCell + Player->location) != 6
		&& (_boardCell + Player->location) != 9 && (_boardCell + Player->location) != 11 && (_boardCell + Player->location) != 15 && (_boardCell + Player->location) != 18
		&& (_boardCell + Player->location) != 20 && (_boardCell + Player->location) != 25 && (_boardCell + Player->location) != 27 && (_boardCell + Player->location) != 31
		&& (_boardCell + Player->location) != 34) {//_boardCell은 boardCell[0]을 의미함. 거기에 Player->location을 더해줘서 [1],[2],[3],...[35]으로 취급.
		printf("이 땅을 사시겠습니까? (0번) 예 (1번) 아니요");
		int select;
		scanf_s("%d", &select);
		if (select == 0) {
			printf("이 땅의 가격은 %d원입니다. 정말로 사시겠습니까? (0번) 예 (1번) 아니요", (_boardCell + Player->location)->value);
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < (_boardCell + Player->location)->value) {
					printf("돈이 모자랍니다.");
				}
				else {
					Player->money -= (_boardCell + Player->location)->value;
					(_boardCell + Player->location)->get_player->color = Player->color;
					Player->player_board[Player->haveboard] = &boardCell[Player->location];
					boardCell[Player->location].get_player = Player;
					Player->haveboard++;
					(_boardCell + Player->location)->build++;


				}
			}
		}
	}
}

void build(struct board* _boardCell, struct player* Player) {
	int select = 0;
	if ((_boardCell + Player->location)->get_player->color == Player->color && (_boardCell + Player->location)->num != 35) {//땅의 소유주인 플레이어와 플레이하는 플레이어의 색깔이 같다면.
		if ((_boardCell + Player->location)->build == 0) {//아무것도 안 지어져 있을 때.
			printf("건설하시겠습니까? (0번) 스킵 (1번) 예");
			scanf_s("%d", &select);
		}
	}
	if ((_boardCell + Player->location)->build == 4) {//다 지어졌을 때.
		printf("더는 건설할 수 없습니다.");
	}
	if (select == 1 && (_boardCell + Player->location)->build != 5) {
		switch ((_boardCell + Player->location)->build) {
		case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("별장의 가격은 5만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < 50000) {
					printf("돈이 모자랍니다.");
				}
				else {
					(_boardCell + Player->location)->build += 1;
					Player->money -= 50000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 10만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 100000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 100000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 15만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 150000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  _boardCell->build += 1;
						  Player->money -= 150000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("별장의 가격은 20만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 200000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 200000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					  }
				  }
			  }
			  break;
		case 2:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("별장의 가격은 5만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < 50000) {
					printf("돈이 모자랍니다.");
				}
				else {
					(_boardCell + Player->location)->build += 1;
					Player->money -= 50000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 10만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 100000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 100000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 15만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 150000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  _boardCell->build += 1;
						  Player->money -= 150000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("별장의 가격은 20만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 200000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 200000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
					  }
				  }
			  }
			  break;
		case 3:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("빌딩의 가격은 15만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < 150000) {
					printf("돈이 모자랍니다.");
				}
				else {
					(_boardCell + Player->location)->build += 1;
					Player->money -= 150000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("빌딩의 가격은 30만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 300000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 300000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("빌딩의 가격은 45만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 450000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 450000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("빌딩의 가격은 60만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 600000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 600000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
					  }
				  }
			  }
			  break;
		case 4:if ((_boardCell + Player->location)->num > 0 && _boardCell->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("호텔의 가격은 25만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < 250000) {
					printf("돈이 모자랍니다.");
				}
				else {
					(_boardCell + Player->location)->build += 1;
					Player->money -= 250000;
					(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("호텔의 가격은 50만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 500000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 500000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel; .
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("호텔의 가격은 75만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 750000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 750000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 35 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("호텔의 가격은 100만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				  scanf_s("%d", &select);
				  if (select == 0) {
					  if (Player->money < 1000000) {
						  printf("돈이 모자랍니다.");
					  }
					  else {
						  (_boardCell + Player->location)->build += 1;
						  Player->money -= 1000000;
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
					  }
				  }
			  }
			  break;
		}
	}
}