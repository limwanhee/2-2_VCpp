#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
using namespace std;

int main() {
	char input;

	printf("      202207016\n");
	printf("        �ӿ���\n");
	printf("      Application\n");

	while (1) {
		printf("p, f, j�߿� �Է��ϼ���\n");
		input = _getch();

		if (input == 112) {
			printf("���� ������ �̳� ���ϴ� �л��̴�\n");
			printf("\n");
		}
		else if (input == 102) {
			printf("���� ������ �ʹ� ��̴�\n");
			printf("\n");
		}
		else if (input == 106) {
			printf("������ ���� �� ���ּ���\n");
			printf("\n");
		}
		else if (input == 27) {
			break;
		}
	}
}