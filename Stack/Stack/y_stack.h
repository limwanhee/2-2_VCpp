#ifndef Y_STACK_H
#define Y_STACK_H

class node {
public:
    int data; //노드에는 데이터와
    node* prev_node; //다음으로 갈 노드의 주소 값을 가지고 있다 스택의 FILO 구조로 변수 명은 전 노드를 가리킨다는 변수명

    // 노드를 초기화하는 생성자
    node(int value) : data(value), prev_node(nullptr) {}
};

class stack {
private:
    node* top;

public:
    // 빈 스택을 초기화하는 생성자
    stack() : top(nullptr) {}

    // 필요한 경우 메모리 할당을 해제하는 소멸자
    ~stack() {
        while (top != nullptr) {
            pop();
        }
    }

    // 스택에 값을 넣는 함수
    void push(int input);

    // 스택에서 값을 꺼내는 함수
    int pop();
};

#endif // Y_STACK_H

