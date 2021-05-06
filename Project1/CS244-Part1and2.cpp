#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//Creates a data type called Customer
struct Customer {
	int accountNumber;
	string name;
	string email;
	double accountBalance;
};

//Methods required for the program
double removeComma(string);
void printOutFile(Customer*, int);

int main() {

	//Opens the file called Customer.txt
	ifstream fileIn("Customer.txt");
	if (!fileIn.is_open()) {
		cout << "Error: File not found!";
		return 1;
	}

	//Finds the number of lines within the file
	int count = 0;
	while (!fileIn.eof()) {
		fileIn.ignore();
		count++;
	}
	fileIn.close();
	fileIn.open("Customer.txt");

	//Creates a pointer array based on the number of customers in the txt file
	Customer* myCustomers = new Customer[count / 4];
	count = 0;

	//Grabs the information from the file and puts it into the pointer array
	while (!fileIn.eof()) {
		fileIn >> myCustomers[count].accountNumber;
		fileIn.ignore();
		getline(fileIn, myCustomers[count].name);
		getline(fileIn, myCustomers[count].email);
		string tempString;
		getline(fileIn, tempString);
		myCustomers[count].accountBalance = removeComma(tempString);
		count++;

	}

	fileIn.close();

	//Sorts the array in decreasing order
	for (int index = 0; index < count; index++){
		for (int index2 = index+1; index2 < count; index2++){
			if (myCustomers[index].accountBalance < myCustomers[index2].accountBalance) {
				Customer tempCust = myCustomers[index];
				myCustomers[index] = myCustomers[index2];
				myCustomers[index2] = tempCust;
			}
		}
	}

	//Prints the info in the pointer array
	for (int index = 0; index < count; index++) {
		cout << "Account Number:\t" << myCustomers[index].accountNumber << endl;
		cout << "Name:\t\t" << myCustomers[index].name << endl;
		cout << "Email:\t\t" << myCustomers[index].email << endl;
		cout << "Account Balace:\t" << setprecision(2) << fixed << myCustomers[index].accountBalance << endl;
		cout << "\n----------------------------------------------------------------\n\n";
	}

	printOutFile(myCustomers, count);

	return 0;
}

//Removes the comma from the cash value in the txt file and returns the value as a double
double removeComma(string myNum) {
	int count = 0;

	for (int i = 0; myNum[i]; i++) {
		if (myNum[i] != ',') {
			myNum[count++] = myNum[i];
		}
	}

	myNum[count] = '\0';
	
	return stod(myNum.c_str());
}

//Prints the data in the pointer array to a file called report1.txt including a total amount value
void printOutFile(Customer * myCustomers, int counter) {
	ofstream fileOut("report1.txt");
	int count = 0;
	double total = 0;
	for (int index = 0; index < counter; index++) {
		count++;
		total += myCustomers[index].accountBalance;
		fileOut << count << ")" << myCustomers[index].name << "\t$" << setprecision(2) << fixed << myCustomers[index].accountBalance << endl;
	}
	fileOut << "--------------------------------------------------------------------------------------------------------\n";
	fileOut << "Total:\t\t$" << setprecision(2) << fixed << total << endl;
}