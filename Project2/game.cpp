#include "battleship-2.h"

int main() {
	//Declares variables required for the project
	//Also deploys the fleet of ships to random locations
	bool fleetPos = false;
	string fleetAns;
	Fleet myFleet;
	myFleet.deployFleet();

	//Prompts the user for whether they would like the positions of the ships displayed or not
	cout << "Would you like to see the fleet positions?[Y/N]\n";
	cin >> fleetAns;
	if (toupper(fleetAns[0]) == 'Y')
		fleetPos = true;

	//Runs most of the game by prompting the user to enter a fire location
	//then prompting them for whether they missed, hit, or already sunk
	do {
		Location userLocation(-1, -1);
		userLocation.fire();
		
		int result = myFleet.isHitNSink(userLocation);

		if (result == 1) 
			cout << "Good job you hit a ship!\n";
		else if (result == 2)
			cout << "You have already hit that ship!\n";
		else 
			cout << "You missed the ships!\n";
		
		if (fleetPos)
			myFleet.printFleet();

	} while (myFleet.operational());

	cout << "Congraculations you hit all the ships! :)\n";

	return 0;
}