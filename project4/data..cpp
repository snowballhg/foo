#define _CRT_SECURE_NO_WARNINGS
#include "data.h"
#include <iostream>
#include <iomanip>
using namespace std;

//default constructor
data::data()
{
	name = NULL;
	phone = NULL;
	product = NULL;
	events = NULL;
}

//constructor with parameters
data::data(const char * name, const char * phone, const char * product, const char * events)
{
	setName(name);
	setPhone(phone);
	setProduct(product);
	setEvents(events);
}

//copy constructor
data::data(const data& vendor)
{
	setName(vendor.name);
	setPhone(vendor.phone);
	setProduct(vendor.product);
	setEvents(vendor.events);
}

//overloading the assignment operator
const data& data::operator= (const data& vendor)
{
	//do nothing if self copy
	if (this == &vendor)
		return *this;
	//make this a deep copy of referenced data
	else
	{
		setName(vendor.name);
		setPhone(vendor.phone);
		setProduct(vendor.product);
		setEvents(vendor.events);
		return *this;
	}
}

//destructor
data::~data()
{
	if(name)
		delete[] name;
	if (phone)
		delete[] phone;
	if (product)
		delete[] product;
	if (events)
		delete[] events;
}

//accessor functions
void data::getName(char * name) const
{
	strcpy(name, this->name);
}

void data::getPhone(char * phone) const
{
	strcpy(phone, this->phone);
}

void data::getProduct(char * product) const
{
	strcpy(product, this->product);
}

void data::getEvents(char * events) const
{
	strcpy(events, this->events);
}

//mutator functions
void data::setName(const char * name)
{
	//deallocate if needed
	if (this->name)
		delete[] this->name;

	//set the symbol
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void data::setPhone(const char * phone)
{
	//deallocate if needed
	if (this->phone)
		delete[] this->phone;

	//set the symbol
	this->phone = new char[strlen(phone) + 1];
	strcpy(this->phone, phone);
}

void data::setProduct(const char * product)
{
	//deallocate if needed
	if (this->product)
		delete[] this->product;

	//set the symbol
	this->product = new char[strlen(product) + 1];
	strcpy(this->product, product);
}

void data::setEvents(const char * events)
{
	//deallocate if needed
	if (this->events)
		delete[] this->events;

	//set the symbol
	this->events = new char[strlen(events) + 1];
	strcpy(this->events, events);
}

bool operator< (const data& d1, const data& d2)
{
	char name1[100];
	char name2[100];

	d1.getName(name1);
	d2.getName(name2);

	if (strcmp(name1, name2) < 0)
		return true;
	else
		return false;
}

bool operator== (const data& d1, const data& d2)
{
	char name1[100];
	char name2[100];

	d1.getName(name1);
	d2.getName(name2);

	if (strcmp(name1, name2) == 0)
		return true;
	else
		return false;
}

ostream& operator<< (ostream& out, const data& vendor)
{
	out << vendor.name << '\t' << vendor.phone << '\t' << vendor.product << '\n' << '\t' << vendor.events;
	return out;
}