#include <iostream>
#include "yuhan_stack.h"

using namespace std;
y_stack stack;

int main() {
	stack.push(5); // 스택에 5를 넣고
	stack.push(1); // 스택에 1을 넣는다


	cout << "꺼낸 값 : " << stack.pop() << endl; 
	cout << "꺼낸 값 : " << stack.pop() << endl;



	//https://www.techiedelight.com/ko/stack-implementation-in-cpp/
}