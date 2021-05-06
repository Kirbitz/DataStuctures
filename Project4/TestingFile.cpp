#include "Stack.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	//Intializes the final stack and readin file reader
	Stack<string> finalStack;

	ifstream myFile;
	myFile.open("SecretMessage.txt");

	//Checks to make sure the file opened properly
	if (!myFile.is_open()) {
		cout << "File failed to open!\n";
		return 1;
	}

	//Reads in the lines of file until the EOF is hit
	while (!myFile.eof()) {
		//Initializes variables required for reading in lines and storing them to words
		Stack<char> fixingStack;
		string readInInput;
		string singleWords;
		string fixedInput = "";
		getline(myFile, readInInput);
		istringstream ss(readInInput);
		int count = 0;

		//Finds each individual word and stores it into singleWords until all words have been ubtained
		while (ss >> singleWords) {
			//Checks if the potision of the work is odd
			if (count % 2 == 0) {
				//Declares variable for fixed the reversed word
				string fixedWord;
				//Reverses the word using a char stack
				for  (int i = 0; i < singleWords.length(); i++)
				{
					fixingStack.push_back(singleWords[i]);
				}
				while (!fixingStack.empty()) {
					fixedWord.push_back(fixingStack.atTop());
					fixingStack.pop_off();
				}
				fixedInput += fixedWord + " ";
			}
			else {
				fixedInput += singleWords + " ";
			}
			count++;
		}
		//Stores the final statement into the stack
		finalStack.push_back(fixedInput);
	}

	//Prints out the stack in reverse
	while (!finalStack.empty()) {
		cout << finalStack.atTop() << endl;
		finalStack.pop_off();
	}

	return 0;
}