#include <stdio.h>
//�����̹Ƿ� ���Ƿ� ����������.
struct player {
	int money;
	int location;
};

void paycheck ( struct player* Player) {
	if (Player->location == 0) {//��ġ�� �̵��� �� �ݺ����� �Ἥ ++�� 1�� �̵��ϸ鼭 �� �Լ��� �ݺ����� �־� ��ġ�� Ȯ���ϰ� ������ �ִ� ������� ���ٶ�.
		Player->money +=20;//pay�� ����. ������ ��ü������ �󸶸� �� ������ ���� �� ������ ��ȹ.
	}
}

int main() {

}