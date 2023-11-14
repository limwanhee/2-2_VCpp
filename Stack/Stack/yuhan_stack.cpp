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

	void push(int num) { // 값 넣는 함수
		for ( i = 0; i < sizeof(arr); i++){ // 배열 크기 만큼의 반복문을 돌린다
			if (arr[i] == NULL) { // 배열의 i번째 값이 비어있다면 
				arr[i] = num; // 배열의 i번째에 값을 넣는다
				break; // 값을 넣었으면 반복문 빠져나오게 만듦
			}
		}
	}
		
	int pop() {
		for ( i = sizeof(arr);  i < 0; i++){ //배열 최대 크기(i)부터 시작해서 0번 인덱스까지 반복을 돌린다
			if (arr[i] != NULL) { //배열의 i번째 값이 비어있지 않다면
				return arr[i]; //배열의 i번째 값을 꺼낸다
			}
		}	
	}

private:
	int* data;
};

