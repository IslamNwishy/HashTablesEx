//Name: Islam Osama Nwishy
//ID#: 900170200
//Assignment 4
//File: App.cpp

#include"hashTable.h"
#include"hashTable.cpp"
#include<string>
#include <algorithm>
using namespace std;


//Data Class, Contains the Data of a City
class Data {
public:
	string CityName;
	string latitude;
	string longitude;
	string country;
	friend ostream & operator<<(ostream& out, const Data& data);
	friend istream & operator>>(istream& in, Data& data);
	friend ofstream & operator<<(ofstream& out, const Data& data);
	friend ifstream & operator>>(ifstream& in, Data& data);
	
};

//A Function that Checks if a string is a number
bool isNum(const string &c) {
	for (int i = 0; i < c.length(); i++)
		if (!isdigit(c[i]))
			return false;
	return true;
}

//A function that takes a string and replaces a certain substring in it to another substring
bool replace(string& str, string from, string to) {
	size_t start_pos = str.find(from);
	if (start_pos == string::npos)		//if you can't find the substring return false
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

//A funtion that takes the input of Latitude or Longitude as DMS
//Dir=1 for Latitude, Dir=any number but 1 for Longitude
void DMS(istream &in, string &dms, int Dir) {
	string temp;									//Temproray Variable to store the input
	
	//Inputing Degrees
	cout << "\tEnter Degrees: ";
	getline(in, temp);
	if (!isNum(temp))						//If the Input is not a number throw an error message and take a new value 
		do {
			cout << "Wrong Input! Hint: Degrees must be a number" << endl;
			cout << "\tEnter Degrees: ";
			getline(in, temp);
		} while (!isNum(temp));

		temp.push_back('o');				//Add the degree symbol and make the string dms = temp
		dms = temp;
	
		//Inputing Minutes
		cout << "\tEnter Minutes: ";
		getline(in, temp);
		if (!isNum(temp))					//If the Input is not a number throw an error message and take a new value
			do {
				cout << "Wrong Input! Hint: Minutes must be a number" << endl;
				cout << "\tEnter Minutes: ";
				getline(in, temp);
			} while (!isNum(temp));

			temp.push_back('\'');			//Add the Minutes Degree and Append it to dms
			dms.append(temp);


			//According to Dir choose to take the input of Latitude or Longitude
			if (Dir == 1) {

				cout << "\tEnter Direction (N or S for Latitude): ";
				getline(in, temp);
				if (toupper(temp[0]) != 'N'&& toupper(temp[0]) != 'S')		//Check Input
					do {
						cout << "Wrong Input! Hint: Direction must be either N or S" << endl;
						cout << "\tEnter Direction (N or S for Latitude): ";
						getline(in, temp);
						
					} while (toupper(temp[0]) != 'N'&& toupper(temp[0]) != 'S');
			}
			else {

				cout << "\tEnter Direction (E or W for Longitude): ";
				getline(in, temp);
				if (toupper(temp[0]) != 'E' && toupper(temp[0]) != 'W')		//Check Input
					do {
						cout << "Wrong Input! Hint: Direction must be either E or W" << endl;
						cout << "\tEnter Direction (E or W for Longitude): ";
						getline(in, temp);
					} while (toupper(temp[0]) != 'E' && toupper(temp[0]) != 'W');
			}

			dms.push_back(toupper(temp[0]));		//Appened the First Letter as an Uppercase to dms

}

//Overloading Cout and Cin
ostream & operator<<(ostream&out, const Data& data) {
	out << data.CityName << ',';
	out << data.latitude << ',';
	out << data.longitude << ',';
	out << data.country;
	return out;
}
istream & operator>>(istream& in, Data& data) {



	cout << "Enter City Name: ";		//input the city name
	getline(in, data.CityName);

	cout << "Enter Latitude: \n";		//input the latitude
	DMS(in, data.latitude, 1);

	cout << "Enter Longitude: \n";		//input the longitude
	DMS(in, data.longitude, 2);

	cout << "Enter Country Name: ";		//input the country name
	getline(in, data.country);

	return in;
}



//Overloading outputing and inputing from a file
ofstream & operator<<(ofstream& out, const Data& data) {
	out << data.CityName << ',';
	out << data.latitude << ',';
	out << data.longitude << ',';
	out << data.country;
	return out;
}
ifstream & operator>>(ifstream& in, Data& data) {

	getline(in, data.CityName, ',');		//Dummy getline to get rid of the numbering

	getline(in, data.CityName, ',');		//Take the cell in the 2nd column of a given row and store it as city name

	getline(in, data.latitude, ',');		//Take the cell in the 3rd column of a given row and store it as latitude
	replace(data.latitude, "°", "o");		//The UTF-8 symbols were not showing up in the console and sometimes not 
	replace(data.latitude, "?", "'");		//Not even in the files so i had to replace them

	getline(in, data.longitude, ',');		//Take the cell in the 4th column of a given row and store it as longitude
	replace(data.longitude, "°", "o");		//The UTF-8 symbols were not showing up in the console and sometimes not 
	replace(data.longitude, "?", "'");		//Not even in the files so i had to replace them

	getline(in, data.country, '\n');		//Take the cell in the 5th column of a given row and store it as country
	replace(data.country, " ", " ");		//The space was not showing properly in the console so i had to replace it

	return in;

}


//Functions Prototyping
void InputFile(ifstream &input, hashTable<string, Data> &Table);
void Start(hashTable<string, Data> &Table, ifstream& input);
void AddEntry(hashTable<string, Data> &Table);
string UpperCase(string x);
Data FindandDisplay(hashTable<string, Data> &Table);
void FindandUpdate(hashTable<string, Data> &Table);
void DisplayTable(hashTable<string, Data> &Table);
void ExportTable(hashTable<string, Data> &Table);

void main() {
	//Variable Declaration
	ifstream input("List.csv");
	ofstream output;
	hashTable<string, Data>Table(1000);
	Table.makeTableEmpty("-1");

	//Taking the Text file and Starting the Program
	InputFile(input, Table);
	Start(Table,input);
}

//A function that inputs the data of a .csv file into the hash Table
void InputFile(ifstream &input, hashTable<string, Data> &Table) {
	Data data;
	string dummy;

	if (!input.fail()) {				//If you managed to open the file, insert all of its data into the Table 
		getline(input, dummy, '\n');	//Dummy getline to get rid of the headings
		while (!input.eof()) {
			input >> data;
			Table.insert(UpperCase(data.CityName), data);
		}
		cout << "Done!" << endl;
	}
	else
		cout << "Error! Could not Open the File!" << endl;		//If the file failed, throw an error massege
	input.close();												//Close the file afterwards

}

// 1 = Add an entry, 2=Retrive a city, 3=Update an Entry, 4=List all cities (traverse), 5= List all cites into a file
// 6= Input from a New File, 7: Exit the Program
void Start(hashTable<string, Data> &Table, ifstream& input) {
	int command = 0;
	string dummy, FileName;

	cout << "Welcome To the Major List of Cities";
	while (command != 7) { //Exit case

		cout << endl << endl << "You Can:" << endl << endl;
		cout << "\t1- Add an Entry to the List\n\t2- Search for a Major City\n\t3- Update the Data of a City\n\t";
		cout << "4- See the Full List\n\t5- Export the List to a File\n\t6- Take a new List From File\n\t7- Exit the Program\n";
		cout << "Please Enter your Choice [1,2,3,4,5,6]" << endl;
		cin >> command;
		getline(cin, dummy);		//Dummy to get rid of the (cin) leftovers
		if (cin.fail()) {			//Check if the input does not suite the type int
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			command = 0;
		}


		switch (command) {
		case 1:
			AddEntry(Table);									//Add a new Entry
			break;
		case 2:
			FindandDisplay(Table);								//Search and Retrieve a city
			break;
		case 3:
			FindandUpdate(Table);								//Search and retrive a city then Update
			break;
		case 4:
			DisplayTable(Table);								//Traverse and output the table;
			break;
		case 5:
			ExportTable(Table);									//Traverse and output to a file;
			break;
		case 6:
			cout << "Please Enter a '.csv' File Destination" << endl;	//Input from a new File
			getline(cin, FileName);
			input.open(FileName);
			InputFile(input, Table);
			break;
		case 7:
			break;												 //Exit case
		default:
			cout << "Wrong Input! Please Try Again!" << endl;	//Wrong Input
			break;

		}
	}
}

//Takes an Entry and add it to the Table
void AddEntry(hashTable<string, Data> &Table) {
	Data temp;
	cin >> temp;
	Table.insert(UpperCase(temp.CityName), temp);
	cout << "City Added! Thank You!" << endl;
}

//Switches a given string to Uppercase
string UpperCase(string x) {
	transform(x.begin(), x.end(), x.begin(), ::toupper);
	return x;
}

//Takes a city name that it searches and displays
Data FindandDisplay(hashTable<string, Data> &Table) {

	string CityName;
	Data temp;
	cout << "\tPlease Enter a City Name to search" << endl << "\t";
	getline(cin, CityName);
	temp=Table.Retrieve(UpperCase(CityName));
	cout << "City Name:" << temp.CityName << endl;
	cout << "Latitude:" << temp.latitude << endl;
	cout << "Longitude:" << temp.longitude << endl;
	cout << "Country:" << temp.country << endl;

	return temp;

}

//1= Change City Name, 2= Change latitude, 3=Change longitude, 4= Change Country, 5= Change All
void FindandUpdate(hashTable<string, Data> &Table) {
	int command = 0;
	Data temp = FindandDisplay(Table);
	string Key = UpperCase(temp.CityName), dummy;
	
	
	while (command==0) { //Exit case is that the user typed a valid input

		cout << "Choose What You Want to Update" << endl;
		cout << "\t1- City Name\n\t2- Latitude\n\t3- Longitude\n\t4- Country\n\t5- Everything" << endl;
		cout << "Please Enter your Choice [1,2,3,4,5]" << endl;
		cin >> command;
		getline(cin, dummy);
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			command = 0;
		}
		
			


		switch (command) {
		case 1:
			
			cout << "\tEnter a City Name" << endl << "\t";		//input the city name
			getline(cin, temp.CityName);
			break;
		case 2:
			
			cout << "\tEnter a Latitude" << endl << "\t";		//input the latitude
			DMS(cin, temp.latitude, 1);
			break;
		case 3:
			
			cout << "\tEnter a Longitude" << endl << "\t";		//input the longitude
			DMS(cin, temp.longitude, 2);
			break;
		case 4:
		
			cout << "\tEnter a Country" << endl << "\t";		//input the country
			getline(cin, temp.country);
			break;
		case 5:
			cin >> temp;										//input Everything
		default:
			cout << "Wrong Input! Please Try Again!" << endl;	//Wrong Input
			break;

		}
		
	}

	if (Table.Update(Key, temp))
		cout << endl << "Updated!" << endl;
	else
		cout << endl << "Couldn't Update! Please Try Again!" << endl;
	
}


//Outputs the full table to the screen
void DisplayTable(hashTable<string, Data> &Table) {
	cout << "No.,City Name,Latitude,Longitude,Country" << endl;
	Table.Traverse();
}

//Outputs the full table to a Given Output File
void ExportTable(hashTable<string, Data> &Table) {
	string OutFile;
	cout << "Please Enter File Destination" << endl;
	getline(cin, OutFile);
	if (Table.Traverse(OutFile))
		cout << endl << "Done!" << endl;
	else
		cout << "Please Try Again" << endl;
	
}