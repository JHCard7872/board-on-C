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

struct player play[4] = {
		{0, BLUE, 2000000, 0, 0, NULL},
		{0, RED, 2000000,0, 0, NULL},
		{0, GREEN, 2000000,0, 0, NULL},
		{0, YELLOW,2000000,0, 0, NULL}
};

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
	"┃  Goldkey ┃                                                                                       ┃   Italy  ┃                                                           ",
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

int fund = 0;

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
	srand((unsigned)time(NULL)); // 랜덤
	int m = 0;
	print_board();

	while (1)
	{ // 보드판 출력 반복.
		k = 0; // k값 이용해서 아마 더블 표현?
		int i = m % 4; // 플레이어 구분
		int gameovercount = 0;
		for (int j = 0; j < 4; j++) // 게임오버
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
		int ch = getchar(); // 엔터키 입력시 시작.
		print_clear();


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
			if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
			if (boardCell[play[i].location].get_player != NULL)
			{
				build(boardCell, &play[i]);
			}
			buy(boardCell, &play[i]);
			if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
			print_clear;

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
				if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
				if (boardCell[play[i].location].get_player != NULL)
				{
					build(boardCell, &play[i]);
				}


				buy(boardCell, &play[i]);
				if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
				print_clear;
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
					if (boardCell[play[i].location].get_player != NULL && boardCell[play[i].location].get_player->color != play[i].color) Pass(boardCell, &play[i]);
					if (boardCell[play[i].location].get_player != NULL)
					{
						build(boardCell, &play[i]);
					}

					buy(boardCell, &play[i]);
					if (play[i].money <= 0 && play[i].haveBoard >= 1) sell(boardCell, &play[i]);
					print_clear();
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
	// 여기까지 가운데 건물 출력.
	for (int i = 0; i < 41; i++) // 여기부터 보드판 출력(옆부분 10*10)
	{
		if (i % 4 == 1) // 플레이어 위치를 알려주는 *를 출력해주는 자리
		{
			for (int j = 0; j < 250; j++)
			{
				if (j % 11 == 3 && j <= 114 && (i == 1 || i == 37)) { printcolor(play[0].color); printf("%c", boardpan[i][j]); } // 플레이어 위치 가 출력되는 위치에 따라 색깔 출력
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
				else if (i == 17 && j == 22) { printcolor(RED); printf("%c", boardpan[i][j]); } // Red 출력해주는 부분(빨간색으로)
				else if (i == 17 && j == 27) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 17 && j >= 36 && j <= 65 && play[1].money > 0)
				{
					if (i == 17 && j == 36 && play[1].location > 9) { printf("%d", play[1].location); } // 위치 출력
					else if (i == 17 && j == 38 && play[1].location > 9) { printf(""); }
					else if (i == 17 && j == 36 && play[1].location <= 9) { printf("%d", play[1].location); }
					else if (i == 17 && j == 45) { printf("%dk", play[1].money / 1000); } // 보유 금액 출력
					else if (i == 17 && j == 60)  printf("");
					else if (i == 17 && j == 62 && play[1].money > 9999 && play[1].money <= 99999) printf("");
					else if (i == 17 && j >= 62 && j <= 63 && play[1].money > 99999 && play[1].money <= 999999) { printf(""); }
					else if (i == 17 && j >= 62 && j <= 64 && play[1].money > 999999 && play[1].money <= 99999999) printf("");
					else if (i == 17 && j >= 62 && j <= 65 && play[1].money > 9999999 && play[1].money <= 999999999) printf("");
					else printf("%c", boardpan[i][j]);
				}
				else if (i == 17 && j >= 36 && j <= 39 && play[1].money <= 0) printf(" ");
				else if (i == 29 && j == 22) { printcolor(YELLOW); printf("%c", boardpan[i][j]); } // Green 출력해주는 부분(파란색으로)
				else if (i == 29 && j == 29) { printcolor(WHITE); printf("%c", boardpan[i][j]); }
				else if (i == 29 && j >= 36 && j <= 65 && play[3].money > 0)
				{
					if (i == 29 && j == 36 && play[3].location > 9) { printf("%d", play[3].location); } // 위치 출력
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
				else if (i == 29 && j >= 36 && j <= 39 && play[3].money <= 0) printf(" ");
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
				else if (j >= 36 && j <= 65 && play[0].money > 0)
				{
					if (j == 36 && play[0].location > 9) { printf("%d", play[0].location); } // 위치 출력
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
				else if (j >= 80 && j <= 83 && play[3].money <= 0) printf(" ");
				else if (j >= 36 && j <= 39 && play[0].money <= 0) printf(" ");
				else if ((j == 1 && boardCell[(77 - i) / 4].get_player != NULL)) { printcolor(boardCell[(77 - i) / 4].get_player->color); printf("%c", boardpan[i][j]); } // 여기부터 건물 출력. 그 건물의 보유 플레이어의 구조체로 찾아가 색 출력
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
				else if (j >= 36 && j <= 65 && play[2].money > 0)
				{
					if (j == 36 && play[2].location > 9) { printf("%d", play[2].location); } // 위치 출력
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
				else if (j >= 36 && j <= 39 && play[2].money <= 0) printf(" ");
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
	else if (color == BLACK) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);
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
		if (playerHaveBoard->player_board[a] == NULL) continue;
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
	char basebuild[2] = "●";
	char buf[2] = { 0 };



	for (int i = 0; i < playerBuild->haveBoard; i++) // 가지고 있는 건물수 만큼 문자열에 저장.
	{
		if (playerBuild->player_board[i]->build == 1) // 건물 1개 일때 >> Villa 출력
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
		else if (playerBuild->player_board[i]->build == 2) // 건물 1개 일때 >> Villa 출력
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

		else if (playerBuild->player_board[i]->build == 3) // 건물 2개 일때 villa출력
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
		else if (playerBuild->player_board[i]->build == 4) // 3일때 빌딩
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
		else if (playerBuild->player_board[i]->build == 5) // 4일때 호텔
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
	char salary[] = "월급 200k!";
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
		clear(14, 128, 10);
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
	if (d2 == 1) { boardpan[3][122 + u] = buf[0]; boardpan[3][123 + u] = buf[1]; } // 1일때
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

	if (_player->location == 27 && _player->money > 200000) { // 여행
		printPlayer(k);
		printString(10, 128, 18, buf_hangul); // 플레이어 위치 출력
		_itoa(_player->location, buf_location, 10);
		printString(10, 147, 2, buf_location); // 위치 출력
		int target;
		system("cls");
		print_board();
		while (1) {
			printf("원하는 위치를 선택하시오.(이용료 200k) ");
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
				printString(10, 128, 18, buf_hangul); // 플레이어 위치 출력
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
		else if (_player->count >= 3) { // 무인도에서 3번이상 player->count =0으로 초기화
			_player->count = 0;
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
		_itoa(_player->location, buf_location, 10); // 위치 출력해주는거(현재위치를 숫자로)
		printString(10, 147, 2, buf_location);
		Fund(_player);
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
	char prize[] = "보상금 1000k";
	char prize1[] = "보상금 500k";
	char prize2[] = "보상금 300k";
	char prize3[] = "보상금 200k";
	char fine[] = "벌금 200k";
	char fine2[] = "벌금 300k";
	char fine3[] = "벌금 500k";
	char trip[] = "세계여행으로 이동";
	char start[] = "출발지로 이동";
	char goldkey[] = "황금열쇠 칸입니다.";
	char salary[] = "월급 200k!";
	int r = rand() % 10;

	for (int i = 0; i < 17; i++)
	{
		boardpan[11][124 + i] = goldkey[i];
	}
	switch (r) { // 위의 문자열 출력해줌.
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
	printf("땅을 파시겠습니까? y or n\n");
	_kbhit();
	if (Player->money <= 0 && Player->haveBoard <= 0) return 0;
	if (_getch() == 'y')
	{
		while (1)
		{
			printf("팔고 싶은 땅의 번호를 입력하세요(취소: -1) : ");
			int number;
			scanf_s("%d", &number); getchar();
			if (number == -1) break;
			if ((_boardCell + number)->get_player == NULL || (_boardCell + number)->get_player->color != Player->color) continue;
			switch ((_boardCell + number)->build) {
			case 1:
				printf("판매가격은 %dk입니다 정말로 파시겠습니까? y or n\n", (_boardCell + number)->value / 1000);
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
					printf("땅 판매를 완료하였습니다!\n");
					printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
				}
				else printf("판매를 취소하였습니다.\n");

				break;
			case 2:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("판매가격은 100k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("판매가격은 100k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("판매가격은 150k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("판매가격은 200k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				break;
			case 3:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("판매가격은 50k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
					Player->money += 50000;
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("판매가격은 100k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("판매가격은 150k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("판매가격은 200k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				break;
			case 4:
				if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
					printf("판매가격은 150k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					printf("판매가격은 300k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					printf("판매가격은 450k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					printf("판매가격은 600k입니다 정말로 파시겠습니까? y or n\n");
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
						printf("땅 판매를 완료하였습니다!\n");
						printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					}
					else printf("판매를 취소하였습니다.\n");
				}
				break;
			case 5: if ((_boardCell + number)->num > 0 && (_boardCell + number)->num < 9) {
				Player->money += 250000;
			}
				  if ((_boardCell + number)->num > 9 && (_boardCell + number)->num < 18) {
					  printf("판매가격은 500k입니다 정말로 파시겠습니까? y or n\n");
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
						  printf("땅 판매를 완료하였습니다!\n");
						  printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					  }
					  else printf("판매를 취소하였습니다.\n");
				  }
				  if ((_boardCell + number)->num > 18 && (_boardCell + number)->num < 27) {
					  printf("판매가격은 750k입니다 정말로 파시겠습니까? y or n\n");
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
						  printf("땅 판매를 완료하였습니다!\n");
						  printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					  }
					  else printf("판매를 취소하였습니다.\n");
				  }
				  if ((_boardCell + number)->num > 27 && (_boardCell + number)->num < 36) {
					  printf("판매가격은 1000k입니다 정말로 파시겠습니까? y or n\n");
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
						  printf("땅 판매를 완료하였습니다!\n");
						  printf("보유 금액은 %dk입니다.\n", Player->money / 1000);
					  }
					  else printf("판매를 취소하였습니다.\n");
				  }
				  break;

			}
		}
	}
	else printf("판매를 취소하였습니다.\n");
}

void buy(struct board* _boardCell, struct player* Player) {//Player는 현재 차례인 플레이어.
	if ((_boardCell + Player->location)->get_player == NULL && (_boardCell + Player->location)->num != 0 && (_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6
		&& (_boardCell + Player->location)->num != 9 && (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15 && (_boardCell + Player->location)->num != 18
		&& (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25 && (_boardCell + Player->location)->num != 27 && (_boardCell + Player->location)->num != 31
		&& (_boardCell + Player->location)->num != 34) {//_boardCell은 boardCell[0]을 의미함. 거기에 Player->location을 더해줘서 [1],[2],[3],...[35]으로 취급.
		int hit;
		printf("이 땅을 사시겠습니까? y or n\n");
		_kbhit();
		hit = _getch();
		int hit1 = 0;
		if (hit == 'y') {
			if (Player->money < (_boardCell + Player->location)->value) {
				printf("돈이 모자랍니다.\n");
				if (Player->haveBoard >= 1)
				{
					sell(boardCell, Player);
					if (Player->money > (_boardCell + Player->location)->value) { buy(boardCell, Player); }

				}
			}
			else
			{
				printf("이 땅의 가격은 %dk입니다. 정말로 사시겠습니까? y or n\n", (_boardCell + Player->location)->value / 1000);
				_kbhit();
				hit1 = _getch();
				if (hit1 == 'y') {

					printf("땅 구매를 완료하였습니다!\n");
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

	if ((_boardCell + Player->location)->get_player->color == Player->color && (_boardCell + Player->location)->num != 35) {//땅의 소유주인 플레이어와 플레이하는 플레이어의 색깔이 같다면.
		if ((_boardCell + Player->location)->build >= 1 && (_boardCell + Player->location)->build < 4) {//아무것도 안 지어져 있을 때.
			printf("건물을 업그레이드 하시겠습니까? y or n\n");
			_kbhit();
			select = _getch();
		}
	}

	if (select == 'y' && (_boardCell + Player->location)->build != 5) {
		switch ((_boardCell + Player->location)->build) {
		case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("별장의 가격은 50k입니다. 정말로 건설하시겠습니까?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 50000) {
					printf("돈이 모자랍니다.\n");
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
					printf("건물 업그레이드를 완료하였습니다!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 100k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 100000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 150k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 150000) {
						  printf("돈이 모자랍니다.\n");
						  if (Player->haveBoard >= 1)
						  {
							  sell(boardCell, Player);
							  build(boardCell, Player);
						  }
					  }
					  else {
						  (_boardCell + Player->location)->build++;
						  Player->money -= 150000;
						  printf("건물 업그레이드를 완료하였습니다!\n");
						  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("별장의 가격은 200k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 200000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  break;
		case 2:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("별장의 가격은 50k입니다. 정말로 건설하시겠습니까?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 50000) {
					printf("돈이 모자랍니다.\n");
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
					printf("건물 업그레이드를 완료하였습니다!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 100k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 100000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("별장의 가격은 150k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 150000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("별장의 가격은 200k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 200000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  break;
		case 3:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("빌딩의 가격은 150k입니다. 정말로 건설하시겠습니까?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 150000) {
					printf("돈이 모자랍니다.\n");
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
					printf("건물 업그레이드를 완료하였습니다!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("빌딩의 가격은 300k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 300000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("빌딩의 가격은 450k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 450000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("빌딩의 가격은 600k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 600000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  break;
		case 4:if ((_boardCell + Player->location)->num > 0 && _boardCell->num < 9 &&
			(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9번 땅은 황금열쇠라서 제외.
			printf("호텔의 가격은 250k입니다. 정말로 건설하시겠습니까?  y or n\n");
			_kbhit();
			select1 = _getch();
			if (select == 'y') {
				if (Player->money < 250000) {
					printf("돈이 모자랍니다.\n");
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
					printf("건물 업그레이드를 완료하였습니다!\n");
				}
			}
		}
			  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
				  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15번 땅은 황금열쇠라서 제외.
				  printf("호텔의 가격은 500k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 500000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
				  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25번 땅은 황금열쇠라서 제외.
				  printf("호텔의 가격은 750k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 750000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 35 &&
				  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14번 땅은  각각 황금열쇠, 기부라서 제외.
				  printf("호텔의 가격은 1000k입니다. 정말로 건설하시겠습니까?  y or n\n");
				  _kbhit();
				  select1 = _getch();
				  if (select == 'y') {
					  if (Player->money < 1000000) {
						  printf("돈이 모자랍니다.\n");
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
						  printf("건물 업그레이드를 완료하였습니다!\n");
					  }
				  }
			  }
			  break;
		}
	}
}

void Pass(struct board* _boardCell, struct player* Player) {

	if ((_boardCell + Player->location)->pass_value > Player->money) {
		printf("돈이 부족합니다.\n");
		if (Player->haveBoard >= 1)
		{
			sell(boardCell, Player); Pass(_boardCell, Player);
		}
		else if (Player->haveBoard <= 0)
		{
			printf("통행료 지불! -%dk\n", (_boardCell + Player->location)->pass_value / 1000);
			Player->money -= (_boardCell + Player->location)->pass_value;
			(_boardCell + Player->location)->get_player->money += (_boardCell + Player->location)->pass_value;
		}
	}
	if ((_boardCell + Player->location)->pass_value < Player->money)
	{
		printf("통행료 지불! -%dk\n", (_boardCell + Player->location)->pass_value / 1000);

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
	char put[] = "k 지급";
	char funding[] = "200k 투자";
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