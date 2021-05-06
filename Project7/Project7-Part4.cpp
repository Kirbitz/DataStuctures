#include <iostream>
#include <ctime>

using namespace std;

void sortArray(char[], int); //Sorts the Array
void removeDuplicatedChars(char[], int); //Removes Duplicates from the array
void printArray(char[], int); //Prints the array

int main() {
	const int charSize = 100;
	char charDNA[charSize];
	srand(time(NULL)); //Seeds a random value in system based on time
	for (int i = 0; i < charSize; i++){ //Fills the charDNA array with char values from A to Z
		charDNA[i] = (rand() % 26) + 'A';
	}
	sortArray(charDNA, charSize);
	printArray(charDNA, charSize);
	cout << endl << endl; //Spaces the two prints
	removeDuplicatedChars(charDNA, charSize);
	printArray(charDNA, charSize);

	return 0;
}

void printArray(char myArray[], int SIZE) {
	for (int i = 0; i < SIZE; i++) //For loop that iterates through the elements of the array
	{
		if (i % 10 == 0 && i > 0)//After every ten elements the array continues printing on the next line
			cout << endl;
		cout << myArray[i] << " ";
	}
}

void sortArray(char myArray[], int currentSize) {
	for (int i = 1; i < currentSize; i++)//For loop to iterate through the array
	{
		int j = i;
		while (j > 0 && myArray[j] < myArray[j - 1]) {//Continues to move the element in the array till it is in its rightful position
			char temp = myArray[j];
			myArray[j] = myArray[j - 1];
			myArray[j - 1] = temp;
			j -= 1;
		}
	}
}

void removeDuplicatedChars(char myArray[], int currentSize) {
	int currentLocation = 1; //Keeps track of the last deletion location
	char currentChar = myArray[0]; //Keeps track of the current character to compare to
	for (int i = 1; i < currentSize; i++) //For loop to iterate through the array once giving O(n) time complexity
	{
		if (myArray[i] == currentChar) //Checks if the current element is a duplicate
			myArray[i] = '$';
		else {
			currentChar = myArray[i]; //Changes the currentChar to the new value to keep track of
			char temp = myArray[currentLocation]; //Next three lines simply swap the elements around from currentLocation and i
			myArray[currentLocation] = myArray[i];
			myArray[i] = temp;
			currentLocation++; //Increments current location in order to keep track of the next swap
		}
	}
}