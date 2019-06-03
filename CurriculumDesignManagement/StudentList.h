#pragma once

#include "LinkedList.h"
#include "Student.h"
#include <string>
#include <iostream>
using namespace std;

class StudentList : public LinkedList<Student>
{
public:
	StudentList() {}
	~StudentList() {}

	void Edit(int stu_ID, int new_info);
	int* getAllID();
	int Length();
	string* writeToFile();

};

void StudentList::Edit(int stu_ID, int new_info)
{
	Node<Student> *ptr = first->next;
	while (ptr)
	{
		if (ptr->data.get_stu_ID() == stu_ID)
		{
			ptr->data.set_stu_ID(new_info);
			break;
		}
		ptr = ptr->next;
	}
}

int* StudentList::getAllID()
{
	Node<Student> *ptr = first->next;
	int *arr = new int[this->length];
	int index = 0;

	while (ptr)
	{
		arr[index++] = ptr->data.get_stu_ID();
		ptr = ptr->next;
	}

	return arr;
}

string* StudentList::writeToFile()
{
	string *str = new string[this->Length()];
	Node<Student> *ptr = first->next;
	int index = 0;

	while (ptr)
	{
		str[index++] = ptr->data.writeToFile();
		ptr = ptr->next;
	}

	return str;
}

int StudentList::Length()
{
	int length = 0;

	Node<Student> *ptr = first->next;
	while (ptr)
	{
		length++;
		ptr = ptr->next;
	}
	return length;
}
