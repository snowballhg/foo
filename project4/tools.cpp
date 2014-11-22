/*
	The tools source holds all the functions that operate the Winery tracker
	It holds the menu, reads input, executes user input, and does some error checking on input
*/
#include "tools.h"
#include "data.h"
using namespace std;

/*
for main() test driver

#include "tools.h"
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main()
{
	//memory leak detection tool
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//test for constructor, add, and display
	char fileName[] = "data.dat";
	table aTable(fileName);

	char reply = ' ';
	do {
		displayMenu();
		reply = readCommand();
		exeCommand(reply, aQueue);
		} while (toupper(reply) != 'Q');

	aTable.writeData(fileName);

	return 0;
}
*/

//function to display menu
void displayMenu()
{
	cout << '\n' << "Please pick one of the following: " << endl;
	cout << "(a) to add a Stock to the table" << endl;
	cout << "(s) to search for a specific Stock" << endl;
	cout << "(m) to modify and existing Stock entry" << endl;
	cout << "(r) to remove a Stock from the table" << endl;
	cout << "(d) to show the data in the table" << endl;
	cout << "(k) to show the size of each chain" << endl;
	cout << "(q) to quit" << endl;
}

//function to read input from the menu
char readCommand()
{
	char replyOption;
	cout << "Enter your choice: ";
	cin >> replyOption;
	cin.ignore(100, '\n');
	return tolower(replyOption);
}

//function to act on user input
void exeCommand(char reply, hashTable& aTable)
{
	int i;
	char key[11];
	float modNetAssetValue;
	char modDate[15];
	float modYtdReturn;
	data stock;

	switch (tolower(reply))
	{
	case 'a':
		getStock(stock);
		aTable.add(stock);
		break;
	case 's':
		cout << "Enter the symbol of the stock you want to remove: " << endl << endl;
		readString("\tStock Symbol: ", key);
		if (aTable.retrieve(key, stock))
		{
			cout << "Stock found in table." << endl;
			cout << stock << endl;
		}
		else
		{
			cout << "Stock not found..." << endl;
		}
		break;
	case 'm':
		cout << "Enter the symbol of the stock you want to remove: " << endl << endl;
		readString("\tStock Symbol: ", key);
		if (aTable.retrieve(key, stock))
		{
			cout << "\nPlease enter information about the Stock: " << endl;
			modNetAssetValue = readFloat("\tNet Asset Value: ");
			readString("\tDate: ", modDate);
			modYtdReturn = readFloat("\tYear-to-date Retuen %: ");
			if (aTable.modify(key, modNetAssetValue, modDate, modYtdReturn))
			{
				cout << "Stock successfully modified." << endl;
			}
		}
		else
		{
			cout << "Stock not found..." << endl;
		}
		break;
	case 'r':
		cout << "Enter the symbol of the stock you want to remove: " << endl << endl;
		readString("\tStock Symbol: ", key);
		if (aTable.remove(key))
		{
			cout << "Stock successfully removed." << endl;
		}
		else
		{
			cout << "Stock not found..." << endl;
		}
		break;
	case 'd':
		aTable.display();
		break;
	case 'k':
		aTable.monitor();
		break;
	case 'q':
		break;
	default:
		cout << "Bad input" << endl;
	}
}

//function for inserting new home from user
void getStock(data& stock)
{
	char symbol[11];
	char name[101];
	float netAssetValue;
	char date[15];
	float ytdReturn;

	cout << "\nPlease enter information about the Stock: " << endl;
	readString("\tStock Symbol: ", symbol);
	readString("\tCompany Name: ", name);
	netAssetValue = readFloat("\tNet Asset Value: ");
	readString("\tDate: ", date);
	ytdReturn = readFloat("\Year-to-date Return %: ");

	stock.setSymbol(symbol);
	stock.setName(name);
	stock.setNetAssetValue(netAssetValue);
	stock.setDate(date);
	stock.setYtdReturn(ytdReturn);
}

//function to read a string from the user
void readString(char * prompt, char * inputStr)
{
	cout << prompt;
	cin.get(inputStr, 101, '\n');
	cin.ignore(100, '\n');
}

//function to rean an int from the user
int readInt(char * prompt)
{
	int temp;
	cout << prompt;
	cin >> temp;
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}

//function to read a floating point number from the user
float readFloat(char * prompt)
{
	float temp;
	cout << prompt;
	cin >> temp;
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}

//function to pause the program
void pause()
{
	cout << "Press ENTER to continue... " << endl;
	cin.get();
}