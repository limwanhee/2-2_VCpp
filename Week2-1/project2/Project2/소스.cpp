#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
using namespace std;

int main() {
	char input;

	printf("      202207016\n");
	printf("        임완희\n");
	printf("      Application\n");

	while (1) {
		printf("p, f, j중에 입력하세요\n");
		input = _getch();

		if (input == 112) {
			printf("나는 과제를 겁나 잘하는 학생이다\n");
			printf("\n");
		}
		else if (input == 102) {
			printf("나는 과제가 너무 즐겁다\n");
			printf("\n");
		}
		else if (input == 106) {
			printf("교수님 과제 더 내주세요\n");
			printf("\n");
		}
		else if (input == 27) {
			break;
		}
	}
}