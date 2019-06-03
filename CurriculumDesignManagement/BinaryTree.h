#pragma once
#include <iostream>
#include <string>
using namespace std;


// Need [DataType] overload "<", ">", "<<" and "==";

template<class DataType>
struct BinaryNode
{
	DataType data;
	BinaryNode<DataType> *leftNode, *rightNode;
	BinaryNode<DataType>() { leftNode = rightNode = nullptr; }
	BinaryNode(DataType &element)
	{
		leftNode = rightNode = nullptr;
		data = element;
	};
};

template<class DataType>
class BinaryTree
{
private:
	BinaryNode<DataType> * root;
	DataType findMin(BinaryNode<DataType> *bt);
	void Release(BinaryNode<DataType> *bt);
	void PreOrder(BinaryNode<DataType> *bt)const;
	void InOrder(BinaryNode<DataType> *bt)const;
	void PostOrder(BinaryNode<DataType> *bt)const;
	BinaryNode<DataType>* isFind(DataType &element, BinaryNode<DataType> *bt);
	void Delete(DataType &element, BinaryNode<DataType> *bt);
	int length;
public:
	BinaryTree() { length = 0; root = NULL; }
	~BinaryTree() { Release(root); }
	void Release() { this->Release(root); }
	void PreOrder();
	void InOrder();
	void PostOrder();
	void Insert(DataType &element);
	DataType isFind(DataType &element);
	void Delete(DataType &element);

	int Length() { return this->length; }
};

template<class DataType>
void BinaryTree<DataType>::Release(BinaryNode<DataType> *bt)
{
	if (bt != NULL)
	{
		Release(bt->leftNode);
		Release(bt->rightNode);
		delete bt;
	}
}

template<class DataType>
void BinaryTree<DataType>::PreOrder(BinaryNode<DataType> *bt)const
{
	if (bt == nullptr) return;
	cout << bt->data << endl;
	PreOrder(bt->leftNode);
	PreOrder(bt->rightNode);
}

template<class DataType>
void BinaryTree<DataType>::InOrder(BinaryNode<DataType> *bt)const
{
	if (bt == NULL) return;
	InOrder(bt->leftNode);
	cout << bt->data << endl;
	InOrder(bt->rightNode);
}

template<class DataType>
void BinaryTree<DataType>::PostOrder(BinaryNode<DataType> *bt)const
{
	if (bt == NULL) return;
	PostOrder(bt->leftNode);
	PostOrder(bt->rightNode);
	cout << bt->data << endl;
}

template<class DataType>
void BinaryTree<DataType>::Insert(DataType &element)
{
	this->length++;

	// 初始化ptr
	BinaryNode<DataType> *ptr = new BinaryNode<DataType>(element);
	ptr->data = element;
	ptr->leftNode = ptr->rightNode = NULL;

	if (root == nullptr)
	{
		/*cout << "root\n";
		system("pause");*/
		root = ptr;
		return;
	}

	BinaryNode<DataType> *tNode = NULL, *tRoot = root;
	while (tRoot)
	{
		tNode = tRoot;
		tRoot = (element < tRoot->data) ? tRoot->leftNode : tRoot->rightNode;
	}
	if (element < tNode->data)
	{
		tNode->leftNode = ptr;
		/*cout << "left\n";
		system("pause");*/
	}
	else if (element > tNode->data)
	{
		tNode->rightNode = ptr;
		/*cout << "right\n";
		system("pause");*/
	}
	else
	{
		/*cout << "this\n";
		system("pause");*/
		tNode->data = ptr->data;
	}
}

// isFInd
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::isFind(DataType &element, BinaryNode<DataType> *bt)
{
	if (bt == nullptr && bt != root)
		return nullptr;
	if (element > bt->data) //查找右子树  
		return isFind(element, bt->rightNode);
	else if (element < bt->data) //查找左子树  
		return isFind(element, bt->leftNode);
	else
		return bt;
}

template<class DataType>
DataType BinaryTree<DataType>::isFind(DataType &element)
{
	BinaryNode<DataType> *temp = this->isFind(element, root);
	return temp->data;
}

// Delete
template<class DataType>
void BinaryTree<DataType>::Delete(DataType &element, BinaryNode<DataType> *bt)
{
	BinaryNode<DataType> *ptr = root, *parent = nullptr, *s = nullptr;

	if (!ptr) return;

	if (ptr->data == element) // 找到要删除的节点
	{
		// 被删节点为叶节点
		if (!ptr->rightNode && !ptr->leftNode)
			root = nullptr;

		// 只有一个左节点
		else if (!ptr->rightNode && ptr->leftNode)
			root = ptr->leftNode;

		// 只有一个右节点
		else if (!ptr->leftNode && ptr->rightNode)
			root = ptr->rightNode;

		//左右节点都不空
		else
		{
			// 令s=ptr->rightNode，找右子树的最小节点替换ptr
			s = ptr->rightNode;

			if (!s->leftNode) // s就是右子树的最小节点
				s->leftNode = ptr->leftNode;
			else
			{
				// 从左子树中找到最小节点
				while (s->leftNode)
				{
					parent = s;
					s = s->leftNode;
				}
				parent->leftNode = s->rightNode;
				s->leftNode = ptr->leftNode;
				s->rightNode = ptr->rightNode;
			}
			root = s;
		}
		free(ptr);
	}
	else if (element > ptr->data) //向右找
		Delete(element, ptr->rightNode);
	else if (element < ptr->data) //向左找
		Delete(element, ptr->leftNode);

}

template<class DataType>
void BinaryTree<DataType>::Delete(DataType &element)
{
	this->length--;
	this->Delete(element, root);
}

template<class DataType>
DataType BinaryTree<DataType>::findMin(BinaryNode<DataType> *bt)
{
	if (nullptr != bt)
	{
		while (nullptr != bt->leftNode)
			bt = bt->leftNode;
	}
	return bt->data;
}

template<class DataType>
void BinaryTree<DataType>::PreOrder()
{
	if (root == nullptr) cout << "\n\t\t\t\t<--当前没有可供显示的信息-->\n\n";
	else PreOrder(root);
}

template<class DataType>
void BinaryTree<DataType>::InOrder()
{
	if (root == nullptr) cout << "\n\t\t\t\t<--当前没有可供显示的信息-->\n\n";
	else InOrder(root);
}

template<class DataType>
void BinaryTree<DataType>::PostOrder()
{
	if (root == nullptr) cout << "\n\t\t\t\t<--当前没有可供显示的信息-->\n\n";
	else PostOrder(root);
}