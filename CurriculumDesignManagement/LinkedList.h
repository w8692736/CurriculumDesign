#pragma once
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

template<class DataType>
class LinkedList
{
protected:

	template<class DataType>
	struct Node
	{
		DataType data;
		Node<DataType> *next;
		Node() { next = NULL; }
		Node(DataType data) { this->data = data; next = NULL; }
	};

	Node<DataType> * first;
	int length;

public:
	LinkedList()
	{
		first = new Node<DataType>;
		length = 0;
	}
	~LinkedList()
	{
		/*length = 0;
		Node<DataType> *ptr = new Node<DataType>;
		while (first!=nullptr)
		{
			ptr = first;
			first = first->next;
			delete ptr;
		}*/
	}

	bool Insert(DataType data)
	{
		if (this->Search(data)) return false; // 不添加重复信息

		Node<DataType> *newPtr = new Node<DataType>(data);
		newPtr->next = first->next;
		first->next = newPtr;

		length++;
		return true;
	}

	bool Delete(DataType data)
	{
		if (!this->Search(data)) return false;

		Node<DataType> *ptr = first;
		while (ptr->next != NULL)
		{
			if (ptr->next->data == data)
			{
				Node<DataType> *del = ptr->next;
				ptr->next = del->next;
				delete del;
				length--;
				break;
			}
			else ptr = ptr->next;
		}

		return true;
	}

	bool Search(DataType data)
	{
		Node<DataType> *ptr = first->next;
		while (ptr != NULL)
		{
			if (ptr->data == data) return true;
			ptr = ptr->next;
		}

		return false;
	}

	DataType Get(DataType data)
	{
		DataType target;
		Node<DataType> *ptr = first->next;
		while (ptr != NULL)
		{
			if (ptr->data == data)
			{
				target = ptr->data;
				break;
			}
			ptr = ptr->next;
		}

		return target;
	}


	bool Edit(DataType data)
	{
		Node<DataType> *newPtr = new Node<DataType>(data);

		Node<DataType> *ptr = first->next;
		while (ptr&&ptr->next->data != data)
			ptr = ptr->next;
		ptr->next->data = data;

		return true;
	}

	int Length()
	{
		return this->length;
	}

	void Print()
	{
		Node<DataType> *ptr = first->next;
		while (ptr != NULL)
		{
			cout << ptr->data;
			ptr = ptr->next;
		}
	}
};



