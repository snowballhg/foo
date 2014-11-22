#ifndef COLLECTION_H
#define COLLECTION_H

#include "data.h"
#include "bst.h"
#include "hashtable.h"

class collection
{
public:
	collection();
	collection(char * fileName);
	collection(const collection& aVendor);
	~collection();

	const collection& operator= (const collection& aVendor);

	void add(const data& aVendor);
	bool remove(char * vendorName);
	bool retrieve(char * vendorName, data& aVendor);
	bool retrieve(char * productType, data * vendors);
	void displayByName();
	void displayByProduct();

private:
	BST vendorTree;
	hashTable productTable;

};
#endif