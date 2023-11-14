#include <iostream>

using namespace std;

class y_stack
{
public:
	int arr[10];
	int i = 0;

	y_stack();
	~y_stack();

	void push(int num) { // 값 넣는 함수
		for (i = 0; i < sizeof(arr) / 4; i++) { // 배열 크기 만큼의 반복문을 돌린다 sizeof(arr) = int = 4바이트가 10개 = 40 그래서 /4 를 해줘서 인덱스 길이만 돌아가게 해줌
			if (arr[i] == NULL) { // 배열의 i번째 값이 비어있다면 
				arr[i] = num; // 배열의 i번째에 값을 넣는다
				break; // 값을 넣었으면 반복문 빠져나오게 만듦
			}
		}
	}

	int pop() { // 값 빼는 함수
		for (i = sizeof(arr) / 4 - 1; i >= 0; i--) { // 4 - 1은 반복을 거꾸로 돌리면 9부터 0까지 돌게 해야하기에 -1을 해줌
			if (arr[i] != NULL) { // 배열의 i번째 값이 NULL이 아니면
				int poppedValue = arr[i]; // 반환할 값을 poppedValue에 넣고 (순서가 NULL로 초기화 후 return으로 이어져야하는데 return문이 먼저 나오면 반복문을 빠져나와서 이런 방식으로 함)
				arr[i] = NULL;  // 배열의 i번째 자리 값을 NULL로 초기화 후 (pop을 연달아 2번 했을 때 반복문 안에 조건문을 만족하기 위해 스택에 저장된 값을 NULL로 초기화 한다  )
				return poppedValue; // 아까 따로 뺀 값을 반환해준다
			}
		}
	}
};
y_stack::y_stack() {

}

y_stack::~y_stack() {

}
