#pragma once
#ifndef Transportation_H
#define Transportation_H
#include <string>
#include <iostream>
#include <fstream>
#include "DoublyLinkedList.h"
#include "NodeList.h"
using namespace std;
class Vehicle {
public:
	Vehicle();
	Vehicle(int , string , string , int ,bool , int , string* );
	void reserve()  { available = 0; }
	void unReserve() { available = 1; }
	bool status() const { return available == 1; }
	int getID() const { return vehicleID; }
	string getmake() const { return make; }
	string getmodel() const { return model; }
	int getSeats()const { return seats; }
	int getextarFeatures()const { return extarFeatures; }
	string * getFeaturesList() const {
		string* temp = new string[extarFeatures];
		int index = 0;
		for (NodeList<string>::Iterator i = otherFeaturesList.begin(); i != otherFeaturesList.end(); i++) {
			temp[index] = *i;
			index++;
		}
		return temp;
	}
	~Vehicle(); // destructor
	Vehicle(const Vehicle& );   //copy Constructor

	Vehicle operator=(const Vehicle& rhs);  // assignment overlaoding

	// operators overloading 
	bool operator>(const Vehicle&);
	bool operator<(const Vehicle&);
	bool operator==(const Vehicle&);
	bool operator<=(const Vehicle&);
	bool operator>=(const Vehicle&);
	bool operator!=(const Vehicle&);

	friend ostream & operator << (ostream &, const Vehicle &);
	friend ofstream & operator << (ofstream &, const Vehicle &);
	
private:
	int vehicleID; //an integer number automatically assigned when object is created.
	string make;
	string model;
	int seats; // number of seats
	bool available; //a Boolean variable that is initially has true indicating that the vehicle is available.
	int extarFeatures; // number of the extra features in the vehicle
	NodeList<string> otherFeaturesList;
	/*Project 5: Refactoring is needed here. You need to replace the dynamic array with a list object. 
	you must update all the affected methods in the entire project*/

};  // end of class Vehicle

//========================================================================
class Inventory {
public:
	Inventory(); 

	Inventory(int );
	//rule of three
	Inventory(const Inventory&);  //C.C
	Inventory operator=(const Inventory&); // =.O.L
	~Inventory(); 

	bool push_Back(Vehicle  );// push_back
	void sortList();
	void printList(NodeList<Vehicle>::Iterator&);
	void printResevedList(NodeList<Vehicle>::Iterator&);
	void printAvailableList(NodeList<Vehicle>::Iterator&);
	bool found(int, NodeList<Vehicle>::Iterator&);
	bool reserveVehicle(int );
	bool returnVehicle(int );
	NodeList<Vehicle>::Iterator checkID(int, NodeList<Vehicle>::Iterator );
	int size() { return registredVehiclesNo; }  // inline implementation
	bool saveToFile(string fileName);
	NodeList<Vehicle>::Iterator firstNode() {
		return v_List.begin();
	}
	friend ofstream & operator<<(ofstream &outfile, const Inventory& objV)
		// overleaoding the insertion operator << for the output file stream
	{
		for (NodeList<Vehicle>::Iterator i = objV.v_List.begin(); i != objV.v_List.end(); i++) {
			outfile << *i;
			outfile << "------------------------------------------\n";
		}
		return outfile;
	}
	//ofstream & operator << (ofstream & oufile );
	//friend ofstream & operator << (ofstream&, const Inventory&);
	 //
	
	//ofstream &operator<<( const Inventory&);
private:

	int capacity; // array size
	int registredVehiclesNo;
	NodeList<Vehicle> v_List;   //dynamic array
	/*Project 5: Refactoring is needed here. You need to replace the dynamic array with a Nodelist object.
      you must update all the affected methods in the entire project*/
};



#endif