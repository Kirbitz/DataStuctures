#ifndef Stack_H
#define Stack_H

#include "Stack.h";
#include <iostream>

using namespace std;

//Initializes the stack class
template <class T>
Stack<T>::Stack() {
	top = -1;
	stackArray = new T[CAPACITY];
}

//Deletes the pointer array to prevent memory leak
template <class T>
Stack<T>::~Stack() {
	delete[] stackArray;
}

//Adds an element to the end of the stack
template <class T>
void Stack<T>::push_back(T elem) {
	//Checks to see if the stack needs to be expanded for more elements
	if (top < CAPACITY - 1) {
		top++;
		stackArray[top] = elem;
	}
	else {
		int newCAPACITY = CAPACITY + CAPACITY * 4;
		//Makes sure the stack expands properly
		if (expand(newCAPACITY)) {
			top++;
			stackArray[top] = elem;
		}
		else {
			cout << "Error with expansion!\n";
		}
	}
}

//Removes the last element added to the stack
template <class T>
void Stack<T>::pop_off() {
	//Makes sure the stack is not empty
	if (!empty()) {
		top--;
		//Checks to see if the stack can be shrunk down
		if (top + 1 < CAPACITY / 2 && top + 1 > 10) {
			int newCapacity = CAPACITY - CAPACITY / 4;
			//Makes sure the stack shrinks properly
			if (!shrink(newCapacity))
				cout << "Error with shrinking!\n";
		}
	}
	else {
		cout << "Stack Underflow error!\n";
	}
}

//Grabs the top element from the stack
template <class T>
T Stack<T>::atTop() {
	//Checks to make sure the stack is not empty
	if (!empty()) {
		return stackArray[top];
	}
	else {
		cout << "Stack is currently empty!\n";
	}
}

//Expands the stack by 25%
template <class T>
bool Stack<T>::expand(int newCapacity) {
	//Checks the expansion is bigger then the orginal capacity
	if (newCapacity > CAPACITY) {
		CAPACITY = newCapacity;
		T* tempStack = new T[CAPACITY];

		for (int i = 0; i <= top; i++){
			tempStack[i] = stackArray[i];
		}
		delete[] stackArray;
		stackArray = tempStack;

		return true;
	}
	return false;
}

//Shrinks the stack by 25%
template <class T>
bool Stack<T>::shrink(int newCapacity) {
	//Checks the reductions is less than the original capacity
	if (newCapacity < CAPACITY) {
		CAPACITY = newCapacity;
		T* tempStack = new T[CAPACITY];

		for (int i = 0; i <= top; i++) {
			tempStack[i] = stackArray[i];
		}
		delete[] stackArray;
		stackArray = tempStack;

		return true;
	}
	return false;
}

#endif // !Stack_H