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
		printf("�ֻ��� ������");
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
	printf("ù��° �ֻ���: %d ", d1);
	Sleep(1500);
	int d2 = Dice();
	//Sleep(1000);
	printf("�ι�° �ֻ���: %d\n", d2);
	if (d1 == d2) {
		*i += 1;
		printf("���� %d %d %d %d\n",*i, d1 , d2, *player_locate);
		if (*i >= 3) {
			
			*player_locate = 10;
			printf("���ε��� %d\n", *player_locate);

			return 0;
		}
	}
	*player_locate +=  d1 + d2;
	if (*player_locate > 40) {
		*player_locate %=  40;
	}
	printf("���� ��ġ %d\n", *player_locate);
	if (d1 == d2) {
		return 1;
	}
	return 0;
}
