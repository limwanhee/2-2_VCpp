#include <iostream>
#include "yuhan_stack.h"

using namespace std;
y_stack stack = y_stack();


int main() {
	stack.push(43);

	cout << stack.pop() << endl;

	//https://www.techiedelight.com/ko/stack-implementation-in-cpp/
}