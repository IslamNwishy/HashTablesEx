//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 4
//File: hashTable.cpp

#include "hashTable.h"
using namespace std;


template <class KeyType, class DataType>
hashTable<KeyType, DataType>::hashTable(int n) {
	//Set Maximum Size = nelemts
	MaxSize = n;
	//Allocate dynamic memory
	Table = new slot[MaxSize];
	//Set h = -1 (the index to a slot)
	h = -1;
	//Set csize = 0 (current size)
	csize = 0;
	
}

template <class KeyType, class DataType>
hashTable<KeyType, DataType>::~hashTable() {
	//delete allocated memory 
	delete []Table;
	//Reset Variables
	h = NULL;
	csize = NULL;
	MaxSize = NULL;
	
}

template <class KeyType, class DataType>
void hashTable<KeyType, DataType>::makeTableEmpty(const KeyType & EmptyKey) {
	//Set Empty = k (key that represents an empty slot)
	Empty = EmptyKey;
	//Loop to put the Empty key (EmptyKey) in all table slots
	for (int i = 0; i < MaxSize; i++)
		Table[i].key = EmptyKey;
	//set h = -1 (index to a slot)
	h = -1;
	//set csize = 0
	csize = 0;
	
}


template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::tableIsEmpty() const {
	return (csize <= 0);
}

template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::tableIsFull() const{
	return(csize >= MaxSize);
}

template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::insert(const KeyType &Key, const DataType &Data) {
	//if table is not full
	if (!tableIsFull()) {
		//find (h) using the hash function passing to it (k)
		h = hash(Key);
		//loop until find an empty slot (circular array: h = (h+1) % MaxSize)
		while (Table[h].key != Empty) {
			h = (h + 1) % MaxSize;
		}
		//insert key and data at the found empty slot (h)
		Table[h].key = Key;
		Table[h].data = Data;
		//increment csize
		csize++;
		//return true;
		return true;
	}
	//else return false;
	else
		return false;
	
}

template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::search(const KeyType &Key) {

	//if table is not empty
	if (!tableIsEmpty()) {

		//find h by calling the hash function passing to it Key
		h = hash(Key);
		//int start = h; //keep the starting point
		int start = h;
		
		//loop until either found or reach empty slot or reach start again
		do{
			//if slot h is empty return false;       //not found
			if (Table[h].key == Empty)
				return false;
			//if there is a match at h return true;  //found
			else if (Table[h].key == Key)
				return true;
			else
				h = (h+1) % MaxSize;                   //move to next slot

		} while (h != start);

		//if h is back to start
		return false;
	}
	
	else
		return false;
	
}

template <class KeyType, class DataType>
DataType hashTable<KeyType, DataType>::Retrieve(const KeyType &Key) {

	
	if (search(Key)) {
		//find h by calling the hash function passing to it Key
		h = hash(Key);
		while (true) {
			if (Table[h].key == Key)
				return Table[h].data;
			else
				h = (h + 1) % MaxSize;
		}
	}

	else {
		cout << "Couldn't Find the City! Here is the Closest result" << endl;
		return Table[Closest(Key)].data;
	}

}


template <class KeyType, class DataType>
int hashTable<KeyType, DataType>::Closest(const string &Key) const {
	int matches = 0, mismatches = 0, closest = 10000;		//Local Variables decleration
	int index, Shortlength, LongLength;

	for (int i = 0; i < MaxSize; i++) {						//Check every element in the table

		if (Table[i].key != Empty) {						//if that element is not empty, compare its distance
			int temp = (Table[i].key.length() - Key.length());
			if (temp< 0)									//find the longer and shorter lengths
			{
				Shortlength = Table[i].key.length(); 
				LongLength = Key.length();
			}
			else {
				Shortlength = Key.length(); 
				LongLength = Table[i].key.length();
			}

			for (int j = 0; j < Shortlength; j++) {		//find how many matches occur in the letters of the 2 strings
				if (Table[i].key[j] == Key[j])
					matches++;
			}

			mismatches = LongLength - matches;
			if (closest > mismatches) {						//if the mismatches are less than the smallest distance
				index = i;				//then save the position of the key and set it as the new smallest distance
				closest = mismatches;
			}
			matches = 0;									//reset the variable (unmatches) to 0
		}
	}
	return index;
}


template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::Update(const KeyType &Key, const DataType &Data) {

	if (search(Key)) {					//If the Key Exists
		h = hash(Key);					
		while (true) {					//Retrive it
			if (Table[h].key == Key) {
				Table[h].data = Data;	//Update it
				return true;
			}
			else
				h = (h + 1) % MaxSize;
		}
	}
	else
		return false;					//Else return false
}

template <class KeyType, class DataType>
bool hashTable<KeyType, DataType>::Traverse() {
	int j = 1;
	if (!tableIsEmpty()) {
		for (int i = 0; i < MaxSize; i++) {	//If the table is not empty, cout all non empty elements
			if (Table[i].key != Empty)
				cout << j << "," << Table[i].data << endl;
			else
				j--;
			j++;
		}
		return true;
	}
	else
		return false;
}



template<class KeyType, class DataType>
bool hashTable<KeyType, DataType>::Traverse(const string &FileName)
{
	int j = 0;
	output.open(FileName);				//open a file if it exists or create one if it doesn't
	if (!output.fail()) {
		output << "No.,City Name,Latitude,Longitude,Country" << endl; //Output the header
		if (!tableIsEmpty()) {
			for (int i = 0; i < MaxSize; i++) {		//output to the file every non empty element
				j++;
				if (Table[i].key != Empty)
					output << j << "," << Table[i].data << endl;
				else
					j--;
			}
			output.close();
			return true;
		}
		else
			return true;
	}

	else {											//Throw an error message if the file fails
		cout << "Could not Open the File! " << endl;
		return false;
	}
}


template<class KeyType, class DataType>
int hashTable<KeyType, DataType>::hash(const KeyType &Key) const {

	return h1(h2(Key));
}

template<class KeyType, class DataType>
int hashTable<KeyType, DataType>::h1(const unsigned long long int & h2) const
{
	return(h2 % MaxSize);
}


template<class KeyType, class DataType>
long long int hashTable<KeyType, DataType>::h2(const string &Name) const
{
	unsigned long long int sum = 0;
	for (long long int i = 0; i < Name.length(); i++) {
		sum += (int(Name[i])*pow(26,i));
	}
	return sum;
}



