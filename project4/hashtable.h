#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"

struct hashNode
{
	data * item;
	hashNode * next;
};

class hashTable
{
public:
	hashTable();
	hashTable(const data& aData);
	hashTable(const hashTable& aTable);
	~hashTable();

	const hashTable& operator= (const hashTable& aTable);

	void add(data * ptrItem);
	bool remove(char * key);
	bool retrieve(char * key, data& aData)const;
	void display(void)const;
	void getSize()const;
	int chainSize(int i)const;
	void writeOut(char * fileName);

private:
	hashNode ** table;
	int capacity;
	int * size;
	const static int DEFAULT_CAPACITY = 11;

	void destroyTable();
	void initializeTable();
	void copyTable(int i, const hashTable& aTable);
	int calculateIndex(char * key)const;
};
#endif