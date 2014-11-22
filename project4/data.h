#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

class data
{
public:
	//overload stream output operator
	friend ostream& operator<< (ostream& out, const data& vendor);
	//overload assignment operator
	const data& operator= (const data& vendor);

	//default constructor
	data();
	//constructor with parameters
	data(const char * name, const char * phone, const char * product, const char * events);
	//copy constructor
	data(const data& vendor);
	//destructor
	~data();
	
	//accessor functions
	void getName(char * name) const;
	void getPhone(char * phone) const;
	void getProduct(char * product) const;
	void getEvents(char * events) const;
	
	//mutator functions
	void setName(const char * name);
	void setPhone(const char * phone);
	void setProduct(const char * product);
	void setEvents(const char * events);
	
private:
	char * name;
	char * phone;
	char * product;
	char * events;
};

bool operator< (const data& d1, const data& d2);	//overload < on data objects
bool operator== (const data& d1, const data& d2);	//overload == on data objects

#endif