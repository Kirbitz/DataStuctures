#include "varList.h";

int main() {
	//Declares variables required for the main method
	VarList<int> myList;
	char selectionAns;
	int numAns;
	
	do {

		cout << "Enter operation [A/R/Q] :"; cin >> selectionAns;

		switch (toupper(selectionAns))
		{
		case 'A':
			cout << "Enter a value\t\t:"; cin >> numAns;
			myList.addValue(numAns);
			break;
		case 'R':
			cout << "Enter a value\t\t:"; cin >> numAns;
			myList.removeValue(numAns);
		case 'Q':
			break;
		default:
			cout << "Your selection was not A, R, or Q!\nPlease try again!\n";
			break;
		}

	} while (toupper(selectionAns) != 'Q');

	return 0;
}