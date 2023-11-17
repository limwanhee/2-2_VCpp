#include "y_stack.h"
#include <iostream>

void stack::push(int input) { // 스택에서 값을 넣을 변수
    node* new_node = new node(input); //push 함수를 쓰면서 매개변수를 받아서 받은 값을 data변수에 넣고 새로운 노드를 만든다
    new_node->prev_node = top; //prev_node 변수에 top변수에 들어가 있는 상위 노드의 값을 넣어 다음 노드로 연결 할 수 있게 한다
    top = new_node;  //다음 노드에게는 지금 노드가 상위 노드이기에 top 변수명에 지금 노드 위치 저장
}

int stack::pop() { //스택에서 값을 뺄 변수
    if (top == nullptr) { //스택에서 값을 뺄려고 할 때 값이 비어있으면
        std::cerr << "오류: 스택이 비어있습니다\n"; // 오류 메세지 출력
        return -1; //여기서 더 기능을 추가 할려면 변경 해도 됨
    }

    int popped_value = top->data; //노드에 저장한 값은 top 노드에 data 변수에 있기에 꺼낸 값을 저장
    node* temp = top; //temp 노드변수에 top 노드 값을 저장
    top = top->prev_node; //꺼냈으니 다음 노드의 주소를 지금 top으로 바꿔준다
    delete temp; //temp 노드 변수에 저장했던거 삭제하기
    return popped_value; //pop 함수는 스택에 값을 빼기 위해 있는 함수기에 리턴 값을 위에서 노드의 저장한 값을 넣은 변수인 popped_value 변수에 넣는다
}
