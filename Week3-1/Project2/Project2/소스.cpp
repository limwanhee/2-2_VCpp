#include <iostream>
#include <chrono>
#include <conio.h>
#define SIZE 5

using namespace std;
using namespace chrono;


int main() {
	char key [SIZE];
	int i = 0;

    if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
		system_clock::time_point start = system_clock::now(); // �Է��ϸ� �ð� ���� ����
		for (i = 0; i < SIZE; i++) {
			key[i] = _getch();      // ����Ű �Է½� 224 00�� ������ �Ǳ⿡ �տ� �ִ� �� 224�� ����
			if (key[i] == -32) {    // -32�� �ԷµǸ�
				key[i] = _getch();  // ���� �Է°��� �Ǻ��Ͽ� �����¿� ���
			}
	
			duration<double>sec = system_clock::now() - start; //�Է��ϸ� �ð� ���� ��

			if(key[i] == 27 || key[i] == '\r' || sec.count() > 0.3 || i == 4) { //esc ��������, ����Ű ��������, �Է� �ð��� 0.3�� ��������, �Է��� 5�� �Է� ������ ����
					break; 
			}
		}

		if (key[0] == 80 && key[1] == 77 && key[2] == 'a') { // �Ʒ�, ������, a
			printf("�Ƶ���! =o");
		}
		else if (key[0] == 77 && key[1] == 80 && key[2] == 77) { //������, �Ʒ�, ������
			printf("�·��!");
		}
		else if (key[0] == 80 && key[1] == 1 && key[2] == 75 && key[4] == 'k') { //�Ʒ�, ���ϴ�(1��Ű), ����, k
			printf("��Ǽ�ǳ��!");
		}
		else {
			printf("�߸��� Ŀ�ǵ带 �Է��߽��ϴ�");
		}
		/*
			
		2��° �Է��ϰ� 0.3�ʰ� ������ ���� �Է��� ��ٸ��� �Է��� �Ǵ� ����
		Ŀ�ǵ带 ������ �� �� ���� ����
		("asdf���a" ó�� �̻��� �ܾ ���������� �νĽ�ų��") �� ������ �������� ���� ������ �ֽ��ϴ�

		*/
	}

}
