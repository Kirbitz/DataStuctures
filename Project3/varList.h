// variable size array class declaration
// Assignment 3.  Dr. Alnaeli
//credit to Professor Nesterenko, KSU.
//varArray.h
//This file expected to be used in parts 1 and 2.
//Plase try not to change this interface.
//please notice the template file inclusion. "implementation.template"

#ifndef VARLIST_H
#define VARLIST_H
template <class T>
class VarList {
public:
	VarList(); // void constructor
	int getSize() const { return size; } // returns the current size of the array
	int check(T key); // returns index of element holding "key" or -1 if none
	void addValue(T);    // adds number to the array
	void removeValue(T); // deletes the number from the array
	void printList();      // prints the values of the array

	//// big three rule
	VarList<T>(const VarList<T>&); // copy constructor
	VarList<T>& operator=(const VarList<T>&); // overloaded assignment
	~VarList(); // destructor

private:
	T* dArray; // pointer to the dynamically allocated array
	int size;   // array size
};


#include "Implementation.template"  //very important to include this template file where your methods need to be implemented.

#endif /* VARLIST_H */

