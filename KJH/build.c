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
	printf("� ���� �Ľðڽ��ϱ�? ���� ��ȣ�� �Է��ϼ��� : ");
	int number;
	scanf_s("%d", &number);
	Player->money+=(_boardCell + number)->sell_value;
	(_boardCell + number)->get_player->color = 0;
	printf("���� ���� �� %d��", Player->money);
}

void buy(struct board* _boardCell, struct player* Player) {//Player�� ���� ������ �÷��̾�.
	if ((_boardCell + Player->location)->get_player->color == 0) {//_boardCell�� boardCell[0]�� �ǹ���. �ű⿡ Player->location�� �����༭ [1],[2],[3],...[35]���� ���.
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
					
				}
			}
		}
	}
}

void build(struct board* _boardCell, struct player* Player) {
	int select=0;
	if ((_boardCell + Player->location)->get_player->color == Player->color) {//���� �������� �÷��̾�� �÷����ϴ� �÷��̾��� ������ ���ٸ�.
		if ((_boardCell + Player->location)->build == 0) {//�ƹ��͵� �� ������ ���� ��.
			printf("�Ǽ��Ͻðڽ��ϱ�? (0��) ��ŵ (1��) ��");
			scanf_s("%d", &select);
		}
		}
		if ((_boardCell + Player->location)->build == 4) {//�� �������� ��.
			printf("���� �Ǽ��� �� �����ϴ�.");
		}
		if (select==1 && (_boardCell + Player->location)->build != 4) {
			switch ((_boardCell+Player->location)->build) {
			case 0:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
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
						//����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
						  }
					  }
				  }
				  break;
			case 1:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 &&
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
						//����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
						  }
					  }
				  }
				  break;
			case 2:if ((_boardCell + Player->location)->num > 0 && (_boardCell + Player->location)->num < 9 && 
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
						//����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
						  }
					  }
				  }
				  break;
			case 3:if ((_boardCell + Player->location)->num > 0 && _boardCell->num < 9 && 
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
						//����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
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
							  //����������Ʈ�߰�����.
						  }
					  }
				  }
				  if ((_boardCell + Player->location)->num > 27 && (_boardCell + Player->location)->num < 36 && 
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
							  //����������Ʈ�߰�����.
						  }
					  }
				  }
				  break;
			}
		}
	}
