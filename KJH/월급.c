#include <stdio.h>
//예시이므로 임의로 수정가능함.
struct player {
	int money;
	int location;
};

void paycheck ( struct player* Player) {
	if (Player->location == 0) {//위치를 이동할 때 반복문을 써서 ++로 1씩 이동하면서 이 함수도 반복문에 넣어 위치를 확인하고 월급을 주는 방식으로 사용바람.
		Player->money +=20;//pay는 월급. 월급을 구체적으로 얼마를 줄 것인지 정한 후 수정할 계획.
	}
}

int main() {

}