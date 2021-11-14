//World fact book program by Nethmi Weeraman//

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <locale>
#include <memory>
#include <algorithm>

using namespace std;

//STRUCT TO STORE COUNTRIES-------------------------------------------------------------------------//
typedef struct country
{
	string name;
	long malePop;
	long femalePop;
	float area;
	string capital;
	short callCode;

} Country;


int complexity = 0;
vector<Country*>* nation;

//SORTING ALGORITHMS------------------------------------------------------------------------------//
void sortingChoice(vector<Country*>*);
template <typename T>
void sortForInput(short*, short*, short*, T*);

template <typename T>
void bubbleSort(T*, int, bool);
template <typename T>
int split(T*, int, int, bool);
template <typename T>
int quickSort(T*, int, int, bool);
template <typename T>
void insertionSort(T*, int, bool, short);

//DISPLAY FUNCTIONS--------------------------------------------------------------------------------//
template <typename T>
void displayCountryDetails(T*, int);
void loadData();
void displayCountryDetails();
void menu(vector<Country*>*);
void exitOrNot();
void inputCheck();
void swapCountryArray(string*, long*, long*, long*, float*, string*, short*, int, int);
void setOrdinal(int);

//SEARCHING ALGORITHMS-----------------------------------------------------------------------------//
void searchChoice(vector<Country*>*);

int linearSearch(vector<Country*>*);
int binarySearch(short*, int, int, int);
int exponentialSearch(short*, int, int);

//APPENDING COUNTRY--------------------------------------------------------------------------------//
void appendDetails(vector<Country*>*);

//CONSTRUCTOR AND DESTRUCTOR FOR COMPLEXITY AND TIME CALCULATION------------------------------------//
struct Timer {

	chrono::time_point<chrono::high_resolution_clock> start, last;

	Timer() {

		auto start = chrono::high_resolution_clock::now();      //Start time begins
		ios_base::sync_with_stdio(false);                       //Get the time as actual time
		complexity = 0;                                         //Resets complexity
	}

	~Timer() {

		auto last = chrono::high_resolution_clock::now();                                                  //End time begins
		double ms = chrono::duration_cast<chrono::milliseconds>(last - start).count();

		//Converts out of scientific notation
		ms *= 1e-6;                                                                                        

			cout << "Time taken: " << fixed << fixed << ms << setprecision(3) << " ms" << endl;            //Turns nanoseconds into milliseconds
			 
		cout << endl << "Complexity: " << complexity;                                                      //Outputs complexity
	}

};

//COMMA SEPERATOR FOR NUMBERS-----------------------------------------------------------------------//
struct separate_thousands : numpunct<char> {
	char_type do_thousands_sep() const override { return ','; }   // separate with commas
	string_type do_grouping() const override { return "\3"; }     // groups 3 digit to separate
};

int main()
{

	nation = new vector<Country*>;
	loadData();
	menu(nation);

	return 0;
}

/*checks if user enters expected data type*/
void inputCheck() {

	bool* data = new bool;
	*data = cin.fail();


	while (*data == true) {
		cout << "\nYou will be redirected to menu\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("pause");
		system("CLS");
		menu(nation);
	}
}

/*Main menu for sort, search and add options*/
void menu(vector<Country*>* nation)
{

	displayCountryDetails();                                              //Display the standard country details(unsorted)
	cout << "\nWELCOME TO THE WORLD FACT BOOK!";

	short* choice = new short;                                            //Options on what to do(sort, search, add countries)
	cout << "\nChoose to add, sort or search the countries:\n"
		<< "\nEnter 1 to add:"
		<< "\nEnter 2 to sort:"
		<< "\nEnter 3 to search:"
		<< "\nEnter 4 to exit program:"
		<< "\nNote: To return to main menu at any stage\nenter an alphabetic value"
		<< "\n\n\tEnter:";
	cin >> *choice;

	inputCheck();

	//Redirecting to choice's function//

	if (*choice == 1)
	{
		delete choice;
		appendDetails(nation);

	}
	else if (*choice == 2)
	{
		delete choice;
		sortingChoice(nation);

	}
	else if (*choice == 3)
	{
		delete choice;
		searchChoice(nation);

	}
	else if (*choice == 4)
	{
		exit(EXIT_FAILURE);
	}

	//Error handling for wrong choice entered//
	else
	{
		cout << "\nInvalid choice: Try again!\n";
		system("pause");
		system("CLS");
		delete choice;
		menu(nation);
	}

}

/*Adds new country by user into file and country struct*/
void appendDetails(vector<Country*>* nation)
{

	Country* newCoun = new Country;

	cout << "\nEnter relevant details:\n\n"
		<< "Name:";
	cin >> newCoun->name;

	inputCheck();

	newCoun->name[0] = toupper(newCoun->name[0]);

	for (int a = 1; a < newCoun->name.length(); a++)
	{
		newCoun->name[a] = tolower(newCoun->name[a]);
	}


	cout << "\nMale population: ";
	cin >> newCoun->malePop;

	inputCheck();

	cout << "\nFemale population: ";
	cin >> newCoun->femalePop;

	inputCheck();

	cout << "\nArea: ";
	cin >> newCoun->area;

	inputCheck();

	cout << "\nCapital: ";
	cin >> newCoun->capital;

	inputCheck();

	newCoun->capital[0] = toupper(newCoun->capital[0]);

	for (int a = 1; a < newCoun->capital.length(); a++)
	{
		newCoun->capital[a] = tolower(newCoun->capital[a]);
	}


	cout << "\nCalling code: ";
	cin >> newCoun->callCode;

	inputCheck();

	nation->push_back(newCoun);

	//Inputting new country created into file with the others//
	ofstream fout;
	fout.open("countries.csv", std::ofstream::app);

	fout << '\n' << newCoun->name << ',' << newCoun->malePop << ',' <<
		newCoun->femalePop << ',' << newCoun->area << ',' <<
		newCoun->capital << ',' << newCoun->callCode;

	fout.close();

	//Choice to add more or not//
	int* addMoreOrNot = new int;
	cout << "\nDo you want to add more countries?"
		<< "\nPress 1 for yes:"
		<< "\nPress any other number for no:\n"
		<< "\n\tEnter:";
	cin >> *addMoreOrNot;


	if (*addMoreOrNot == 1) { appendDetails(nation); }
	delete addMoreOrNot;
	cout << "\nYou will be redirected to menu\n";
	system("pause");
	system("ClS");

	main();


}

/*Handles the choice of different sorting routes*/
void sortingChoice(vector<Country*>* nation)
{

	short* input = new short;
	cout << "\nWhich do you want to sort the countries order in?\n"
		<< "Press 1 for total population:\n"
		<< "Press 2 for male population:\n"
		<< "Press 3 for female population:\n"
		<< "Press 4 for area:\n"
		<< "Press 5 for calling code:\n"
		<< "\n\tEnter: ";
	cin >> *input;

	inputCheck();

	while (*input != 1 && *input != 2 && *input != 3 && *input != 4 && *input != 5)
	{
		cout << "\nPlease select according to given choices.\n"
			<< "Enter: ";
		cin >> *input;
		inputCheck();
	}

	short* ascDscInput = new short;
	cout << "\nSort in ascending or descending order?\n"
		<< "Press 1 for ascending order:\n"
		<< "Press 2 for descending order:\n"
		<< "\n\tEnter: ";
	cin >> *ascDscInput;

	inputCheck();

	while (*ascDscInput != 1 && *ascDscInput != 2)
	{
		cout << "\nPlease select according to given choices.\n"
			<< "Enter: ";
		cin >> *ascDscInput;
		inputCheck();

	}

	short* sortInput = new short;
	cout << "\nWhich sorting algorithm would you like to use?\n"
		<< "Press 1 for quick sort algorithm:\n"
		<< "Press 2 for insertion sort algorithm:\n"
		<< "Press 3 for bubble sort algorithm:\n"
		<< "Enter: ";
	cin >> *sortInput;

	inputCheck();

	while (*sortInput != 1 && *sortInput != 2 && *sortInput != 3)
	{
		cout << "\nPlease select according to given choices.\n"
			<< "Enter: ";
		cin >> *sortInput;
		inputCheck();

	}
	system("ClS");

	cout << "\n\nSorted in: ";
	if (*input == 1) { cout << "Total population"; }
	else if (*input == 2) { cout << "Male population"; }
	else if (*input == 3) { cout << "Female population"; }
	else if (*input == 4) { cout << "Area"; }
	else if (*input == 5) { cout << "Calling code"; }

	cout << "\t\tOrdered in: ";
	if (*ascDscInput == 1) { cout << "Ascending"; }
	else { cout << "Descending"; }


	cout << "\t\tSorted by: ";
	if (*sortInput == 1) { cout << "Quick sort"; }
	else if (*sortInput == 2) { cout << "Integration sort"; }
	else if (*sortInput == 3) { cout << "Bubble sort"; }


	switch (*input)
	{

	case 1:
	{
		long* arr = new long[nation->size()];


		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = (nation->at(i)->femalePop + nation->at(i)->malePop);
		}
		cout << endl;

		sortForInput(sortInput, ascDscInput, input, arr);

	}

	break;

	case 2:
	{

		long* arr = new long[nation->size()];


		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = nation->at(i)->malePop;
		}
		cout << endl;

		sortForInput(sortInput, ascDscInput, input, arr);
	}

	break;

	case 3:
	{

		long* arr = new long[nation->size()];

		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = nation->at(i)->femalePop;
		}
		cout << endl;

		sortForInput(sortInput, ascDscInput, input, arr);
	}

	break;

	case 4:
	{

		float* arr = new float[nation->size()];

		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = nation->at(i)->area;
		}
		cout << endl;

		sortForInput(sortInput, ascDscInput, input, arr);
	}
	break;


	case 5:
	{

		short* arr = new short[nation->size()];

		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = nation->at(i)->callCode;
		}
		cout << endl;
		sortForInput(sortInput, ascDscInput, input, arr);
	}
	break;

	}


}

/*Implement sorting choice chosen*/
template <typename T>
void sortForInput(short* sortInput, short* ascDscInput, short* input, T* arr) {

	switch (*sortInput)
	{
	case 1:
	{
		Timer timer;
		delete sortInput;
		(*ascDscInput == 1) ? quickSort(arr, 0, (nation->size()-1), true) :
			quickSort(arr, 0, (nation->size()-1), false);


	}
	break;

	case 2:
	{
		Timer timer;
		delete sortInput;
		(*ascDscInput == 1) ? insertionSort(arr, (nation->size()), true, *input) :
			insertionSort(arr, (nation->size()), false, *input);

	}
	break;

	case 3:
	{
		Timer timer;
		delete sortInput;
		(*ascDscInput == 1) ? bubbleSort(arr, (nation->size()), true) :
			bubbleSort(arr, (nation->size()), false);

	}
	break;
	}

	cout << "\n\nDisplaying sorted details:\n";
	displayCountryDetails(arr, *input);
	delete input;
	delete ascDscInput;
	arr = NULL;
	exitOrNot();

}


/*Reads country details from file*/
void loadData()
{
	ifstream fin("countries.csv");

	if (fin.is_open())
	{
		string* heading = new string;
		getline(fin, *heading, ',');
		getline(fin, *heading, ',');
		getline(fin, *heading, ',');
		getline(fin, *heading, ',');
		getline(fin, *heading, ',');
		fin >> *heading;

		delete heading;

		string* comma = new string;

		while (fin.peek() != EOF)
		{
			Country* tempCoun = new Country;

			getline(fin, tempCoun->name, ',');
			fin >> tempCoun->malePop;
			getline(fin, *comma, ',');
			fin >> tempCoun->femalePop;
			getline(fin, *comma, ',');
			fin >> tempCoun->area;
			getline(fin, *comma, ',');
			getline(fin, tempCoun->capital, ',');
			fin >> tempCoun->callCode;

			nation->push_back(tempCoun);
		}

		delete comma;
		//Unit test for incorrect input: File reading//

	}
	else
	{
		cout << "Error: not opened\n" << endl;
	}

}

/*Shows country details as a table*/
void displayCountryDetails()
{

	cout << "\n\t\t\t\t\t\t\t\t\t    "
		<< " -.TABLE OF COUNTRIES AND THEIR DETAILS.-" << endl;

	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;


	cout << std::left << setw(25)
		<< "Country name:" << setw(25)
		<< "Total population:" << setw(30)
		<< "Male population:" << setw(35)
		<< "Female population:" << setw(30)
		<< "Area:" << setw(30)
		<< "Capital:" << setw(30)
		<< "Calling code:" << endl;

	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;

	//Calls thousands separator struct//
	auto thousands = unique_ptr<separate_thousands>(new separate_thousands());
	cout.imbue(locale(cout.getloc(), thousands.release()));

	int x = 1;
	for (int i = 0; i < nation->size(); i++)
	{
		cout << left
			<< setw(30) << nation->at(i)->name
			<< setw(12) << nation->at(i)->malePop + nation->at(i)->femalePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->malePop + nation->at(i)->femalePop < nation->at(m)->malePop + nation->at(i)->femalePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;


		cout << setw(12) << nation->at(i)->malePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->malePop < nation->at(m)->malePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(12) << nation->at(i)->femalePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->femalePop < nation->at(m)->femalePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(15) << fixed << setprecision(2) << nation->at(i)->area;


		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->area < nation->at(m)->area)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(25) << nation->at(i)->capital
			<< setw(12) << nation->at(i)->callCode;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->callCode < nation->at(m)->callCode)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;
	}


	cout << endl << endl << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;


	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;

}

/*Sets ordinals for ranks in table display*/
void setOrdinal(int x) {

	if (x % 10 == 1 && x != 11)
	{
		cout << "[" << x << setw(15) << "st]";
	}
	else if (x % 10 == 2 && x != 12)
	{
		cout << "[" << x << setw(15) << "nd]";
	}
	else if (x % 10 == 3 && x != 13)
	{
		cout << "[" << x << setw(15) << "rd]";
	}
	else
	{
		cout << "[" << x << setw(15) << "th]";
	}


}

/*Gets the search choice from user and displays details accordingly*/
void searchChoice(vector<Country*>* nation)
{

	int* position = new int;
	int* choiceInput = new int;
	cout << "\nWhat would you like to search by?\n"
		<< "Press 1 for name:\n"
		<< "Press 2 for calling code (Binary search):\n"
		<< "Press 3 for calling code (Exponential search):\n"
		<< "\n\tEnter:";
	cin >> *choiceInput;

	inputCheck();

	if (*choiceInput == 1)
	{
		Timer timer;
		*position = linearSearch(nation);
	}

	else if (*choiceInput == 2 || *choiceInput == 3)
	{

		short* arr = new short[nation->size()];

		for (int i = 0; i < nation->size(); i++)
		{
			arr[i] = nation->at(i)->callCode;
		}

		quickSort(arr, 0, nation->size() - 1, true);

		int* value = new int;
		cout << "\nEnter call code: ";
		cin >> *value;

		if (*choiceInput == 2)
		{
			Timer timer;
			*position = binarySearch(arr, 0, nation->size() - 1, *value);
		}
		else if ((*choiceInput == 3))
		{
			Timer timer;
			*position = exponentialSearch(arr, nation->size(), *value);
		}


		for (int i = 0; i < nation->size(); i++)
		{
			if (arr[*position] == nation->at(i)->callCode)
			{
				*position = i;
				break;
			}
		}


		delete arr;
		delete value;
	}

	else {
		cout << "\nInvalid: Try again!\n";
		searchChoice(nation);
	}


	if (*position != -1)
	{
		cout << "\n\nShowing matched country details:\n"
			<< "\nName:" << nation->at(*position)->name
			<< "\n\tMale Population: " << nation->at(*position)->malePop
			<< "\n\tFemale Population: " << nation->at(*position)->femalePop
			<< "\n\tArea of country: " << nation->at(*position)->area
			<< "\n\tCountry capital: " << nation->at(*position)->capital
			<< "\n\tCalling code: " << nation->at(*position)->callCode;

	}


	delete choiceInput;
	delete position;
	exitOrNot();


}

/*Binary search algorithm for call code*/
int binarySearch(short* arr, int start, int last, int value)
{

	//We use divide and conquer in this search method
	//We start at the middle value and
	// according to the size of the value we go either left or right
	//From there again we get the middle value and so on

	while (start <= last)
	{
		unique_ptr<int> mid(new int);
		*mid = (start + last) / 2;

		//complexity++;
		//Include complexity++ here rather than below
		//for greater accuracy in complexities

		if (arr[*mid] == value)
		{
			cout << "Found";
			return *mid;
		}

		else if (value < arr[*mid])
		{
			last = *mid - 1;
		}

		else if (value > arr[*mid])
		{
			start = *mid + 1;
		}

		complexity++;
	}

	cout << "Not found";
	return -1;
}

/*Linear search algorithm for name*/
int linearSearch(vector<Country*>* nation)
{
	string name;
	cout << "\nEnter name:";
	cin >> name;

	string arr;
	int i = 0;

	//Case adjustments//
	name[0] = toupper(name[0]);

	for (int a = 1; a < name.length(); a++)
	{
		name[a] = tolower(name[a]);
	}

	for (int x = 0; x < nation->size(); x++)
	{
		if (i > 4)
		{
			cout << "\nPartial match: Did you mean " << arr << "?" << "\n";
			return (x - 1);

		}
		else { i = 0; }

		arr = nation->at(x)->name;

		//Checking if digits are equal starting from the last//
		while (name[name.length() - i] == arr[arr.length() - i])
		{
			i++;
			complexity++;
			if (arr.length() - i <= 0)
			{
				cout << "Found";
				return x;
			}

		}

		complexity++;
	}

	cout << "Not found;";
	return -1;
}

/*Exponential search algorithm for call code*/
int exponentialSearch(short* arr, int last, int value) {

	std::unique_ptr<int> val(new int);
	int* lastbound = new int;
	*lastbound = last - 1;
	int* i = new int;
	*i = 1;

	//This hops between the numbers
	//until there is a value greater than the one searched for
	while (*i < last && arr[*i] <= value) {

		*i = *i * 2;
		complexity++;
	}

	//After this it is divided, and the range between this and the end is searched for
	//to find the call code
	*val = binarySearch(arr, (*i / 2), min(*i, *lastbound), value);
	delete lastbound;
	delete i;
	return *val;

}


/*Displays country details table after sorting*/
//overriding function
template <typename T>
void displayCountryDetails(T* arr, int input)
{

	string* tmparrN = new string[nation->size()];
	long* tmparrT = new long[nation->size()];
	long* tmparrM = new long[nation->size()];
	long* tmparrF = new long[nation->size()];
	float* tmparrA = new float[nation->size()];
	string* tmparrC = new string[nation->size()];
	short* tmparrCC = new short[nation->size()];

	//Mapping the sorted details with it's other correct country details//
	switch (input)
	{

	case 1:
	{


		for (int i = 0; i < nation->size(); i++)
		{
			for (int x = 0; x < nation->size(); x++)
			{
				if (arr[i] == (nation->at(x)->malePop + nation->at(x)->femalePop))
				{
					swapCountryArray(tmparrN, tmparrT, tmparrM, tmparrF, tmparrA, tmparrC, tmparrCC, i, x);
				}

			}
		}

	}
	break;

	case 2:
	{


		for (int i = 0; i < nation->size(); i++)
		{
			for (int x = 0; x < nation->size(); x++)
			{
				if (arr[i] == nation->at(x)->malePop)
				{
					swapCountryArray(tmparrN, tmparrT, tmparrM, tmparrF, tmparrA, tmparrC, tmparrCC, i, x);
				}

			}
		}

	}
	break;

	case 3:
	{


		for (int i = 0; i < nation->size(); i++)
		{
			for (int x = 0; x < nation->size(); x++)
			{
				if (arr[i] == nation->at(x)->femalePop)
				{
					swapCountryArray(tmparrN, tmparrT, tmparrM, tmparrF, tmparrA, tmparrC, tmparrCC, i, x);
				}

			}
		}

	}
	break;

	case 4:
	{


		for (int i = 0; i < nation->size(); i++)
		{
			for (int x = 0; x < nation->size(); x++)
			{
				if (arr[i] == nation->at(x)->area)
				{
					swapCountryArray(tmparrN, tmparrT, tmparrM, tmparrF, tmparrA, tmparrC, tmparrCC, i, x);
				}

			}
		}

	}
	break;

	case 5:
	{


		for (int i = 0; i < nation->size(); i++)
		{
			for (int x = 0; x < nation->size(); x++)
			{
				if (arr[i] == nation->at(x)->callCode)
				{
					swapCountryArray(tmparrN, tmparrT, tmparrM, tmparrF, tmparrA, tmparrC, tmparrCC, i, x);
				}

			}
		}

	}
	break;

	}

	//Correct order pushed into vector from temporary arrays//
	for (int i = 0; i < nation->size(); i++)
	{
		nation->at(i)->name = tmparrN[i];
		nation->at(i)->femalePop = tmparrF[i];
		nation->at(i)->area = tmparrA[i];
		nation->at(i)->capital = tmparrC[i];
		nation->at(i)->callCode = tmparrCC[i];
		nation->at(i)->malePop = tmparrM[i];
	}

	delete[] tmparrT;
	delete[] tmparrN;
	delete[] tmparrM;
	delete[] tmparrF;
	delete[] tmparrA;
	delete[] tmparrC;
	delete[] tmparrCC;
	delete[] arr;


	cout << "\n\t\t\t\t\t\t\t\t\t    "
		<< " -.TABLE OF COUNTRIES AND THEIR DETAILS.-" << endl;

	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;


	cout << std::left << setw(25)
		<< "Country name:" << setw(25)
		<< "Total population:" << setw(30)
		<< "Male population:" << setw(35)
		<< "Female population:" << setw(30)
		<< "Area:" << setw(30)
		<< "Capital:" << setw(30)
		<< "Calling code:" << endl;

	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;

	//Calls thousands separator struct//
	auto thousands = unique_ptr<separate_thousands>(new separate_thousands());
	cout.imbue(locale(cout.getloc(), thousands.release()));

	int x = 1;
	for (int i = 0; i < nation->size(); i++)
	{
		cout << left
			<< setw(30) << nation->at(i)->name
			<< setw(12) << nation->at(i)->malePop + nation->at(i)->femalePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->malePop + nation->at(i)->femalePop < nation->at(m)->malePop + nation->at(i)->femalePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;


		cout << setw(12) << nation->at(i)->malePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->malePop < nation->at(m)->malePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(12) << nation->at(i)->femalePop;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->femalePop < nation->at(m)->femalePop)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(15) << fixed << setprecision(2) << nation->at(i)->area;


		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->area < nation->at(m)->area)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;

		cout << setw(25) << nation->at(i)->capital
			<< setw(12) << nation->at(i)->callCode;

		for (int m = 0; m < nation->size(); m++)
		{
			if (nation->at(i)->callCode < nation->at(m)->callCode)
			{
				x++;
			}
		}

		setOrdinal(x);

		x = 1;
	}


	cout << endl << endl << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;


	cout << "..........................." << "........................................................................" <<
		"..................................." << "................................................................."
		<< endl;

	//Deletes countries vector
	delete nation;
}


/*Swaps sorted table with respective country details*/
void swapCountryArray(string* tmparrN, long* tmparrT, long* tmparrM, long* tmparrF, float* tmparrA, string* tmparrC, short* tmparrCC, int i, int x) {

	tmparrT[i] = nation->at(x)->malePop + nation->at(x)->femalePop;
	tmparrN[i] = nation->at(x)->name;
	tmparrF[i] = nation->at(x)->femalePop;
	tmparrA[i] = nation->at(x)->area;
	tmparrC[i] = nation->at(x)->capital;
	tmparrCC[i] = nation->at(x)->callCode;
	tmparrM[i] = nation->at(x)->malePop;

}


/*Bubble sort algorithm*/
template <typename T>
void bubbleSort(T* arr, int arrSize, bool ascending)
{


	if (ascending == true) {
		for (int i = 1; i < arrSize; i++)             //Outer loop is to check if 2 values are already sorted
		{

			for (int x = 0; x < arrSize - i; x++)       //i is deducted to keep check out of sorted values
			{
				//and not to go out of bound
				if (arr[x] > arr[x + 1])
				{
					swap(arr[x], arr[x + 1]);

				}

				complexity++;
			}

			complexity++;
		}
	}

	else {

		for (int i = 1; i < arrSize; i++)             //Outer loop is to check if 2 values are already sorted
		{

			for (int x = 0; x < arrSize - i; x++)       //i is deducted to keep check out of sorted values
			{
				//and not to go out of bound
				if (arr[x] < arr[x + 1])
				{
					swap(arr[x], arr[x + 1]);

				}

				complexity++;
			}

			complexity++;
		}


	}

}

/*Insertion sort algorithm*/
template <typename T>
void insertionSort(T* arr, int arrSize, bool ascending, short input)
{

	//We start, assuming arr[0] is in sorted set
	//Then we move smaller values to the left
	//We compare against digit at position and the number behind it
	if ((ascending == true)) {

		//For sorting float values
		if (input == 4) {
			for (int i = 1; i < arrSize; i++)
			{
				unique_ptr<float> value(new float);
				*value = arr[i];
				unique_ptr<int> position(new int);
				*position = i;

				while (*position > 0 && arr[*position - 1] > *value)
				{
					arr[*position] = arr[*position - 1];
					*position = *position - 1;
					complexity++;
				}

				//Final value placed in correct space
				arr[*position] = *value;
				complexity++;

			}
		}
		//For sorting other values
		else
		{
			for (int i = 1; i < arrSize; i++)
			{
				unique_ptr<int> value(new int);
				*value = arr[i];
				unique_ptr<int> position(new int);
				*position = i;

				while (*position > 0 && arr[*position - 1] > *value)
				{
					arr[*position] = arr[*position - 1];
					*position = *position - 1;
					complexity++;
				}

				//Final value placed in correct space
				arr[*position] = *value;
				complexity++;

			}
		}

	}
	else {
		//For sorting float values
		if (input == 4) {
			for (int i = 1; i < arrSize; i++)
			{
				unique_ptr<float> value(new float);
				*value = arr[i];
				unique_ptr<int> position(new int);
				*position = i;

				while (*position > 0 && arr[*position - 1] < *value)
				{
					arr[*position] = arr[*position - 1];
					*position = *position - 1;
					complexity++;
				}

				//Final value placed in correct space
				arr[*position] = *value;
				complexity++;

			}
		}
		//For sorting other values
		else
		{
			for (int i = 1; i < arrSize; i++)
			{
				unique_ptr<int> value(new int);
				*value = arr[i];
				unique_ptr<int> position(new int);
				*position = i;

				while (*position > 0 && arr[*position - 1] < *value)
				{
					arr[*position] = arr[*position - 1];
					*position = *position - 1;
					complexity++;
				}

				//Final value placed in correct space
				arr[*position] = *value;
				complexity++;

			}
		}


	}

}

/*Quicksort algorithm*/
//Partition for divide and conquer sortin

template <class T>
int split(T* arr, int start, int last, bool ascending)
{
	if (ascending == true) {
		int pivot = arr[last]; //Initial pivot
		int sindex = start;

		for (int left = sindex; left <= last - 1; left++)  //Left is start
		{
			if (arr[left] <= pivot)
			{
				swap(arr[left], arr[sindex]);
				sindex++;
			}

			complexity++;
		}

		swap(arr[sindex], arr[last]);
		//The end value(the pivot) will be swapped with the sindex
		//This is done because at sindex is where, after looping
		//the place it should be

		return sindex;
	}

	else {
		int pivot = arr[last]; //Initial pivot
		int sindex = start;

		for (int left = sindex; left <= last - 1; left++)  //Left is start
		{
			if (arr[left] > pivot)
			{
				swap(arr[left], arr[sindex]);
				sindex++;
			}

			complexity++;
		}

		swap(arr[sindex], arr[last]);
		//The end value(the pivot) will be swapped with the sindex
		//This is done because at sindex is where, after looping
		//the place it should be

		return sindex;

	}
}

//Sorts left and right and gets partition
template <typename T>
int quickSort(T* arr, int start, int last, bool ascending)
{

	if (start < last)
	{
		int sindex = split(arr, start, last, ascending);  //Split into two with pivot
		quickSort(arr, start, sindex - 1, ascending);      //Sorts left side
		quickSort(arr, sindex + 1, last, ascending);       //Sorts right side
	}

	if (start > last){return -1;}
}

/*Choice to exit or go to menu*/
void exitOrNot() {
	short* exitOrnot = new short;
	cout << "\n\nDo you want to exit or go to the main menu?"
		<< "\nPress 1 to go to main menu:"
		<< "\nPress any number to exit:\n"
		<< "\n\tEnter: ";
	cin >> *exitOrnot;

	if (*exitOrnot == 1)
	{
		delete exitOrnot;
		system("CLS");
		main();
	}
	else { exit(EXIT_FAILURE); }

}

