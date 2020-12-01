#include <stdio.h>

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
	int haveBoard;
	int color;
	int money;
	int location;
	int count;
	struct board* player_board[20];
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

//0,2,6,9,11,15,18,20,25,27,31,34,35
void sell(struct board* _boardCell, struct player* Player) {
	printf("� ���� �Ľðڽ��ϱ�? ���� ��ȣ�� �Է��ϼ��� : ");
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

void buy(struct board* _boardCell, struct player* Player) {//Player�� ���� ������ �÷��̾�.
	if ((_boardCell + Player->location)->get_player->color == 0 &&(_boardCell+Player->location)!= 0 && (_boardCell + Player->location) != 2 && (_boardCell + Player->location) != 6
		&& (_boardCell + Player->location) != 9 && (_boardCell + Player->location) != 11 && (_boardCell + Player->location) != 15 && (_boardCell + Player->location) != 18
		&& (_boardCell + Player->location) != 20 && (_boardCell + Player->location) != 25 && (_boardCell + Player->location) != 27 && (_boardCell + Player->location) != 31
		&& (_boardCell + Player->location) != 34) {//_boardCell�� boardCell[0]�� �ǹ���. �ű⿡ Player->location�� �����༭ [1],[2],[3],...[35]���� ���.
		printf("�� ���� ��ðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
		int select;
		scanf_s("%d", &select);
		if (select == 0) {
			printf("�� ���� ������ %d���Դϴ�. ������ ��ðڽ��ϱ�? (0��) �� (1��) �ƴϿ�", (_boardCell + Player->location)->value);
			scanf_s("%d", &select);
			if (select == 0) {
				if (Player->money < (_boardCell + Player->location)->value) {
					printf("���� ���ڶ��ϴ�.");
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
	if ((_boardCell + Player->location)->get_player->color == Player->color && (_boardCell + Player->location)->num!=35) {//���� �������� �÷��̾�� �÷����ϴ� �÷��̾��� ������ ���ٸ�.
		if ((_boardCell + Player->location)->build == 0) {//�ƹ��͵� �� ������ ���� ��.
			printf("�Ǽ��Ͻðڽ��ϱ�? (0��) ��ŵ (1��) ��");
			scanf_s("%d", &select);
		}
		}
		if ((_boardCell + Player->location)->build == 4) {//�� �������� ��.
			printf("���� �Ǽ��� �� �����ϴ�.");
		}
		if (select==1 && (_boardCell + Player->location)->build != 5) {
			switch ((_boardCell+Player->location)->build) {
			case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
				(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num !=- 6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
				printf("������ ������ 5�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
				scanf_s("%d", &select);
				if (select == 0) {
					if (Player->money < 50000) {
						printf("���� ���ڶ��ϴ�.");
					}
					else {
						(_boardCell + Player->location)->build += 1;
						Player->money -= 50000;
						(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
					}
				}
			}
				  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 && 
					  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 10�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 100000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 100000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 && 
					  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 15�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 150000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  _boardCell->build += 1;
							  Player->money -= 150000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa1;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 && 
					  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
					  printf("������ ������ 20�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 200000) {
							  printf("���� ���ڶ��ϴ�.");
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
				(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != -6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
				printf("������ ������ 5�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
				scanf_s("%d", &select);
				if (select == 0) {
					if (Player->money < 50000) {
						printf("���� ���ڶ��ϴ�.");
					}
					else {
						(_boardCell + Player->location)->build += 1;
						Player->money -= 50000;
						(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
					}
				}
			}
				  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 &&
					  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 10�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 100000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 100000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 &&
					  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 15�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 150000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  _boardCell->build += 1;
							  Player->money -= 150000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_villa2;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 &&
					  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
					  printf("������ ������ 20�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 200000) {
							  printf("���� ���ڶ��ϴ�.");
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
				(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
				printf("������ ������ 15�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
				scanf_s("%d", &select);
				if (select == 0) {
					if (Player->money < 150000) {
						printf("���� ���ڶ��ϴ�.");
					}
					else {
						(_boardCell + Player->location)->build += 1;
						Player->money -= 150000;
						(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
					}
				}
			}
				  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 && 
					  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 30�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 300000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 300000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 && 
					  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
					  printf("������ ������ 45�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 450000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 450000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_building;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 && 
					  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
					  printf("������ ������ 60�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 600000) {
							  printf("���� ���ڶ��ϴ�.");
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
				(_boardCell + Player->location)->num != 2 && (_boardCell + Player->location)->num != 6) {//2,6,9�� ���� Ȳ�ݿ���� ����.
				printf("ȣ���� ������ 25�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
				scanf_s("%d", &select);
				if (select == 0) {
					if (Player->money < 250000) {
						printf("���� ���ڶ��ϴ�.");
					}
					else {
						(_boardCell + Player->location)->build += 1;
						Player->money -= 250000;
						(_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
					}
				}
			}
				  if ((_boardCell + Player->location)->num > 9 && (_boardCell + Player->location)->num < 18 && 
					  (_boardCell + Player->location)->num != 11 && (_boardCell + Player->location)->num != 15) {//11,15�� ���� Ȳ�ݿ���� ����.
					  printf("ȣ���� ������ 50�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 500000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 500000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel; .
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 18 && (_boardCell + Player->location)->num < 27 && 
					  (_boardCell + Player->location)->num != 20 && (_boardCell + Player->location)->num != 25) {//20,25�� ���� Ȳ�ݿ���� ����.
					  printf("ȣ���� ������ 75�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 750000) {
							  printf("���� ���ڶ��ϴ�.");
						  }
						  else {
							  (_boardCell + Player->location)->build += 1;
							  Player->money -= 750000;
							  (_boardCell + Player->location)->pass_value = (_boardCell + Player->location)->pass_hotel;
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 35 && 
					  (_boardCell + Player->location)->num != 31 && (_boardCell + Player->location)->num != 34) {//31,14�� ����  ���� Ȳ�ݿ���, ��ζ� ����.
					  printf("ȣ���� ������ 100�����Դϴ�. ������ �Ǽ��Ͻðڽ��ϱ�? (0��) �� (1��) �ƴϿ�");
					  scanf_s("%d", &select);
					  if (select == 0) {
						  if (Player->money < 1000000) {
							  printf("���� ���ڶ��ϴ�.");
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
