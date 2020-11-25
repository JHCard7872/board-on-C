#include <stdio.h>
#include <Windows.h>
#include <time.h>


int Dice();
int Dice_Move(int* player_locate, int i);

int main() {
	int player1 = 1;
	int k;
	int i;
	while(1) {
		i = 0;
		printf("주사위 굴리기");
		scanf_s("%d", &k);
		if (Dice_Move(&player1, &i)) {
			if (Dice_Move(&player1, &i)) {
				if (Dice_Move(&player1, &i)) {

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
int Dice_Move(int* player_locate, int* i) {
	int d1 = Dice();
	printf("첫번째 주사위: %d ", d1);
	Sleep(1500);
	int d2 = Dice();
	//Sleep(1000);
	printf("두번째 주사위: %d\n", d2);
	if (d1 == d2) {
		*i += 1;
		printf("더블 %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) {
			
			*player_locate = 10;
			printf("무인도행 %d\n", *player_locate);

			return 0;
		}
	}
	*player_locate +=  d1 + d2;
	if (*player_locate > 40) {
		*player_locate %=  40;
	}
	printf("현재 위치 %d\n", *player_locate);
	if (d1 == d2) {
		return 1;
	}
	return 0;
}
