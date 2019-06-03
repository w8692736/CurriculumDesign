#pragma once
#include "CurriculumDesign.h"
#include "Student.h"
#include "LinkedList.h"
using namespace std;

Score Grade();
void title();

class CurriculumDesignList : public LinkedList<CurriculumDesign>
{
public:
	CurriculumDesignList() {}
	~CurriculumDesignList() {}

	LinkedList<CurriculumDesign> GetPass();
	void Mark(string design_name, string author, Score score);
	int GetPassLength();
	int Length();
	string* writeToFile();
};

LinkedList<CurriculumDesign> CurriculumDesignList::GetPass()
{
	LinkedList<CurriculumDesign> design;
	Node<CurriculumDesign> *ptr = first->next;

	while (ptr)
	{
		if (ptr->data.get_design_score() < 60);
		else design.Insert(ptr->data);
		ptr = ptr->next;
	}

	return design;
}

void CurriculumDesignList::Mark(string design_name, string author, Score score)
{
	Node<CurriculumDesign> *ptr = first->next;

	while (ptr)
	{
		if (ptr->data.get_author() == author && ptr->data.get_design_name() == design_name)
		{
			ptr->data.set_design_score(score);
			break;
		}
		ptr = ptr->next;
	}

}

int CurriculumDesignList::GetPassLength()
{
	int length = 0;

	Node<CurriculumDesign> *ptr = first->next;
	while (ptr)
	{
		if (ptr->data.get_design_score() != 0) length++;
		ptr = ptr->next;
	}

	return length;
}

int CurriculumDesignList::Length()
{
	int length = 0;

	Node<CurriculumDesign> *ptr = first->next;
	while (ptr)
	{
		length++;
		ptr = ptr->next;
	}

	return length;
}

string* CurriculumDesignList::writeToFile()
{
	string *str = new string[this->Length()];
	Node<CurriculumDesign> *ptr = first->next;
	int index = 0;

	while (ptr)
	{
		str[index++] = ptr->data.writeToFile();
		ptr = ptr->next;
	}

	return str;
}

