#include <iostream>
#include "yuhan_stack.h"

using namespace std;
y_stack stack;

int main() {
	stack.push(5); // ���ÿ� 5�� �ְ�
	stack.push(1); // ���ÿ� 1�� �ִ´�


	cout << "���� �� : " << stack.pop() << endl; 
	cout << "���� �� : " << stack.pop() << endl;



	//https://www.techiedelight.com/ko/stack-implementation-in-cpp/
}