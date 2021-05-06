// IteratorBasicProjectExampleArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<algorithm> //std::max
using namespace std;
//typedef char Elem;
template <class Elem>
class ArraySequenceE {
public:

	class Iterator {
	protected:
		//int j = 0; // index of the next element to report 
		//bool removable = false; // can remove be called at this time? 
		Elem* v;        // pointer to the dynamic array 
		Iterator(Elem* u)      // //constructorcreate from pointer
		{
			v = u;
		}// an iterator for the list
	public:

		Elem& operator*() { return *v; }      // reference to the element
		Iterator& operator++()
		{
			++v;
			return *this;
		}

		// move to previous position
		Iterator& operator--()
		{
			--v;
			return *this;
		}

		// compare positions
		bool operator==(const Iterator& p) const
		{
			return v == p.v;
		}

		bool operator!=(const Iterator& p) const
		{
			return v != p.v;
		}
		// Define postfix increment operator.  
		Iterator operator++(int) //post increment operator overloading
		{
			Iterator temp = *this; // save the original value
			++* this;  //increment
			return temp; // return the older value
		}

		friend class ArraySequenceE;     // give ArraySequenceE access

	};

private:
	Elem* dynamicArray;
	int currentSize;
	int currentCapacity;
public:
	ArraySequenceE() {
		currentSize = 0;
		currentCapacity = 10;
		dynamicArray = new Elem[currentCapacity];
	}

	ArraySequenceE(int capacity) { //Overloaded constructor for capacity pass in
		currentSize = 0;
		currentCapacity = capacity;
		dynamicArray = new Elem[currentCapacity];
	}

	int size() const { return currentSize; }
	bool empty() const { return currentSize == 0; }

	void reserve(int N) {     // reserve at least N spots
		if (currentCapacity >= N) return;      // already big enough
		Elem* B = new Elem[N];       // allocate bigger array
		for (int j = 0; j < currentSize; j++)      // copy contents to new array
			B[j] = dynamicArray[j];
		if (dynamicArray != NULL) delete[] dynamicArray;      // discard old array
		dynamicArray = B;           // make B the new array
		currentCapacity = N;         // set new capacity
	}
	//insertion:
	//void insert(const Iterator& p, const Elem& e) // insert e before p
	void insert(Iterator& p, const Elem& e) // insert e before p
	{
		//note that p is not const so that we can fix it if the original array was expanded.
		int j = 0;
		if (currentSize >= currentCapacity) {      // overflow?
		 //find rank of p and stored to use it later for fixing p after changing the array to the exanded one.
			{
				Iterator q = beginItr();
				while (q != p) {    // until finding p
					++q; ++j;     // advance and count hops
				}
			}
			reserve(max(1, 2 * currentCapacity));    // double array size. Use max just in case currentcapacity was zero
			//fixing p
			p = Iterator(&dynamicArray[j]);
		}
		Iterator next = endItr();
		Iterator current = endItr();

		if (currentSize != 0)
		{
			--current;
			while (next != p) {
				*(next) = *(current);
				if (next != p) {
					--next;
					--current;
				}
			}
		}
		*(next) = e;          // put in empty slot
		++currentSize;          // one more element
	}
	void insertFront(const Elem& e) { Iterator p = beginItr();  insert(p, e);  /*used tmp p becasue neginItr is const. */ }
	void insertBack(const Elem& e) { Iterator p = endItr();  insert(p, e); }
	//deletion (erasing elements)
	void erase(const Iterator& p)    // remove p
	{
		if (empty()) throw invalid_argument("No element to remove");

		Iterator current = p;
		Iterator next = p;
		++next;
		while (next != endItr())
		{
			*current = *next;
			if (next != endItr())
			{
				++current; ++next;
			}
		}
		//p = end();
		--currentSize;

		// one fewer element
	}
	void eraseFront() { erase(beginItr()); }
	void eraseBack() {
		Iterator current = endItr();
		--current;
		erase(current);
	}
	Iterator beginItr() const  // begin position is first item
	{
		return Iterator(dynamicArray);
	}

	Iterator endItr() const  // end position is just beyond last
	{
		return Iterator(dynamicArray + currentSize);
	}

	Elem& operator[](int i) { //Overloads the [] operator for location of the object at index i
		//Iterator tester = beginItr();
		Iterator myIterator = atIndex(i);
		if (myIterator != endItr())
			return *myIterator;
		else {
			cout << "Element Not Found!\nPlease try again!\n";
			return *(beginItr());
		}
	}

	Elem& at(int i) /*throw (IndexOutOfBounds)*/ {
		Iterator myIterator = atIndex(i);
		if (myIterator != endItr())
			return *myIterator;
		else {
			cout << "Element Not Found!\nPlease try again!\n";
		}
	}

	void erase(int i) {
		ArraySequenceE<Elem>::Iterator myIterator = atIndex(i);
		if (myIterator != ArraySequenceE<Elem>::endItr())
			ArraySequenceE<Elem>::erase(myIterator);
		else
			cout << "Element Not Found!\nPlease try a different element!\n";
	}

	void insert(int i, const Elem& e) {
		ArraySequenceE<Elem>::Iterator myIterator = atIndex(i);
		if (myIterator != ArraySequenceE<Elem>::endItr())
			ArraySequenceE<Elem>::insert(myIterator, e);
		else
			cout << "Element Not Found\nPlease try a different element!\n";
	}

	typename ArraySequenceE<Elem>::Iterator atIndex(int index) const { //Finds the object at the specified index
		typename ArraySequenceE<Elem>::Iterator current = ArraySequenceE<Elem>::beginItr();
		if (index > ArraySequenceE<Elem>::size() - 1)
			return ArraySequenceE<Elem>::endItr();
		//Flows through the list and ends element of the current index
		for (int i = 0; i < index; i++){
			++current;
		}
		return current;
	}

	int indexOf(const typename ArraySequenceE<Elem>::Iterator& p) const {
		typename ArraySequenceE<Elem>::Iterator current = ArraySequenceE<Elem>::beginItr();
		int j = 0;
		while (current != p && current != ArraySequenceE<Elem>::endItr()) {
			++current;
			++j;
		}
		if (current != ArraySequenceE<Elem>::endItr())
			return j;
		else
			cout << "Error Object Not Found!\n";
	}

	ArraySequenceE(const ArraySequenceE& org) { //Copy Constructor
		currentSize = org.currentSize;
		currentCapacity = org.currentCapacity;
		dynamicArray = new Elem[currentCapacity];
		for (int i = 0; i < currentCapacity; i++){
			dynamicArray[i] = org.dynamicArray[i];
		}
	}

	ArraySequenceE operator=(const ArraySequenceE& rhs) { //Overloaded = operator
		if (this != &rhs) {
			currentSize = rhs.currentSize;
			currentCapacity = rhs.currentCapacity;
			dynamicArray = new Elem[currentCapacity];
			for (int i = 0; i < currentCapacity; i++) {
				dynamicArray[i] = rhs.dynamicArray[i];
			}
		}
		return *this;
	}

	~ArraySequenceE() {
		delete [] dynamicArray;
	}
};

int main()
{
	try {
		std::cout << "Hello World!\n";
		ArraySequenceE<char> Ar;

		for (char ch = 'A'; ch <= 'F'; ch = ch + 1)
			Ar.insertBack(ch);
		//['A', 'B', 'C', 'D', 'E','F']
		for (ArraySequenceE<char>::Iterator current = Ar.beginItr(); current != Ar.endItr(); ++current)
			cout << *current << endl;


		Ar.insertFront('Z');
		//['Z', 'A', 'B', 'C', 'D', 'E','F']
		//ArraySequenceE<char>::Iterator q = Ar.beginItr();
		int q = 0;
		Ar.insert(q, '$');
		//['$', 'Z', 'A', 'B', 'C', 'D', 'E','F']
		//ArraySequenceE<char>::Iterator r = Ar.endItr();
		int r = Ar.size() - 1;
		Ar.insert(r, '@');
		Ar.insertBack('%');
		Ar.insertBack('#');
		Ar.insertBack('+');
		Ar.insertBack('+');
		//['$', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', '@', '%', '#', '+', '+']
		for (char ch = 'G'; ch <= 'O'; ch = ch + 1)
			Ar.insertFront(ch);
		//['O','N','M','L','K','J','I','H','G','$', 'Z', 'A', 'B', 'C', 'D', 'E','F', '@', '%', '#', '+', '+']

		//Prints out the elements of Ar using an iterator
		/*for (ArraySequenceE<char>::Iterator current = Ar.beginItr(); current != Ar.endItr(); ++current)
			cout << *current << endl;*/

		//Prints out the elements in Ar using the [] operator
		/*for (int i = 0; i < Ar.size(); i++) {
			cout << Ar[i] << endl;
		}*/

		Ar.erase(q);

		//Prints out the elements in Ar using the .at method
		for (int i = 0; i < Ar.size(); i++) {
			cout << Ar.at(i) << endl;
		}

		//Prints the position of the second element in the array 
		cout << Ar.indexOf(++(Ar.beginItr())) << endl;
		
	}
	catch (...) {

		cout << "Something went wrong\n";
	}
}