#include "collection.h"
#include <iostream>
#include <fstream>
using namespace std;

collection::collection()
{ }

collection::collection(char * fileName)
{
	ifstream in;
	data currData;
	char name[101];
	char phone[15];
	char product[101];
	char events[101];

	//initialize the table with the records in the file
	in.open(fileName);
	if (!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.getline(name, 101, ';');
	while (!in.eof())
	{
		//read in the attributes of current record
		in.getline(phone, 15, ';');
		in.getline(product, 101, ';');
		in.getline(events, 101, '\n');

		//populate current data 
		currData.setName(name);
		currData.setPhone(phone);
		currData.setProduct(product);
		currData.setEvents(events);

		//add current data to the table
		add(currData);

		//start reading in next record 
		in.getline(name, 101, ';');
	}
	in.close();
}

collection::collection(const collection& aVendor)
{

}

const collection& collection::operator= (const collection& aVendor)
{

}

collection::~collection()
{
	vendorTree.~BST;
	productTable.~hashTable;
}

void collection::add(const data& aVendor)
{
	data * ptrItem = new data;
	*ptrItem = aVendor; //deep copy

	vendorTree.add(ptrItem);
	productTable.add(ptrItem);
}
