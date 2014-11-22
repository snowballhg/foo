#include "hashtable.h"
#include <iostream>
using namespace std;

//lots of help at http://stackoverflow.com/a/11373463 for this one

void hashTable::initializeTable()
{
	table = new hashNode*[capacity];
	size = new int[capacity];

	//initialize each head of the individual linked list
	int i;
	for (i = 0; i < capacity; i++)
	{
		table[i] = NULL;
		size[i] = 0;
	}
	//cout << "Table initialized." << endl;
}

hashTable::hashTable() : capacity(DEFAULT_CAPACITY)
{
	initializeTable();
}

hashTable::hashTable(const data& aData) : capacity(DEFAULT_CAPACITY)
{
	initializeTable();

	data * currData;
	char * name;
	char * phone;
	char * product;
	char * events;

	add(currData);
}

hashTable::hashTable(const hashTable& aTable):capacity(aTable.capacity)
{
	table = new hashNode*[capacity];
	size = new int[capacity];

	//copy the array of linked list
	int i;	
	for(i=0; i<capacity; i++)
	{
		//copy each linked list in the array
		if (aTable.table[i] == NULL)
		{
			table[i] = NULL;
			size[i] = 0;
		}
		else
		{
			copyTable(i, aTable);
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
	if(this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTable(); 

		//make *this a deep copy of "aTable"
		table = new hashNode*[capacity];
		capacity = aTable.capacity;
		size = new int[capacity];

		//copy the array of linked list
		int i;	
		for(i=0; i<capacity; i++)
		{
			//copy each linked list in the array
			if (aTable.table[i] == NULL)
			{
				table[i] = NULL;
				size[i] = 0;
			}
			else
			{
				copyTable(i, aTable);
			}
		}		
		return *this;
	}
}

void hashTable::copyTable(int i, const hashTable& aTable)
{
	//copy the first hashNode in current chain
	table[i] = new hashNode; //(aTable.table[i]->item)
	size[i] = aTable.chainSize(i);

	//copy the rest of the chain
	hashNode * srcHashNode = aTable.table[i]->next;
	hashNode * dstHashNode = table[i];
	while (srcHashNode)
	{
		dstHashNode->next = new hashNode; //(srcNode->item)
		dstHashNode = dstHashNode->next;
		srcHashNode = srcHashNode->next;
	}
	dstHashNode->next = NULL;
}

void hashTable::destroyTable ()
{
	//delete each chain
	int i;
	for(i=0; i<capacity; i++)
	{
		hashNode * head = table[i];
		hashNode * curr;
		while(head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}

	//delete the array
	delete[] table;
	delete[] size;
}
hashTable::~hashTable()
{
	destroyTable(); 
}

void hashTable::add(data * ptrItem)
{
	//calculate the insertion position (the index of the array)
	char key[100];
	ptrItem->getProduct(key);
	int index = calculateIndex(key);

	//create a new hashNode to hold data
	hashNode * newHashNode = new hashNode;

	//insert the new hashNode at the beginning of the linked list
	if (table[index] == NULL)
	{
		newHashNode->next = table[index];
		table[index] = newHashNode;
		size[index]++;
	}
	else
	{
		newHashNode->next = table[index];
		table[index] = newHashNode;
		size[index]++;
	}
}

bool hashTable::remove (char * key)
{
	//calculate the removal position (the index of the array)
	int index = calculateIndex(key);	

	//search for the data to be removed in the chain (linked list)
	hashNode * curr = table[index];
	hashNode * prev = NULL;
	char id[100];
	while (curr)
	{
		curr->item->getProduct(id);
		if(strcmp(key, id) == 0)
		{
			//find match and remove the hashNode
			if (!prev)
			{
				table[index] = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}

			curr->next = NULL;
			delete curr;
			size[index]--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

bool hashTable::retrieve (char * key, data & aData)const
{
	//calculate the retrieval position (the index of the array)
	int index = calculateIndex(key);

	//search for the data in the chain (linked list)
	hashNode * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item->getProduct(id);
		if(strcmp(key, id) == 0)
		{
			//find match and return the data
			curr->item->setName(aData.getName);
			curr->item->setPhone(aData.getPhone);
			curr->item->setProduct(aData.getProduct);
			curr->item->setEvents(aData.getEvents);
			return true;
		}
		else
		{
			curr = curr->next;
		}
	}

	//data is not in the table
	return false;
}

void hashTable::display (void)const
{
	int i;
	hashNode * curr;

	cout << "Data in the table: " << endl << endl;
	for(i=0; i<capacity; i++)
	{
		for (curr = table[i]; curr; curr = curr->next)
		{
			//we can use << on data object because we overload << in the data class
			cout << '\t' << curr->item << endl;
		}
	}
}

void hashTable::getSize() const
{
	int i;
	for (i = 0; i < capacity; i++)
	{
		cout << "Chain - " << i << " - has " << size[i] << " hashNodes";
	}
}

int hashTable::chainSize(int i) const
{
	return size[i];
}

int hashTable::calculateIndex (char * key)const
{
	char * c = key;
	int total = 0;
	while(*c)
	{
		total += static_cast<int>(*c);
		c++;
	}

	return total%capacity;
}