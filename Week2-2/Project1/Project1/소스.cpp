#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	char input[5];

	printf("    임완희의 행복한 VC++\n");


	while (1) {
		printf("command>");
		gets_s(input);

		if (strcmp(input, "q") == 0) {
			printf("qwer화이팅\n");
			printf("\n");
		}
		else if (strcmp(input, "w") == 0) {
			printf("과제 너무 좋다\n");
			printf("\n");
		}
		else if (strcmp(input, "e") == 0) {
			printf("담주부턴 과제량 3배다?\n");
			printf("\n");
		}
		else if (strcmp(input, "r") == 0) {
			printf("행복합니다...\n");
			printf("\n");
		}
		/*
		else if (input[0] == 27) {
			break; 
		}
		미구현... 1시간동안 찾아봤는데 몰르겠어요...
		*/
		else {
			printf("qwer중 입력해주세요");
		}
	}
}