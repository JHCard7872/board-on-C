#include <stdio.h>

struct board1 {
	char name[16];
	int num;
	int build;
	int value;
	int pass_value;
	int player;
	int sell_value;
	struct board* get_player;
};

void print_board(void);

int main(void) {

	//y축 21칸 x축 81칸
	 print_board();
	 // 나중에 플레이어 위치, 땅값 구현할것.
}

void print_board(void) {
	char boardpan[21][130] = {
	"┏   18  ┳   19  ┳   20  ┳   21  ┳   22  ┳   23  ┳   24  ┳   25  ┳   26  ┳   27  ┓",
	"┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃",
	"┠   17  ╋   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ╋   28  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   16  ┫                                                               ┠   29  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   15  ┫                                                               ┠   30  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   14  ┫                                                               ┠   31  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   13  ┫                                                               ┠   32  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   12  ┫                                                               ┠   33  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   11  ┫                                                               ┠   34  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   10  ┫                                                               ┠   35  ┫",
	"┃       ┃                                                               ┃       ┃",
	"┠   9   ╋   8   ┳   7   ┳   6   ┳   5   ┳   4   ┳   3   ┳   2   ┳   1   ╋   0   ┫",
	"┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃",
	"┗   ─   ┸   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┛"
	};
	for (int i = 0; i < 21; i++)
	{
		printf("%s\n", boardpan[i]);
	} // 음.........어렵다.......... printf로 하는게 맞겠지? 문자열로 하니깐 중간에 말을 못넣겠네 내일한다.
}