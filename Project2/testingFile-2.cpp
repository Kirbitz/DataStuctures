//Test Application File.

#include "battleship-2.h"
#include <iostream>

using std::cout; using std::cin; using std::endl;
bool validLocations(Fleet);
bool uniqueLocations(Fleet);

/// this is main function
int main() {

	// srand(time(nullptr)); // random seed   
	// checking location objects created by default and overloaded constructors
	srand(time(nullptr));
	Location mySpot(4, 5), userShot;

	userShot.print();

	if (userShot.getCoordX() == -1 && userShot.getCoordY() == -1)
		cout << " default Constructor: Passed!\n";
	else
		cout << " default Constructor: Failed!\n";

	mySpot.print();

	if (mySpot.getCoordX() == 4 && mySpot.getCoordY() == 5)
		cout << " Overloaded (x,y) Constructor: Passed!\n";
	else
		cout << " Overloaded (x,y)  Constructor: Failed!\n";

	//testing the pick method. coordinates must be between 1 and 5. 
	//Will try 50 patterns
	int passedCount = 0;
	int possibleconsecutiveDuplications = 0;
	Location previousLoc; //previous generated random location
	for (int i = 0; i < 50; ++i)
	{
		mySpot.pick(); // selecting a new random location

		if (i > 0 && mySpot == previousLoc)
			++possibleconsecutiveDuplications;

		if ((mySpot.getCoordX() >= 1 && mySpot.getCoordX() <= 5) && (mySpot.getCoordY() >= 1 && mySpot.getCoordY() <= 5))
			++passedCount;

		previousLoc = mySpot;

	}

	cout << "Correct generated locations: " << passedCount << "/" << 50;
	if (passedCount == 50)
		cout << "--> Passed!" << endl;
	else
		cout << "--> Failed!" << endl;

	if (possibleconsecutiveDuplications > 10)
		cout << "\nWarning! System generated the same coordinates consecutively more than 10 time. Please used a better seed for the rand() function. --> " << possibleconsecutiveDuplications << endl;

	cout << "Last Randomly generated location: ";
	mySpot.print();

	cout << "\nInput location: ";
	userShot.fire(); // having user input a location

	////testing the == perator overloading
	if (mySpot == userShot) {
		cout << "Random location matches user input.";
		if ((mySpot.getCoordX() == userShot.getCoordX()) && (mySpot.getCoordY() == userShot.getCoordY()))
			cout << "--> Passed! \n";
		else
			cout << "Failed! Manual inspection is recommended.\n";
	}
	else
	{
		cout << "Random location does not match user input.";
		if (!((mySpot.getCoordX() == userShot.getCoordX()) && (mySpot.getCoordY() == userShot.getCoordY())))
			cout << "--> Passed!\n";
		else
			cout << "Failed! Manual inspection is recommended.\n";

	}

	////testing copare method
	if (compare(mySpot, userShot)) {
		cout << "Random location matches user input.";
		if ((mySpot.getCoordX() == userShot.getCoordX()) && (mySpot.getCoordY() == userShot.getCoordY()))
			cout << "--> Passed!\n";
		else
			cout << "Failed! Manual inspection is recommended.\n";
	}
	else {
		cout << "Random location does not match user input.";
		if (!((mySpot.getCoordX() == userShot.getCoordX()) && (mySpot.getCoordY() == userShot.getCoordY())))
			cout << "--> Passed!\n";
		else
			cout << "Failed! Manual inspection is recommended.\n";

	}



	// checking ship object================================================================

	 // uncomment this part once you are done debugging above code

	Ship myship;

	myship.setLocation(mySpot); // placing ship at myspot location
	if (mySpot == myship.getLocation())
		cout << "setlocation() works. --> passed!\n";
	else
		cout << "setlocation() didn't work. --> failed!\n";

	if (myship.match(userShot))
		cout << "\nmyship\'s location matches user input. --> passed!\n";
	else
		cout << "\nmyship's location does not match user input. --> passed!\n";

	if (!myship.isSunk()) {
		cout << "\nmyship is not sunk yet. --> passed!\nsinking it.\n";
		myship.sink();
	}
	if (myship.isSunk()) {
		cout << "\nsink method worked. --> passed!\n";
	}
	else
		cout << "sink method didn't worked. --> failed!\n";

	//testing the innsertion operator overloading. manual inspection is needed.
	cout << "myship\'s information is: " << myship << endl;

	//testing printship method. . manual inspection is needed.
	cout << "myship\'s status is: "; myship.printShip();

	////
	//// checking fleet object============================================================================
	//// 
	//// uncomment this part once you are done debugging above code
	Fleet myFleet;
	//testing the fleet default information:
	Ship* fleetInfoList = myFleet.getShipList();
	bool fleetDefaultInfoTest = true;
	Location defaultLocation(-1, -1);
	for (int i = 0; i < myFleet.getFleetSize(); ++i)
		if (!(fleetInfoList[i].getLocation() == defaultLocation) || (fleetInfoList[i].isSunk()))
		{
			fleetDefaultInfoTest = false;
			break;
		}
	if (fleetDefaultInfoTest)
		cout << "\nFleet Default Info is Correct. --> Passed!";
	else
		cout << "Fleet Default Info is NOT Correct. --> Failed!";

	myFleet.deployFleet(); // fleet is deployed at random locations
	if (validLocations(myFleet))
		cout << "\nAll Locations are  valid. --> Passed!";
	else
		cout << "\nInvalid Location/s. --> Failed!";

	if (uniqueLocations(myFleet))
		cout << "\nNo duplicated Locations. --> Passed!";
	else
		cout << "\nduplicated locations are being dedection.. --> Failed!";

	if (myFleet.operational()) {
		cout << "\nAt least one ship is up.";
		//is this ture?
		Ship* fleetInfoList = myFleet.getShipList();
		bool operational = true;
		for (int i = 0; i < myFleet.getFleetSize(); ++i)
			if (fleetInfoList[i].isSunk())
			{
				operational = false;
				break;
			}
		if (operational)
		{
			cout << "\nOperational Method. --> Passed!\n";
		}
		else
		{
			cout << "\nOperational Method. --> Failed!\n";
		}
	}

	if (myFleet.isHitNSink(userShot))
		cout << "there was a ship at userShot location, now it is sunk.\n";
	else
		cout << "there was no ship at userShot location.\n";

	cout << "\nWarning: Manual Inspection is expected for the output format expectations.\nmyFleet\'s status is: ";
	myFleet.printFleet();

	userShot.fire();

	if (myFleet.isHitNSink(userShot))
		cout << "there was a ship at userShot location, now it is sunk.\n";
	else
		cout << "there was no ship at userShot location.\n";

	cout << "Warning: Manual Inspection is needed. Make sure that the hit ship is shown as sunk.";

	myFleet.printFleet();

	return 0;
}//end of main method



bool validLocations(Fleet myFleet) {
	//Pre-conditionds: myFleet object must have a valid array of ship data type.
	Ship* fleetInfoList = myFleet.getShipList();
	for (int i = 0; i < myFleet.getFleetSize(); ++i)
		if (!((fleetInfoList[i].getLocation().getCoordX() >= 1 && fleetInfoList[i].getLocation().getCoordX() <= 5) && (fleetInfoList[i].getLocation().getCoordY() >= 1 && fleetInfoList[i].getLocation().getCoordY() <= 5)))
		{
			return false;
		}

	return true;
}

bool uniqueLocations(Fleet myFleet) {
	//Pre-conditionds: myFleet object must have a valid array of ship data type.
	Ship* fleetInfoList = myFleet.getShipList();
	for (int i = 0; i < myFleet.getFleetSize(); ++i)
		for (int j = i + 1; j < myFleet.getFleetSize(); ++j) {
			if (fleetInfoList[i].getLocation() == fleetInfoList[j].getLocation())
			{
				return false;
			}

		}
	return true;
}