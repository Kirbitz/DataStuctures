
// Assignment 3.  Dr. Alnaeli, Stout 
//testMain.cpp
#include <iostream>
#include <string>
#include <ctime>
#include "varList.h"
using namespace std;
template <class T>
void testingCpyConstruct(VarList<T>);

int main() {
	srand(time(nullptr) + rand() % 100); //better seed
	VarList<char> charList;
	if (charList.getSize() == 0) 
		cout << "Default size: Passed!" << endl;
	else
		cout << "Default size: Failed!. Review the default constructor" << endl;
	// testing regular member functions
	
	for (int i = 0; i < 5; ++i)
	{
		char tmp = (char)('A' + rand() % 26) ;
		charList.addValue( tmp);
		if (!(tmp >= 'A' && tmp <= 'Z'))
		{
			cout << "Invalid random data. Failed! Review the addValue method" << endl;
			return 1;
		}

	}
	cout << "Valid random data. Passed!" << endl;

	if (charList.getSize() == 5) {
		cout << "Updated size: Passed!" << endl;
		
	}
	else {
		cout << "Updated size: Failed!. Review the addValue method." << endl;
		return 1;
	}
	charList.printList();	
	cout << "Attention: Manual Inspection is required. Please make sure that the data is properly printed." << endl;
	char properData;
	cout << "Is data properly printed? Y/N : ";
	cin >> properData;
	if (properData != 'Y' && properData != 'y') {
		cout << "Failed!...Please review the printList method. " << endl;
		return 1;
	}
	char duplicatedValue= '$';
	cout << "\nAdding  '" << duplicatedValue <<"'"<< endl;
	charList.addValue(duplicatedValue);
	if(charList.check(duplicatedValue)>-1) {
		cout << "Check Method: Passed!" << endl;
	}
	else {
		cout << "Failed!. Review the check method." << endl;
		return 1;
	}

	charList.printList();
	cout << "\nAdding  '" << duplicatedValue <<"', again!"<< endl;
	charList.addValue(duplicatedValue);// trying to add duplicate, should not add it

	charList.printList();
	cout << "Attention: Manual Inspection is required. Please make sure that the $ is not present twice in the list." << endl;
	
	cout << "Is $ present twice in the list? Y/N : ";
	cin >> properData;
	if (properData == 'Y' && properData == 'y') {
		cout << "Failed!...Please review the addValue method. " << endl;
		return 1;
	}

	cout << "\ncurrent size of the list: " << charList.getSize() << endl;

	if (charList.check(duplicatedValue) == -1) // check() returns -1 if value (key) not present
	{
		cout << "\n" << duplicatedValue << " is not present in the list. Failed!" << endl;
		return 1;

	}
	else
		cout << "\n" << duplicatedValue << " is present in the list. Passed!" << endl;

	if (charList.check('*') == -1)
		cout << "\n* is not present in the array. Passed!" << endl;
	else
	{
		cout << "\n* is present in the list. Failed!" << endl;
		return 1;
	}

	charList.printList();
	charList.removeValue(duplicatedValue);
	charList.printList();
	if (charList.check(duplicatedValue) != -1) // check() returns -1 if value (key) not present
	{
		cout << "\n" << duplicatedValue << " is still present in the list. Failed!.....Review the removeValue method." << endl;
		return 1;

	}
	else
		cout << "\n" << duplicatedValue << " was removed from the list. Passed!" << endl;
	int currentSize1 = charList.getSize();
	charList.removeValue('$'); //removing non existing value
	charList.printList();
	int currentSize2 = charList.getSize();
	if (currentSize1 != currentSize2) {
		cout << "Problem with nonexisting value removal....Failed!" << endl;
		return 1;
	}
	//// uncomment this when you debugged the first part
	int originalSize = charList.getSize();

	{
		VarList<char> charList2, charList3; //local variables

		charList3 = charList2 = charList; // testing overloaded assignment
		charList3 = charList3; // testing protection against self-assingment
		cout << "charList  :"; 		charList.printList();
		cout << "charList2 :"; charList2.printList();
		cout << "charList3 :"; charList3.printList();

		testingCpyConstruct(charList3); // testing copy constructor
		cout << "after sending to a functon, charList3 :"; charList3.printList(); // if destructor is implemented correctly
		// this should print properly after tes tfunc complete
		if (charList.getSize() == originalSize && charList2.getSize() == originalSize && charList3.getSize() == originalSize)
		{
			cout << "Rule of three, Test 1......... Passed!\n";
		}
		else
		{
			cout << "Problem with Rule of three. Failed!";
			return 1;
		}
	}
	cout << "outside of the block where local copies were declared. charList  :";
	charList.printList();  // must print properly, otherwise this is a rproblem with rule of 3 implementations
	if (charList.getSize() == originalSize )
	{
		cout << "Rule of three, Test 2......... Passed!\n";
	}
	else
	{
		cout << "Problem with Rule of three, test 2........ Failed!";
		return 1;
	}
	return 0;

} // end of function main.


//// tests pass-by-value for object of class varArray
template <class T>
void testingCpyConstruct(VarList<T> receivedList)
{ // copy constructor is invoked on "receivedList"
	receivedList.printList();

}
//// destructor is invoked when "receivedList" goes out of its scope since it is a method parameter
