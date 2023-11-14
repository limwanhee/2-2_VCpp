#pragma once

class y_stack
{
public:
	y_stack();
	~y_stack();

	void push(int num);
	int pop();

private:
	int* data;
};