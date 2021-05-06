//Hashing and Collision Handling.
//Dr. ALnaeli. University of Wisconsin.
//CS244_Assignment7_Q3
#include <iostream>
#include <string>
using namespace std;
int bicycleListCurrentSize = 0; // # of bicycles in the list
const int MAX_SIZE = 101;
class Bicycle {
private:
	int bikeIdentificationNumber;
	string bikeName;
	double bikePrice;
	string currentOwner;
	string currentOwnerAddress;
	string currentOwnerPhoneNo;

public:
	//constructor
	Bicycle(int _bike_ID_int, string _bikeName_str, double _bike_Price_dbl,
		string _currentOwner_str, string _currentOwnerAddress_str, string _currentOwnerPhoneNo_str) {
		bikeIdentificationNumber = _bike_ID_int;
		bikeName = _bikeName_str;
		bikePrice = _bike_Price_dbl;
		currentOwner = _currentOwner_str;
		currentOwnerAddress = _currentOwnerAddress_str;
		currentOwnerPhoneNo = _currentOwnerPhoneNo_str;
	}
	Bicycle() {
		bikeName = "-";
		bikeIdentificationNumber = -1;
		bikePrice = 0;
		currentOwner = "-";
		currentOwnerAddress = "-";
		currentOwnerPhoneNo = "-";
	}
	int getbikeIdentificationNumber() { return bikeIdentificationNumber; }
	string getInfo() {

		return ("[" + to_string(bikeIdentificationNumber) + " , " + bikeName + "," + to_string(bikePrice) + " , " + currentOwner + " , " + currentOwnerAddress
			+ " , " + currentOwnerPhoneNo + "]");
	}

	Bicycle(const Bicycle& otherBicycle)
	{
		bikeName = otherBicycle.bikeName;
		bikeIdentificationNumber = otherBicycle.bikeIdentificationNumber;
		bikePrice = otherBicycle.bikePrice;
		currentOwner = otherBicycle.currentOwner;
		currentOwnerAddress = otherBicycle.currentOwnerAddress;
		currentOwnerPhoneNo = otherBicycle.currentOwnerPhoneNo;
	}

	Bicycle& operator=(const Bicycle& otherBicycle)
	{
		if (this != &otherBicycle)
		{
			bikeName = otherBicycle.bikeName;
			bikeIdentificationNumber = otherBicycle.bikeIdentificationNumber;
			bikePrice = otherBicycle.bikePrice;
			currentOwner = otherBicycle.currentOwner;
			currentOwnerAddress = otherBicycle.currentOwnerAddress;
			currentOwnerPhoneNo = otherBicycle.currentOwnerPhoneNo;
		}
		return *this;
	}

};  // end of class Bicycle

//============secret Hashing Function===================
// simple hash method for demonstration purpose
int myHashFunction(Bicycle* currentBike)
{
	int zoo = 505;
	if (currentBike == nullptr)
		return -1;

	return ((currentBike->getbikeIdentificationNumber() + zoo) % MAX_SIZE);
}
//======================================================
void addNewbikeToCollection(Bicycle* newBicycle);
Bicycle* findBike(Bicycle*& newBicycle);
void printList(int);
void testing(Bicycle*, Bicycle*);
//hash table
Bicycle* hashTable[MAX_SIZE];  //hash table
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main() {

	for (int i = 0; i < MAX_SIZE; ++i)
		hashTable[i] = nullptr;

	Bicycle* bike_1 = new Bicycle(101123456, "Trek Butterfly Madone", 500000.00, "Saleh Alnaeli", "xyz1, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_2 = new Bicycle(101123487, "Trek Yoshimoto Nara", 200000.00, "Chris Mooney", "xyz2, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_3 = new Bicycle(101123429, "KAWS: Trek Madone", 160000.00, "Chris Freeman", "xyz3, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_4 = new Bicycle(101123433, "Aurumania Crystal Edition Gold Bike", 114000.00, "Nelu Alnaeli", "xyz4, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_5 = new Bicycle(101123410, "Trek Madone 7: Diamond", 75000.00, "Terry Mason", "xyz5, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_6 = new Bicycle(101123466, "Chrome Hearts X Cervelo", 60000.00, "Diane Chrisie", "xyz6, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_7 = new Bicycle(101123567, "Montante Luxury Gold Collection", 46000.00, "Ali Algadry", "xyz7, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_8 = new Bicycle(101123569, "eRockit’s Electric Assist Bike", 44000.00, "Jonatahn Maletic", "xyz8, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_9 = new Bicycle(101123570, "Litespeed Blade Bike", 40788.00, "Mo Salah", "xyz9, Menomonie, WI 54751", "715-###-####");
	Bicycle* bike_10 = new Bicycle(101123557, "Phanuel Krencker’s ‘Bicylettes de Luxe’", 34425.00, "Hadi Dalla", "xyz10, Menomonie, WI 54751", "715-###-####");
	////WithoutLinearProbing (: ++++++++
	addNewbikeToCollection(bike_1);
	addNewbikeToCollection(bike_2);
	addNewbikeToCollection(bike_3);
	addNewbikeToCollection(bike_4);
	addNewbikeToCollection(bike_5);
	addNewbikeToCollection(bike_6);
	addNewbikeToCollection(bike_7);
	addNewbikeToCollection(bike_8);
	addNewbikeToCollection(bike_9);
	addNewbikeToCollection(bike_10);
	testing(bike_6, bike_7);
	return 0;
} //end of main
void addNewbikeToCollection(Bicycle* newBicycle) {
	int hashedLocation = myHashFunction(newBicycle);
	while (hashTable[hashedLocation] != nullptr) {
		hashedLocation++;
	}
	bicycleListCurrentSize++;
	hashTable[hashedLocation] = newBicycle;
}
Bicycle* findBike(Bicycle*& newBicycle) {
	int hashedLocation = myHashFunction(newBicycle);
	while (hashTable[hashedLocation] != nullptr && hashTable[hashedLocation]->getbikeIdentificationNumber() != newBicycle->getbikeIdentificationNumber()) {
		hashedLocation++;
	}
	if (hashTable[hashedLocation] == nullptr)
		return nullptr;
	return hashTable[hashedLocation];
}

void printList(int size) {
	int i = 0;
	while (i < size) {
		cout << i << " : " << hashTable[i]->getInfo() << endl;
		++i;
	}
}

void testing(Bicycle* bike_6, Bicycle* bike_7) {
	//Testing. (1 of 3)........................
	cout << "The current number of bicycle records in the list: " << bicycleListCurrentSize << ", [Supposed to be: " << 10 << "]" << endl;
	cout << "Test 1/3: ";
	if (bicycleListCurrentSize < 10)
	{
		cout << "Failed!" << endl;
	}
	else
		cout << "Passed!" << endl;
	cout << "***************************************************" << endl;

	//Testing. (2 of 3)........................
	///note: objects bike_6 and bike_7 will be mapped to the same spot. Thust collision.
	Bicycle* tmp3 = findBike(bike_6);
	cout << "Test 2/3: ";
	if (tmp3->getbikeIdentificationNumber() != bike_6->getbikeIdentificationNumber())
	{
		cout << "Failed!" << endl;
	}
	else
	{
		cout << "Passed!" << endl;
	}
	cout << "***************************************************" << endl;

	//Testing. (3 of 3)........................
	Bicycle* tmp4 = findBike(bike_7);
	cout << "Test 3/3: ";
	if (tmp4->getbikeIdentificationNumber() != bike_7->getbikeIdentificationNumber())
	{
		cout << "Failed!" << endl;
	}
	else
	{
		cout << "Passed!" << endl;
	}
	cout << "***************************************************" << endl;
}
