#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

int main() {
	
	

	printf("    임완희의 행복한 VC++\n");


	while (1) {
		printf("command>");
		char tmp1, tmp2;

		while ((tmp1 = _getche()) != '\r')
		{
			tmp2 = tmp1;
		}

		switch (tmp2) {
			case 'q':
				printf("\nqwer 화이팅\n");
				break;

			case 'w':
				printf("\n과제 너무 좋다\n");
				break;

			case 'e':
				printf("\n담주부터 과제량 3배다\n");
				break;

			case 'r':
				printf("\n행복합니다\n");
				break;

			default:
				printf("\n다른 영어를 입력해주세요\n");
				break;
		}
	}
}