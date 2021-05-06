#pragma once
#ifndef STACK_H
#define STACK_H

template <class T>
class Stack {
public:
	Stack();
	~Stack();
	void push_back(T elem);
	void pop_off();
	T atTop();
	bool empty() { return top == -1; }
	int getCAPACITY() { return CAPACITY; }

private:
	int CAPACITY = 10;
	int top;
	T* stackArray;
	bool expand(int);
	bool shrink(int);
};

#include "Stack.cpp";

#endif