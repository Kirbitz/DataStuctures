#include "battleship-2.h"

//Methods for the Location class

Location::Location() { // void constructor, dynamically allocates the coordinates array and assignes -1 to both of the coordinates
	coordinates = new int[2];
	coordinates[0] = -1;
	coordinates[1] = -1;
}

Location::Location(int coord1, int coord2) {	// overloaded constructor to be used to create a location object with given coordinates.
	coordinates = new int[2];
	coordinates[0] = coord1;
	coordinates[1] = coord2;
}

void Location::pick() { // picks a random location. Means assignes 1 to 5 to the elements of the coordinates array
	int newX;
	int newY;
	do{
		newX = rand() % 5 + 1;
		newY = rand() % 5 + 1;
	} while (coordinates[0] == newX && coordinates[1] == newY);
	coordinates[0] = newX;
	coordinates[1] = newY;
}
void Location::fire() { // asks the user to input coordinates of the next shot
	do {
		cout << "Please enter a X coordinate between 1 and 5.\n";
		cin >> coordinates[0];
	} while (coordinates[0] < 1 || coordinates[0] > 5);

	do {
		cout << "Please enter a Y coordinate between 1 and 5.\n";
		cin >> coordinates[1];
	} while (coordinates[1] < 1 || coordinates[1] > 5);

}
void Location::print() const { // prints location in format "[x,y]"  e.g., [2,4]
	cout << "[" << coordinates[0] << "," << coordinates[1] << "]";
}

// predicate returns true if the two locations match
bool compare(const Location& lhs, const Location& rhs) {
	if (lhs.coordinates[0] == rhs.coordinates[0] && lhs.coordinates[1] == rhs.coordinates[1]) 
		return true;
	
	return false;
}

//rule of three
Location::Location(const Location& org){ // copycostructor
	coordinates = new int[2];
	coordinates[0] = org.coordinates[0];
	coordinates[1] = org.coordinates[1];
}
Location& Location::operator=(const Location& rhs) { //assignment overloading
	this->coordinates[0] = rhs.coordinates[0];
	this->coordinates[1] = rhs.coordinates[1];
	return *this;
}
Location::~Location() {	//destructor
	delete[] coordinates;
}


//Methods for the ship class
Ship::Ship() { // void constructor, sets sunk=false
	sunk = false;
}
bool Ship::match(const Location& location) const { // returns true if this location matches
	return (loc == location);
}

void Ship::sink() { sunk = true; }  // sets "sunk" member variable of the ship to true

void Ship::setLocation(const Location& rhs) { // deploys the ship at the specified location
	loc = rhs;
}
void Ship::printShip() const { // prints location and status of the ship
	string status;
	if (!sunk)
		status = " up ";
	else
		status = " sunk ";
	loc.print();
	cout << "->" << status << endl;
}

ostream& operator<<(ostream& os, const Ship& sh)
{
	string status;
	if (!sh.sunk)
		status = " up ";
	else
		status = " sunk ";
	sh.loc.print();

	os << "->" << status << endl;
	return os;
}

//Methods for Fleet class

void Fleet::deployFleet() { // deploys the ships in random locations
	int i = 0;
	while (i < FLEET_SIZE) {
		Location tempLoc;
		tempLoc.pick();
		if (check(tempLoc) == -1) {
			ships[i].setLocation(tempLoc);
			i++;
		}
	}
}						// of the ocean
bool Fleet::operational() const { // predicate returns true if at least
	for (int i = 0; i < FLEET_SIZE; i++){
		if (!ships[i].isSunk())
			return true;
	}
	return false;
}						  // one ship in the fleet is not sunk
int Fleet::isHitNSink(const Location& shotLoc) { 
	int checkValue = check(shotLoc);
	if (!(checkValue == -1)) {
		if (ships[checkValue].isSunk())
			return 2;

		ships[checkValue].sink();
		return 1;
	}
	return 0;		  // returns 1 if there was a deployed
					  // ship at this location (hit) and sinks it
}					  // and returns 0  if a miss(not occupied by any ship)
					  //returns 2 if it is occupied by it is already sunk!
void Fleet::printFleet() const { // prints out locations of ships in fleet
	for (int i = 0; i < FLEET_SIZE; i++){
		ships[i].printShip();
	}
}

int Fleet::check(const Location& matchLoc) const {  // returns index of the ship 
	for (int i = 0; i < FLEET_SIZE; i++){
		if (ships[i].match(matchLoc))
			return i;
	}
	return -1;				  // that matches location
}							  // -1 if none match