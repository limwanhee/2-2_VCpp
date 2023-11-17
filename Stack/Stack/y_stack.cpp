#include "y_stack.h"
#include <iostream>

void stack::push(int input) { // ���ÿ��� ���� ���� ����
    node* new_node = new node(input); //push �Լ��� ���鼭 �Ű������� �޾Ƽ� ���� ���� data������ �ְ� ���ο� ��带 �����
    new_node->prev_node = top; //prev_node ������ top������ �� �ִ� ���� ����� ���� �־� ���� ���� ���� �� �� �ְ� �Ѵ�
    top = new_node;  //���� ��忡�Դ� ���� ��尡 ���� ����̱⿡ top ������ ���� ��� ��ġ ����
}

int stack::pop() { //���ÿ��� ���� �� ����
    if (top == nullptr) { //���ÿ��� ���� ������ �� �� ���� ���������
        std::cerr << "����: ������ ����ֽ��ϴ�\n"; // ���� �޼��� ���
        return -1; //���⼭ �� ����� �߰� �ҷ��� ���� �ص� ��
    }

    int popped_value = top->data; //��忡 ������ ���� top ��忡 data ������ �ֱ⿡ ���� ���� ����
    node* temp = top; //temp ��庯���� top ��� ���� ����
    top = top->prev_node; //�������� ���� ����� �ּҸ� ���� top���� �ٲ��ش�
    delete temp; //temp ��� ������ �����ߴ��� �����ϱ�
    return popped_value; //pop �Լ��� ���ÿ� ���� ���� ���� �ִ� �Լ��⿡ ���� ���� ������ ����� ������ ���� ���� ������ popped_value ������ �ִ´�
}
