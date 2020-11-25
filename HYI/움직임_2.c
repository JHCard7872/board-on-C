#include <stdio.h>
#include <Windows.h>
#include <time.h>

struct Player {
	int locate;
	int count;
};

int Dice();
int Dice_Move(int* player_locate, int* i);
void Island(int* count);

int main() {
	struct Player player1;
	player1.locate = 1;
	player1.count = 0;
	int k;
	int i;
	while(1) {
		i = 0;
		printf("주사위 굴리기");
		scanf_s("%d", &k);
		if (Dice_Move(&player1.locate, &i)) {
			if (Dice_Move(&player1.locate, &i)) {
				if (Dice_Move(&player1.locate, &i)) {

				}
			}
		}
	}

}
int Dice() {
	srand(time(NULL));

	int k = rand() % 6 + 1;

	return k;
}
int Dice_Move(struct Player* player, int* i) {
	Sleep(1500);
	int d1 = Dice();
	Sleep(1500);
	int d2 = Dice();
	//Sleep(1500);
	if (player->locate == 10) {
		player->count++;
		printf("무인도 %d번째 주사위\n", player->count);
		if (player->count < 3) {
			printf("첫번째 주사위: %d ", d1);
			printf("두번째 주사위: %d\n", d2);
			if (d1 == d2) {
				player->locate += d1 + d2;
				player->count = 0;
				printf("현재 위치 %d\n", player->locate);
			}
			return 0;
		}
		else if (player->count >= 3) {
			player->count = 0;
		}
	}
	printf("첫번째 주사위: %d ", d1);
	printf("두번째 주사위: %d\n", d2);
	if (d1 == d2) {
		*i += 1;
		//printf("더블 %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) {
			
			player->locate = 10;
			printf("무인도행 %d\n", player->locate);

			return 0;
		}
	}
	player->locate +=  d1 + d2;
	if (player->locate > 36) {
		player->locate %= 36;
	}
	printf("현재 위치 %d\n", player->locate);
	if (d1 == d2) {
		return 1;
	}
	return 0;
}
void Island(int* count) {
	*count += 1;

}