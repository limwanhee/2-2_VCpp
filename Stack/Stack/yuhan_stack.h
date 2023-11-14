#include <iostream>

using namespace std;

class y_stack
{
public:
	int arr[10];
	int i = 0;

	y_stack();
	~y_stack();

	void push(int num) { // �� �ִ� �Լ�
		for (i = 0; i < sizeof(arr) / 4; i++) { // �迭 ũ�� ��ŭ�� �ݺ����� ������ sizeof(arr) = int = 4����Ʈ�� 10�� = 40 �׷��� /4 �� ���༭ �ε��� ���̸� ���ư��� ����
			if (arr[i] == NULL) { // �迭�� i��° ���� ����ִٸ� 
				arr[i] = num; // �迭�� i��°�� ���� �ִ´�
				break; // ���� �־����� �ݺ��� ���������� ����
			}
		}
	}

	int pop() { // �� ���� �Լ�
		for (i = sizeof(arr) / 4 - 1; i >= 0; i--) { // 4 - 1�� �ݺ��� �Ųٷ� ������ 9���� 0���� ���� �ؾ��ϱ⿡ -1�� ����
			if (arr[i] != NULL) { // �迭�� i��° ���� NULL�� �ƴϸ�
				int poppedValue = arr[i]; // ��ȯ�� ���� poppedValue�� �ְ� (������ NULL�� �ʱ�ȭ �� return���� �̾������ϴµ� return���� ���� ������ �ݺ����� �������ͼ� �̷� ������� ��)
				arr[i] = NULL;  // �迭�� i��° �ڸ� ���� NULL�� �ʱ�ȭ �� (pop�� ���޾� 2�� ���� �� �ݺ��� �ȿ� ���ǹ��� �����ϱ� ���� ���ÿ� ����� ���� NULL�� �ʱ�ȭ �Ѵ�  )
				return poppedValue; // �Ʊ� ���� �� ���� ��ȯ���ش�
			}
		}
	}
};
y_stack::y_stack() {

}

y_stack::~y_stack() {

}
