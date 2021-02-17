#pragma once
#include<iostream>
using namespace std;

enum Color{RED,BLACK};

struct RBTree
{
	int nVal;
	Color nCol;
	RBTree* pFather;
	RBTree* pLeft;
	RBTree* pRight;
};

class CRbtree
{
public:
	CRbtree(void);
	~CRbtree(void);
private:
	void LeftRotate(RBTree* pTree);
	void RightRotate(RBTree* pTree);
	void InsertCase1(RBTree* pTree,RBTree* pFather,RBTree* pUncle);
	void InsertCase2(RBTree* pTree,RBTree* pFather,RBTree* pUncle);
	void InsertCase3(RBTree* pTree,RBTree* pFather,RBTree* pUncle);
	void InsertCase4(RBTree* pTree,RBTree* pFather,RBTree* pUncle);
	RBTree* GetGrandFather(RBTree* pTree);
	RBTree* GetUncle(RBTree* pTree);
	RBTree* GetBro(RBTree* pTree);
	void DeleteCase1(RBTree* pTree,RBTree* pFather,RBTree* pBro);
	void DeleteCase2(RBTree* pTree,RBTree* pFather,RBTree* pBro);
	void DeleteCase3(RBTree* pTree,RBTree* pFather,RBTree* pBro);
	void DeleteCase4(RBTree* pTree,RBTree* pFather,RBTree* pBro);
public:
	RBTree* Find(int val);
	void InsertNode(int val); 
	void DeleteNode(int val);
	void FrontShow(RBTree* pTree);
	RBTree* GetRoot();
private:
	RBTree* pRoot;
};

