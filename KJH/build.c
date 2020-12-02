#include <stdio.h>

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
	int haveBoard;
	int color;
	int money;
	int location;
	int count;
	struct board* player_board[20];
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

//0,2,6,9,11,15,18,20,25,27,31,34,35
void sell(struct board* _boardCell, struct player* Player) {
	printf("어떤 땅을 파시겠습니까? 땅의 번호를 입력하세요 : ");
	int number;
	scanf_s("%d", &number);
	switch ((_boardCell + number)->build) {
	case 1: Player->money += (_boardCell + number)->value;
		break;
	case 2: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 50000;
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
	}
	case 4: if (_boardCell + number)->num > 0 && _boardCell + number)->num < 9) {
	Player->money += 150000;
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
	(_boardCell + number)->get_player->color = 0;
	Player->haveboard--;
}

void buy(struct board* _boardCell, struct player* Player) {//Player는 현재 차례인 플레이어.
	if ((_boardCell + Player->location)->get_player->color == 0 &&(_boardCell+Player->location)!= 0 && (_boardCell + Player->location) != 2 && (_boardCell + Player->location) != 6
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
	int select=0;
	if ((_boardCell + Player->location)->get_player->color == Player->color && (_boardCell + Player->location)->num!=35) {//땅의 소유주인 플레이어와 플레이하는 플레이어의 색깔이 같다면.
		if ((_boardCell + Player->location)->build == 0) {//아무것도 안 지어져 있을 때.
			printf("건설하시겠습니까? (0번) 스킵 (1번) 예");
			scanf_s("%d", &select);
		}
		}
		if ((_boardCell + Player->location)->build == 4) {//다 지어졌을 때.
			printf("더는 건설할 수 없습니다.");
		}
		if (select==1 && (_boardCell + Player->location)->build != 5) {
			switch ((_boardCell+Player->location)->build) {
			case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
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
