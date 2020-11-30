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
	int haveboard;
	int color;
	int money;
	int location;
	struct board* player_board[20];
};

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


void sell(struct board* _boardCell, struct player* Player) {
	printf("어떤 땅을 파시겠습니까? 땅의 번호를 입력하세요 : ");
	int number;
	scanf_s("%d", &number);
	Player->money+=(_boardCell + number)->sell_value;
	(_boardCell + number)->get_player->color = 0;
	printf("현재 가진 돈 %d원", Player->money);
}

void buy(struct board* _boardCell, struct player* Player) {//Player는 현재 차례인 플레이어.
	if ((_boardCell + Player->location)->get_player->color == 0) {//_boardCell은 boardCell[0]을 의미함. 거기에 Player->location을 더해줘서 [1],[2],[3],...[35]으로 취급.
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
					
				}
			}
		}
	}
}

void build(struct board* _boardCell, struct player* Player) {
	int select=0;
	if ((_boardCell + Player->location)->get_player->color == Player->color) {//땅의 소유주인 플레이어와 플레이하는 플레이어의 색깔이 같다면.
		if ((_boardCell + Player->location)->build == 0) {//아무것도 안 지어져 있을 때.
			printf("건설하시겠습니까? (0번) 스킵 (1번) 예");
			scanf_s("%d", &select);
		}
		}
		if ((_boardCell + Player->location)->build == 4) {//다 지어졌을 때.
			printf("더는 건설할 수 없습니다.");
		}
		if (select==1 && (_boardCell + Player->location)->build != 4) {
			switch ((_boardCell+Player->location)->build) {
			case 0:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
				(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num !=- 6) {//2,6,9번 땅은 황금열쇠라서 제외.
				printf("별장의 가격은 5만원입니다. 정말로 건설하시겠습니까? (0번) 예 (1번) 아니요");
				scanf_s("%d", &select);
				if (select == 0) {
					if (Player->money < 50000) {
						printf("돈이 모자랍니다.");
					}
					else {
						(_boardCell + Player->location)->build += 1;
						Player->money -= 50000;
						//통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
						  }
					  }
				  }
				  break;
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
						//통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
						  }
					  }
				  }
				  break;
			case 2:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
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
						//통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
						  }
					  }
				  }
				  break;
			case 3:if ((_boardCell + Player->location)->num > 0 && _boardCell->num < 9 && 
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
						//통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
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
							  //통행료업데이트추가예정.
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 && 
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
							  //통행료업데이트추가예정.
						  }
					  }
				  }
				  break;
			}
		}
	}
