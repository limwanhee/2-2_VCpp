#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

int main() {
	
	

	printf("    �ӿ����� �ູ�� VC++\n");


	while (1) {
		printf("command>");
		char tmp1, tmp2;

		while ((tmp1 = _getche()) != '\r')
		{
			tmp2 = tmp1;
		}

		switch (tmp2) {
			case 'q':
				printf("\nqwer ȭ����\n");
				break;

			case 'w':
				printf("\n���� �ʹ� ����\n");
				break;

			case 'e':
				printf("\n���ֺ��� ������ 3���\n");
				break;

			case 'r':
				printf("\n�ູ�մϴ�\n");
				break;

			default:
				printf("\n�ٸ� ��� �Է����ּ���\n");
				break;
		}
	}
}