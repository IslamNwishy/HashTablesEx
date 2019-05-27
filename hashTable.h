//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 4
//File: hashTable.h

#include<fstream>
#include<iostream>
#include<math.h>
using namespace std;

#ifndef HashTable_H
#define HashTable_H


template <class KeyType, class DataType>
class hashTable {

public:
	ifstream input;									//Input file stream name
	ofstream output;								//Output file stream name


	hashTable(int n = 11);							//Constructor
	~hashTable();									//Destructor

	void makeTableEmpty(const KeyType &);			//Empty all Slots
	bool tableIsEmpty() const;						//Return true if the table is Empty
	bool tableIsFull() const;						//Return true if the table is full
	bool insert(const KeyType &, const DataType &); //Add a new element to the table
	bool search(const KeyType &);					//return true if the element exists in the table
	DataType Retrieve(const KeyType&);				//Returns an element if it exists or the closest one to it
	int Closest(const string&) const;				//Returns the closest Key using Hamming-Distance
	bool Update(const KeyType&, const DataType&);	//Updates the data of a given Key
	bool Traverse();								//Outputs the non empty elements to the screen
	bool Traverse(const string& FileName);			//Outputs the non empty elements to a file

private:

	class slot {									//A class that represents a table slot
	public:
		KeyType key;
		DataType data;
	};

	slot *Table;									//Pointer to the table
	int h, MaxSize, csize;				//h is the hash value, MaxSize is the table's max size, csize is the current size
	KeyType Empty;									//The Value of the symbol for an empty slot

	int hash(const KeyType &) const;				//Returns the hash value of a given key
	int h1(const unsigned long long int&) const;	//Returns the the remainder of a given number / by max size (x % max)
	long long int h2(const string &) const;			//Returns the Sum of all characters in a stirng * 26^i
	

};

#endif // !HashTable_H

