#ifndef Y_STACK_H
#define Y_STACK_H

class node {
public:
    int data; //��忡�� �����Ϳ�
    node* prev_node; //�������� �� ����� �ּ� ���� ������ �ִ� ������ FILO ������ ���� ���� �� ��带 ����Ų�ٴ� ������

    // ��带 �ʱ�ȭ�ϴ� ������
    node(int value) : data(value), prev_node(nullptr) {}
};

class stack {
private:
    node* top;

public:
    // �� ������ �ʱ�ȭ�ϴ� ������
    stack() : top(nullptr) {}

    // �ʿ��� ��� �޸� �Ҵ��� �����ϴ� �Ҹ���
    ~stack() {
        while (top != nullptr) {
            pop();
        }
    }

    // ���ÿ� ���� �ִ� �Լ�
    void push(int input);

    // ���ÿ��� ���� ������ �Լ�
    int pop();
};

#endif // Y_STACK_H

