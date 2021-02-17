#include "Rbtree.h"


CRbtree::CRbtree(void)
{
	this->pRoot = NULL;
}


CRbtree::~CRbtree(void)
{
}

void CRbtree::LeftRotate(RBTree* pTree)
{
	RBTree* pFather = NULL;
	RBTree* pRightSon = NULL;
	RBTree* pSonSon = NULL;
	pRightSon = pTree->pRight;
	if(!pTree->pFather)
		this->pRoot = pRightSon;
	else
		pFather = pTree->pFather;

	if(pRightSon)
		pSonSon = pRightSon->pLeft;

	//三子
	if(pFather)
	{
		if(pFather->pLeft == pTree)
			pFather->pLeft = pRightSon;
		else if(pFather->pRight == pTree)
			pFather->pRight = pRightSon;
	}
	pTree->pRight = pSonSon;
	pRightSon->pLeft = pTree;
	//三父
	if(pSonSon)
		pSonSon->pFather = pTree;
	pRightSon->pFather = pFather;
	pTree->pFather = pRightSon;

}

void CRbtree::RightRotate(RBTree* pTree)
{
	RBTree* pFather = NULL;
	RBTree* pLeftSon = NULL;
	RBTree* pSonSon = NULL;
	pLeftSon = pTree->pLeft;
	if(!pTree->pFather)
		this->pRoot = pLeftSon;
	else
		pFather = pTree->pFather;

	if(pLeftSon)
		pSonSon = pLeftSon->pRight;

	//三子
	if(pFather)
	{
		if(pFather->pLeft == pTree)
			pFather->pLeft = pLeftSon;
		else if(pFather->pRight == pTree)
			pFather->pRight = pLeftSon;
	}
	pTree->pLeft = pSonSon;
	pLeftSon->pRight = pTree;
	//三父
	if(pSonSon)
		pSonSon->pFather = pTree;
	pLeftSon->pFather = pFather;
	pTree->pFather = pLeftSon;
}

RBTree* CRbtree::GetGrandFather(RBTree* pTree)
{
	if(!pTree || !pTree->pFather)
		return NULL;
	return pTree->pFather->pFather;
}

RBTree* CRbtree::GetUncle(RBTree* pTree)
{
	if(!pTree || !pTree->pFather || !GetGrandFather(pTree))
		return NULL;

	if(GetGrandFather(pTree)->pLeft == pTree->pFather)
		return GetGrandFather(pTree)->pRight;
	else if(GetGrandFather(pTree)->pRight == pTree->pFather)
		return GetGrandFather(pTree)->pLeft;

	return NULL;
}

void CRbtree::FrontShow(RBTree* pTree)
{
	if(!pTree)
		return ;
	cout << pTree->nVal << " " << pTree->nCol << " ";
	if(pTree->pLeft)
		cout << pTree->pLeft->nVal << " "; 
	else
		cout << "NULL ";

	if(pTree->pRight)
		cout << pTree->pRight->nVal << endl;
	else
		cout << "NULL " << endl;

	FrontShow(pTree->pLeft);
	FrontShow(pTree->pRight);
}

RBTree* CRbtree::GetRoot()
{
	return this->pRoot;
}

void CRbtree::InsertNode(int val)
{
	if(!this->pRoot)
	{
		this->pRoot = new RBTree;
		this->pRoot->nVal = val;
		this->pRoot->nCol = BLACK;
		this->pRoot->pFather = NULL;
		this->pRoot->pLeft = NULL;
		this->pRoot->pRight = NULL;
		return;
	}

	RBTree* pTemp = this->pRoot;
	while(pTemp)
	{
		if(pTemp->nVal > val)
		{
			if(pTemp->pLeft)
				pTemp = pTemp->pLeft;
			else
			{
				pTemp->pLeft = new RBTree;
				pTemp->pLeft->nVal = val;
				pTemp->pLeft->nCol = RED;
				pTemp->pLeft->pFather = pTemp;
				pTemp->pLeft->pLeft = NULL;
				pTemp->pLeft->pRight = NULL;
				pTemp = pTemp->pLeft;
				break;
			}
		}
		else if(pTemp->nVal < val)
		{
			if(pTemp->pRight)
				pTemp = pTemp->pRight;
			else
			{
				pTemp->pRight = new RBTree;
				pTemp->pRight->nVal = val;
				pTemp->pRight->nCol = RED;
				pTemp->pRight->pFather = pTemp;
				pTemp->pRight->pLeft = NULL;
				pTemp->pRight->pRight = NULL;
				pTemp = pTemp->pRight;
				break;
			}
		}
	}
	InsertCase1(pTemp,GetGrandFather(pTemp),GetUncle(pTemp));
}

void CRbtree::InsertCase1(RBTree* pTree,RBTree* pGrand,RBTree* pUncle)
{
	if(!pTree->pFather)
	{
		pTree->nCol = BLACK;
		return ;
	}
	if(pTree->pFather->nCol == BLACK)
		return ;

	InsertCase2(pTree,pGrand,pUncle);
}

void CRbtree::InsertCase2(RBTree* pTree,RBTree* pGrand,RBTree* pUncle)
{
	if(pTree->pFather->nCol == RED && pUncle && pUncle->nCol == RED)
	{
		pTree->pFather->nCol = BLACK;
		pUncle->nCol = BLACK;
		pGrand->nCol = RED;
		InsertCase1(pGrand,GetGrandFather(pGrand),GetUncle(pGrand));
		return ;
	}
	InsertCase3(pTree,pGrand,pUncle);
}

void CRbtree::InsertCase3(RBTree* pTree,RBTree* pGrand,RBTree* pUncle)
{
	// <
	if(pGrand->pLeft == pTree->pFather && pTree->pFather->pRight == pTree)
	{
		LeftRotate(pTree->pFather);
		pTree = pTree->pLeft;
	}
	else if(pGrand->pRight == pTree->pFather && pTree->pFather->pLeft == pTree)  // >
	{
		RightRotate(pTree->pFather);
		pTree = pTree->pRight;
	}
	InsertCase4(pTree,pGrand,pUncle);
}

void CRbtree::InsertCase4(RBTree* pTree,RBTree* pGrand,RBTree* pUncle)
{
	// /
	if(pGrand->pLeft == pTree->pFather && pTree->pFather->pLeft == pTree)
	{
		pTree->pFather->nCol = BLACK;
		pGrand->nCol = RED;
		RightRotate(pGrand);
	}
	else if(pGrand->pRight == pTree->pFather && pTree->pFather->pRight == pTree)
	{
		pTree->pFather->nCol = BLACK;
		pGrand->nCol = RED;
		LeftRotate(pGrand);
	}
}

RBTree* CRbtree::Find(int val)
{
	RBTree* pTree = this->pRoot;
	while(pTree)
	{
		if(pTree->nVal == val)
			return pTree;
		else if(pTree->nVal > val)
		{
			pTree = pTree->pLeft;
		}
		else if(pTree->nVal < val)
		{
			pTree = pTree->pRight;
		}
	}

	return NULL;
}

RBTree* CRbtree::GetBro(RBTree* pTree)
{
	if(!pTree || !pTree->pFather)
		return NULL;
	if(pTree->pFather->pLeft == pTree)
		return pTree->pFather->pRight;
	else if(pTree->pFather->pRight == pTree)
		return pTree->pFather->pLeft;

	return NULL;
}

void CRbtree::DeleteNode(int val)
{
	RBTree* pDel = Find(val);
	if(!pDel)
		return ;
	// 两个孩子的情况
	if(pDel->pLeft && pDel->pRight)
	{
		RBTree* pTemp = pDel->pLeft;
		while(pTemp)
		{
			if(pTemp->pRight)
				pTemp = pTemp->pRight;
			else
			{
				pDel->nVal = pTemp->nVal ;
				pDel = pTemp;
				break;
			}
		}
	}

	// 一个孩子的情况
	// 根
	if(!pDel->pFather)
	{
		RBTree* pSon = pDel->pLeft ? pDel->pLeft : pDel->pRight;
		if(pSon)
		{
			pSon->nCol = BLACK;
			pSon->pFather = NULL;
			this->pRoot = pSon;
			delete pDel;
			pDel = 0;
			return ;
		}
	}
	// 红色节点
	if(pDel->nCol == RED)
	{
		RBTree* pSon = pDel->pLeft ? pDel->pLeft:pDel->pRight;
		if(pDel->pFather->pLeft == pDel)
			pDel->pFather->pLeft = pSon;
		else if(pDel->pFather->pRight == pDel)
			pDel->pFather->pRight = pSon;

		if(pSon)
			pSon->pFather = pDel->pFather;

		delete pDel;
		pDel = 0;
		return ;
	}

	// 黑色节点
	if(pDel->nCol == BLACK)
	{
		RBTree* pSon = pDel->pLeft ? pDel->pLeft:pDel->pRight;
		if(pSon)
		{
			pSon->nCol = BLACK;
			if(pDel->pFather->pLeft == pDel)
				pDel->pFather->pLeft = pSon;
			else if(pDel->pFather->pRight == pDel)
				pDel->pFather->pRight = pSon;

			pSon->pFather = pDel->pFather;
			delete pDel;
			pDel = 0;
			return ;
		}
	}

	RBTree* pBro = GetBro(pDel);
	if(pDel->pFather)
	{
		if(pDel->pFather->pLeft == pDel)
			pDel->pFather->pLeft = NULL;
		else if(pDel->pFather->pRight == pDel)
			pDel->pFather->pRight = NULL;
	}

	DeleteCase1(pDel,pDel->pFather,pBro);
	delete pDel;
	return ;
}

void CRbtree::DeleteCase1(RBTree* pTree,RBTree* pFather,RBTree* pBro)
{
	if(!pFather)
	{
		pTree->nCol = BLACK;
		if(!pTree->pLeft && !pTree->pRight)
			pRoot = NULL;
		return ;
	}
	if(pBro && pBro->nCol == RED)
	{
		pBro->nCol = BLACK;
		pFather->nCol = RED;
		if(pFather->pLeft == pBro)
			RightRotate(pFather);
		else if(pFather->pRight == pBro)
			LeftRotate(pFather);
		return ;
	}
	DeleteCase2(pTree,pFather,pBro);
}

void CRbtree::DeleteCase2(RBTree* pTree,RBTree* pFather,RBTree* pBro)
{
	if((!pBro->pLeft && !pBro->pRight) || (pBro->pLeft && pBro->pRight && pBro->pLeft->nCol == BLACK && pBro->pRight->nCol == BLACK))
	{
		if(pFather->nCol == RED)
		{
			pFather->nCol = BLACK;
			pBro->nCol = RED;
			return ;
		}
		else if(pFather->nCol == BLACK)
		{
			pBro->nCol = RED;
			DeleteCase1(pFather,pFather->pFather,GetBro(pFather));
			return ;
		}
	}
	DeleteCase3(pTree,pFather,pBro);
}

void CRbtree::DeleteCase3(RBTree* pTree,RBTree* pFather,RBTree* pBro)
{
	// <
	if(pFather->pLeft == pBro && pBro->pRight && pBro->pRight->nCol == RED)
	{
		pBro->nCol = RED;
		pBro->pRight->nCol = BLACK;
		LeftRotate(pBro);
		pBro = pBro->pFather;
	}
	else if(pFather->pRight == pBro && pBro->pLeft && pBro->pLeft->nCol == RED) // >
	{
		pBro->nCol = RED;
		pBro->pLeft->nCol = BLACK;
		RightRotate(pBro);
		pBro = pBro->pFather;
	}
	DeleteCase4(pTree,pFather,pBro);
}

void CRbtree::DeleteCase4(RBTree* pTree,RBTree* pFather,RBTree* pBro)
{
	// /
	if(pFather->pLeft == pBro && pBro->pLeft && pBro->pLeft->nCol == RED)
	{
		pBro->nCol = pFather->nCol;
		pBro->pLeft->nCol = BLACK;
		pFather->nCol = BLACK;
		RightRotate(pFather);
	}
	else if(pFather->pRight == pBro && pBro->pRight && pBro->pRight->nCol == RED)
	{
		pBro->nCol = pFather->nCol;
		pBro->pRight->nCol = BLACK;
		pFather->nCol = BLACK;
		LeftRotate(pFather);
	}
}