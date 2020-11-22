/*C프로그래밍2 4분반
 2020136082 오준혁.
 실습 1-3
 이진수 변환*/
수정해봤는데 보입니까?
#include <stdio.h>

int main(void) {

	/*num[31]로 31개 만큼 배열로 변수를 만들어줬다.
	정수를 입력받을 변수 number를 선언했다.*/
	int num[31];
	int number;

	printf("정수를 입력하시오: ");
	scanf_s("%d", &number);

	if (number < 0) // 입력받은 정수가 음수일때 2진수의 앞부분은 1로 해주고 양수로 바꿔주었다.
	{
		number = -number;
		printf("1");
	}
	else // 입력받은 정수가 음수가 아닐때 앞부분은 0으로 출력해주었다.
	{
		printf("0");
	}

	for (int i = 0; i < 31; i++) // int는 총 32비트이기 때문에 맨 앞의 부호부분을 제외한 31비트를 사용할것이기 때문에 31만큼 반복해주었다.
	{
		num[i] = number % 2; // num0, num1, num2, ... 에 number에 2를 나눈 나머지 값을 저장해준다.
		number = number / 2; // 한번 나머지를 구하면 2로 나눈값에 다시 2를 나눈 나머지 값을 구해야 하므로 계속 2로 나누어 준다.
	}

	for (int j = 30; j >= 0; j--) // 2를 나눈 나머지 값을 거꾸로 출력해줘야 하므로 num[0]~num[30]순으로 출력해주었다.
	{
		printf("%d", num[j]);
	}

	return 0;
}
