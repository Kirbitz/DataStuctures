
#include <string>
#include <iostream>
#include <fstream>
#include "transportation.h"
#include "NodeList.h"
using namespace std;

/****************************Class Vehicle Method Implementations***************************************/
Vehicle::Vehicle() { 
	/*default constructor
	//fields are initialized with default data.
	//for the vehicle object, an empty dynamic array is allocated.
	*/
	vehicleID = -1;
	make = "NA";
	model = "NA";
	seats = 0;
	available = true;
	extarFeatures = 0;
	//otherFeaturesList = new NodeList<string>();
};

Vehicle::Vehicle(int _vehicleID_, string _make_, string _model_, int _seats_,
	bool _available_, int _extarFeatures_, string* _otherFeaturesList_) {
	/*overloaded constructor
	//fields are initialized with data sent via the constructor.
	//the array of features is sent fro outsite as a pointer.
	*/
	vehicleID = _vehicleID_;
	make = _make_;
	model = _model_;
	seats = _seats_;
	available = _available_;
	extarFeatures = _extarFeatures_;
	//otherFeaturesList = new NodeList<string>();
	for (int i = 0; i < extarFeatures; ++i)
		otherFeaturesList.insertBack(_otherFeaturesList_[i]);
};

//-------------
// if (v1>v2) 
bool Vehicle::operator> (const Vehicle& v) { 
	/* 
	// overloading the greater than operator >. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
		return ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures)));
}

bool Vehicle::operator< (const Vehicle& v) { // used seats then extrafeatures as keys
		/*
	// overloading the less than operator <. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
	return ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures)));
}


bool Vehicle::operator==(const Vehicle& v) // uses seats then extrafeatures as keys to compare between Vehicle objects
{
	/*
// overloading the equality operator ==. Number of seats and extra features are used 
//for determining if two vehicles are equal.
*/
	return (this->seats == v.seats && this->extarFeatures == v.extarFeatures);
}

bool Vehicle::operator<=(const Vehicle& v) // seats is the key
{
	/* overloading operator <= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures))));
}
bool Vehicle::operator>=(const Vehicle& v) // seats is the key
{	/* overloading operator >= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures))));

}

bool Vehicle::operator!=(const Vehicle& v) // seats is the key
{
	/* overloading the  operator != not equal*/
	return (!((this->seats == v.seats) && (this->extarFeatures == v.extarFeatures)));
}


//Rule of Three:
//destructor
Vehicle::~Vehicle() { 
	while (!otherFeaturesList.empty())
		otherFeaturesList.eraseFront();
};
// copy constructor	
Vehicle::Vehicle(const Vehicle& org) {  	
	vehicleID = org.vehicleID;
	make = org.make;
	model = org.model;
	seats = org.seats;
	available = org.available;
	extarFeatures = org.extarFeatures;
	//otherFeaturesList = new string[extarFeatures];
	for (NodeList<string>::Iterator i = org.otherFeaturesList.begin(); i != org.otherFeaturesList.end(); i++)
		otherFeaturesList.insertBack(*i);
}
//assignment operator overloading
Vehicle Vehicle::operator=(const Vehicle& rhs) {
	if (this != &rhs)
	{
		while (!otherFeaturesList.empty())
			otherFeaturesList.eraseFront();

		vehicleID = rhs.vehicleID;
		make = rhs.make;
		model = rhs.model;
		seats = rhs.seats;
		available = rhs.available;
		extarFeatures = rhs.extarFeatures;
		//otherFeaturesList = new string[extarFeatures];
		for (NodeList<string>::Iterator i = rhs.otherFeaturesList.begin(); i != rhs.otherFeaturesList.end(); i++)
			otherFeaturesList.insertBack(*i);

	}
	return *this;
}

/******** Friend Functions to the Vehicle***********/
ostream & operator<<(ostream &out, const Vehicle &objV)
// overleaoding the insertion operator <<
{
	out << "------------------------------------------\n";
	out <<"ID: "<< objV.vehicleID << endl;
	out << "Make: " << objV.make << endl;
	out << "Model: " << objV.model << endl;
	out << "Vumber of seats: "<<objV.seats << endl;
	if (objV.available)
		out << "Availability: available" << endl;
	else
		out << "Availability: Not available" << endl;
	out << "Extra Features["<< objV.extarFeatures <<"]: " << endl;
	if (objV.extarFeatures < 1)
		out << "Basic trim" << endl;
	else {
		out << "[";
		out << *objV.otherFeaturesList.begin();
		for (NodeList<string>::Iterator i = ++objV.otherFeaturesList.begin(); i != objV.otherFeaturesList.end(); i++)
			out << ", " << *i;
		out << "]" << endl;
	}
	return out;
}
ofstream & operator<<(ofstream &out, const Vehicle &objV)
// overleaoding the insertion operator << for the output file stream
{
	out << objV.vehicleID << endl;
	out << objV.make << endl;
	out << objV.model << endl;
	out << objV.seats << endl;
	out << objV.available << endl;
	out << objV.extarFeatures << endl;
	for (NodeList<string>::Iterator i = objV.otherFeaturesList.begin(); i != objV.otherFeaturesList.end(); i++)
		out << *i << endl;

	return out;
}



/****************************Class Inventory Method Implementations***************************************/
//default constructor
Inventory::Inventory() {
	capacity = 100; //default size
	registredVehiclesNo = 0;
	//v_List = new Vehicle[capacity];
}

//constructor II
Inventory::Inventory(int _capacity_) {
	capacity = _capacity_;
	registredVehiclesNo = 0;
	//v_List = new Vehicle[capacity];
	//	registredVehiclesNo = capacity;
}
Inventory::~Inventory() //destructor
{
	while (!v_List.empty())
		v_List.eraseFront();
}
//copy constructor
Inventory::Inventory(const Inventory& obj) {
	capacity= obj.capacity; 
	registredVehiclesNo = obj.registredVehiclesNo;
	//v_List = new Vehicle[capacity];
	for (NodeList<Vehicle>::Iterator i = obj.v_List.begin(); i != obj.v_List.end(); ++i)
		v_List.insertBack(*i);
}

//assignment overloading.
Inventory Inventory::operator=(const Inventory& rhs) {
	if (this != &rhs) {
		capacity = rhs.capacity;
		registredVehiclesNo = rhs.registredVehiclesNo;
		while (!v_List.empty())
			v_List.eraseFront();
		//v_List = new Vehicle[capacity];
		for (NodeList<Vehicle>::Iterator i = rhs.v_List.begin(); i != rhs.v_List.end(); ++i)
			v_List.insertBack(*i);
	}
	return *this;
}
//
bool Inventory::push_Back(Vehicle  ve) {
	/*inserting vehilce object to the inventory list*/
	/*Project 6: improve it by extending the underlining list, expands as needed.*/
	/*Project 6: make sure that it is consistent with the new data structure (NodeList) you used for this class.*/
	if (true) {
		v_List.insertBack(ve);
		++registredVehiclesNo;
		return true;
	}
	else
		return false;
}// end of push_back
//
void Inventory::sortList() {
	/*sorts the inventory list in decreasing order. See the operator > overloading for the class Vehicle*/
	for (NodeList<Vehicle>::Iterator i = v_List.begin(); i != v_List.end(); i++)
		for (NodeList<Vehicle>::Iterator j = i; j != v_List.end(); j++)
			if (*j > *i) {
				Vehicle strTmpTask = *j;
				*j = *i;
				*i = strTmpTask;
			}
}
void Inventory::printList(NodeList<Vehicle>::Iterator& index) {
	/*Project 5: Refactoring is needed here. You need to reimplement this method in a recursive way.*/
	/*so the method will traverse the list reursively to print out the vehicle info for all the list*/
	if(index != v_List.end()){
		cout << *index;
		cout << "------------------------------------------\n";
		printList(++index);
	}
}
void Inventory::printResevedList(NodeList<Vehicle>::Iterator& index) {  // print list of the reserved vehicles
	/*Project 5: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	if (index != v_List.end()) {
		if (!(*index).status()) { cout << *index; }
		printResevedList(++index);
	}
}
void Inventory::printAvailableList(NodeList<Vehicle>::Iterator& index) {// print list of the available vehicles
	/*Project 5: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	if (index != v_List.end()) {
		if ((*index).status()) { cout << *index; }
		printAvailableList(++index);
	}
}
bool Inventory::found(int seatsNo, NodeList<Vehicle>::Iterator& index) {
	// print list of the available vehicles that has AT LEAST seatsNo seats.
	//Pre-conditions: seatsNo is a positive value > 0
	/*Project 5: Refactoring is needed here. You need to reimplement this method in recursive way.*/

	int count = 0;
	bool Yes = true;
	if(index != v_List.end()) {
		if ((*index).status() && (*index).getSeats() >= seatsNo) {
			cout << *index;
			Yes = false;
		}
		if (!Yes)
			Yes = found(seatsNo, ++index);
		else
			found(seatsNo, ++index);
	}
	return Yes;
}
bool Inventory::reserveVehicle(int _vehicleID_) {
	NodeList<Vehicle>::Iterator index = v_List.begin();
	NodeList<Vehicle>::Iterator tmpVehicleID = checkID(_vehicleID_, index);
	if (tmpVehicleID != v_List.end() && (*tmpVehicleID).status()) {  //found and available			
		(*tmpVehicleID).reserve();
		return true;
	}
	return false;
}
bool Inventory::returnVehicle(int _vehicleID_) {
	NodeList<Vehicle>::Iterator index = v_List.begin();
	NodeList<Vehicle>::Iterator tmpVehicleID = checkID(_vehicleID_, index);
	if ((tmpVehicleID != v_List.end()) && (!(*tmpVehicleID).status())) {  //found and reserved available			
		(*tmpVehicleID).unReserve();
		return true;
	}
	return false;
}
NodeList<Vehicle>::Iterator Inventory::checkID(int _vehicleID_, NodeList<Vehicle>::Iterator index) {
	/*Project 5: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	if (index == v_List.end())
		return v_List.end();

	if ((*index).getID() == _vehicleID_)
		return index;
	else
		return checkID(_vehicleID_, ++index);
	

}


bool Inventory::saveToFile(string fileName) {
	/*this method prints the list data in a text file (received as a parameter) */
	//pre-conditions: fileName is a valid file name.  something.txt
	ofstream outFile;
	outFile.open(fileName);
	if (outFile.fail()) return false;
	//outFile << size() << endl;
	for (NodeList<Vehicle>::Iterator i = v_List.begin(); i != v_List.end(); ++i) { // updating the database
		outFile << *i;
	}

	outFile.close();
	return true;

}


/************** Freind functions to class Inventory ******************/


//ofstream & operator<<(ofstream &outfile, const Inventory &objV)
//// overleaoding the insertion operator << for the output file stream
//{
//
//	for (NodeList<Vehicle>::Iterator i = objV.v_List.begin(); i != objV.v_List.end(); i++) {
//		outfile << *i;
//		outfile << "------------------------------------------\n";
//	}
//	return outfile;
//}

