#include <iostream>
#include "yuhan_stack.h"

using namespace std;

class y_stack
{
public:
	int arr[30] = { NULL };
	int i;

	y_stack();
	~y_stack();

	void push(int num) { // �� �ִ� �Լ�
		for ( i = 0; i < sizeof(arr); i++){ // �迭 ũ�� ��ŭ�� �ݺ����� ������
			if (arr[i] == NULL) { // �迭�� i��° ���� ����ִٸ� 
				arr[i] = num; // �迭�� i��°�� ���� �ִ´�
				break; // ���� �־����� �ݺ��� ���������� ����
			}
		}
	}
		
	int pop() {
		for ( i = sizeof(arr);  i < 0; i++){ //�迭 �ִ� ũ��(i)���� �����ؼ� 0�� �ε������� �ݺ��� ������
			if (arr[i] != NULL) { //�迭�� i��° ���� ������� �ʴٸ�
				return arr[i]; //�迭�� i��° ���� ������
			}
		}	
	}

private:
	int* data;
};

