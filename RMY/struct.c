#include <stdio.h>

struct board {
	char name[16];
	int num;
	int build;
	int value;
	int pass_value;
	int sell_value;
	struct player* get_player;
};

struct player {
	int color;
	int money;
	int location;
	struct board* player_board[20];
};

int main(void) {
	struct board boardCell[36] = {
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
}