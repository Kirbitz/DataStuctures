#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main() {

	//Creates a data type named aircraft
	struct AirCraft {
		string aircraftName;
		string manufacturer;
		double takeOffDistance;
		double maxTakeOffWeight;
		int seats;
	};

	vector<AirCraft> myAirCrafts;

	//Opens the file aircrafts.txt
	ifstream fileIn("aircrafts.txt");
	if (!fileIn.is_open()) {
		cout << "Error: File not found!";
		return 1;
	}

	//Grabs the data from the file and puts it into the aircraft vector
	while (!fileIn.eof()) {
		AirCraft tempAir;
		getline(fileIn, tempAir.aircraftName);
		getline(fileIn, tempAir.manufacturer);
		fileIn >> tempAir.takeOffDistance;
		fileIn.ignore();
		fileIn >> tempAir.maxTakeOffWeight;
		fileIn.ignore();
		fileIn >> tempAir.seats;
		fileIn.ignore();
		fileIn.ignore();

		myAirCrafts.push_back(tempAir);
	}

	//Prints out the data with the vector in reverse order
	for (vector<AirCraft>::reverse_iterator airCraftIndex = myAirCrafts.rbegin(); airCraftIndex < myAirCrafts.rend(); airCraftIndex++) {
		cout << "Aircraft Name: " << airCraftIndex->aircraftName << endl;
		cout << "Manufacturer: " << airCraftIndex->manufacturer << endl;
		cout << "Takeoff Distance: " << airCraftIndex->takeOffDistance << endl;
		cout << "Max Takeoff Weight: " << airCraftIndex->maxTakeOffWeight << endl;
		cout << "Seats: " << airCraftIndex->seats << endl << endl;
	}

	return 0;
}