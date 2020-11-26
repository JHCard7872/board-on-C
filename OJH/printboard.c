#include <stdio.h>
#include <windows.h>

#define WHITE 7
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6

struct board {
	char name[16];
	int num;
	int build;
	int value;
	int pass_value;
	char player;
	int sell_value;
	struct board* get_player;
};

void print_board(void);
void printcolor(int color);

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
	"┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃ ountry┃ ountry┃",
	"┗   ─   ┸   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┻   ─   ┛"
	};
	for (int i = 0; i < 20; i = i + 2)
	{
		printf("%s\n", boardpan[i]);
		if (i == 0)
		{
			for (int j = 0; j < 10; j++)
			{
				printf("   "); printcolor(BLUE); printf("%c", '*'); printcolor(RED); printf("%c", '*'); printcolor(GREEN); printf("%c", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
			}
			
		}
		else if (i > 0 && i < 18)
		{
			printf("   "); printcolor(BLUE); printf("%c", '*'); printcolor(RED); printf("%c", '*'); printcolor(GREEN); printf("%c", '*'); printcolor(YELLOW); printf("%c", '*'); printcolor(WHITE);
			printf("                                                                 ");
			printf("   "); printcolor(BLUE); printf("%c", '*'); printcolor(RED); printf("%c", '*'); printcolor(GREEN); printf("%c", '*'); printcolor(YELLOW); printf("%c", '*'); printcolor(WHITE);
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				printf("   "); printcolor(BLUE); printf("%c", '*'); printcolor(RED); printf("%c", '*'); printcolor(GREEN); printf("%c", '*'); printcolor(YELLOW); printf("%c ", '*'); printcolor(WHITE);
			}
		}
		printf("\n");
		printf("%s\n", boardpan[i + 1]);
		printf("            \n");
	}
	printf("%s\n", boardpan[20]);

}

void printcolor(int color) {
	if (color == WHITE)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else if (color == BLUE)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	}
	else if (color == GREEN)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	}
	else if (color == RED)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	}
	else if (color == YELLOW)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	}
}