#ifndef BST_H
#define BST_H

#include "data.h"

struct TreeNode
{
	data item;
	treeNode * left, *right;
};

class BST
{
public:
	BST();
	BST(data * aData);
	BST(const BST& aTree);
	~BST();

	const BST& operator= (const BST& aTree);

	void add(data * ptrItem);
	bool remove(char * key);
	bool retrieve(char * key, data& aData)const;
	void display(void)const;
	int getSize(void)const;
	void writeOut(char * fileName);

private:
	treeNode * root;
	int size;

	void insert(treeNode*& root, const data& aData);
	bool retrieve(treeNode * root, char * key, data& aData) const;
	bool remove(treeNode*& root, char * key);
	void deleteNode(treeNode *& target);
	void display(treeNode * root) const;
	void destroyTree(treeNode*& root);
	void copyTree(treeNode*& newRoot, treeNode * root);
	void writeOut(ofstream& out, treeNode * root);
};
#endif
