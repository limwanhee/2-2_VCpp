#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	char input[5];

	printf("    �ӿ����� �ູ�� VC++\n");


	while (1) {
		printf("command>");
		gets_s(input);

		if (strcmp(input, "q") == 0) {
			printf("qwerȭ����\n");
			printf("\n");
		}
		else if (strcmp(input, "w") == 0) {
			printf("���� �ʹ� ����\n");
			printf("\n");
		}
		else if (strcmp(input, "e") == 0) {
			printf("���ֺ��� ������ 3���?\n");
			printf("\n");
		}
		else if (strcmp(input, "r") == 0) {
			printf("�ູ�մϴ�...\n");
			printf("\n");
		}
		/*
		else if (input[0] == 27) {
			break; 
		}
		�̱���... 1�ð����� ã�ƺôµ� �����ھ��...
		*/
		else {
			printf("qwer�� �Է����ּ���");
		}
	}
}