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
			printf("q, w, e, r�߿� �Է��ϼ���\n");
			input = _getch();

			if (input == 113) {
				printf("���� ������ �̳� ���ϴ� �л��̴�\n");
				printf("\n");
			}
			else if (input == 119) {
				printf("���� ������ �ʹ� ��̴�\n");
				printf("\n");
			}
			else if (input == 101) {
				printf("������ ���� �� ���ּ���\n");
				printf("\n");
			}

			else if (input == 114) {
				printf("������ ���� �� ���ּ���\n");
				printf("\n");
			}

			else if (input == 27) {
				break;
			}
		}
	}
}