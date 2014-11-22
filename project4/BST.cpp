#include "BST.h"
#include <iostream>
#include <fstream>
using namespace std;

BST::BST()
   : root(NULL),
     size = 0
{
	// anytime you can, you should do your init like I have here before the curly braces.
}

BST::BST(data * ptrItem)
   : root(NULL), 
     size(0)
{
	// not sure what the point of these are ...
	data * currData;
	char * name;
	char * phone;
	char * product;
	char * events;

	add(currData);
}

BST::BST(const BST& aTree)
  : root(NULL)
    size(0)
{
	// WHOA don't do this are you nutz =p?

	// do something more like this
	// I'm not sure what you're trying to do, you're either doing
	// 1) creating a new BST that references the "SAME" tree as aTree (unlikey)
	// 2) creating a new BST that is a COPY of the tree in aTree (likely)
	// 2 is more likely because if you perform #1 any operation performed on aTree affects your new tree cause
	// they point to the same memory, usually not what you want.
	
	// to peform #1 you'd just set this.root = aTree.root;
	
	// To perform #2, you'd walk aTree's tree and copy each element into "this"'s tree
}

const BST& BST::operator= (const BST& aTree)
{
	if (this != &aTree)
	{
		// Yikes don't do this either!
		// you don't want to destroy the object on the right hand side of the equal sign.
		// thats like saying
		int a = 7;
		int b = a;  // and then you expect "a" to be zero.
	
	
		//copy the tree
		copyTree(root, aTree.root);
	}
	return *this;
}


void BST::copyTree(treeNode*& newRoot /* a pointer to a reference?  Do you hate your sanity? */, treeNode * root)
{
	if (root)
	{
		//copy root
		newRoot = new treeNode(*root);
		copyTree(newRoot->left, root->left);
		copyTree(newRoot->right, root->right);
	}
	else
	{
		newRoot = NULL;
	}
}

BST::~BST()
{
	destroyTree(root);
}

void BST::destroyTree(treeNode *& /* again this is nutter butters */ root)
{
	if (root)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
	
	 // not needed, C++ delete automatically sets pointers to null after delete (not true in plain old C)
	}
}

void BST::add(data * ptrItem)
{
	insert(root, *ptrItem);
}

void BST::insert(treeNode*& root, const data& aData)
{
	if (!root)
	{
		root = new treeNode;
		size++;
	}
	else if (aData < root->item)
	{
		insert(root->left, aData);
	}
	else
	{
		insert(root->right, aData);
	}
}

bool BST::remove(treeNode*& root, char * key)
{
	if (!root)
	{
		return false;
	}
	char name[101];
	root->item.getName(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		deleteNode(root);
		return true;
	}
	else if (temp < 0)
		return remove(root->right, key);
	else
		return remove(root->left, key);
}

void BST::deleteNode(treeNode *& target)
{
	treeNode * temp;

	//a leaf
	if (!target->left && !target->right)
	{
		delete target;
		target = NULL;
	}
	//no left child
	else if (!target->left)
	{
		temp = target;
		target = target->right;
		temp->right = NULL;
		delete temp;
	}
	//no right child
	else if (!target->right)
	{
		temp = target;
		target = target->left;
		temp->left = NULL;
		delete temp;
	}
	//two children
	else
	{
		//find the inorder successor
		treeNode * prev = NULL;
		treeNode * curr = target->right;
		while (curr->left)
		{
			prev = curr;
			curr = curr->left;
		}

		//copy data at curr (the inorder successor) into target
		target->item = curr->item;

		//disconnect curr (the inorder successor)
		if (!prev)
			target->right = curr->right;
		else
			prev->left = curr->right; //the inorder successor could have a right child

		//delete curr (the inorder successor)
		curr->right = NULL;
		delete curr;
	}
	size--;
}

bool BST::retrieve(char * key, data & aData)const
{
	return retrieve(root, key, aData);
}

bool BST::retrieve(treeNode * root, char * key, data& aData) const
{
	if (!root)
	{
		return false;
	}

	char name[100];
	root->item.getName(name);
	int temp = strcmp(name, key);
	if (temp == 0)
	{
		aData = root->item;
		return true;
	}
	else if (temp < 0)
	{
		return retrieve(root->right, key, aData);
	}
	else
	{
		return retrieve(root->left, key, aData);
	}
}

void BST::display(void)const
{
	cout << "Data in the table: " << endl << endl;
	display(root);
}

void BST::display(treeNode * root)const
{
	if (root)
	{
		display(root->left);
		cout << '\t' << root->item << endl;
		display(root->right);
	}
}

int BST::getSize(void) const
{
	return size;
}

void BST::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	writeOut(out, root);
	out.close();
}
void BST::writeOut(ofstream& out, treeNode * root)
{
	if (root)
	{
		char name[101];
		char phone[15];
		char product[101];
		char events[101];
		root->item.getName(name);
		root->item.getPhone(phone);
		root->item.getProduct(product);
		root->item.getEvents(events);
		out << name << ';' << phone << ';' << product << events << '\n';

		writeOut(out, root->left);
		writeOut(out, root->right);
	}
}
