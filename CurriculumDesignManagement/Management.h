#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include "BinaryTree.h"
#include "Student.h"
#include "StudentList.h"
#include "CurriculumDesign.h"
#include "CurriculumDesignList.h"
#include "LinkedList.h"

using namespace std;

void title();

// ÿ���һ��ѧ����Ϣ�Ͷ�Ӧ���һ��������Ϣ����������߼�Ϊѧ����
// ���ⲻ��ɾ����ÿɾ��һ��ѧ���Ͷ�Ӧɾ��һ������
// ѧ������Ϣ����������������ڿ����ֺ�����ӵ���������

class Management
{
private:
	BinaryTree<CurriculumDesign> *design; // �洢�����Ѵ�ֵĿ�����Ϣ
	StudentList *stu_list; // �洢����ѧ������Ϣ
	CurriculumDesignList *design_list; // �洢���п������Ϣ
public:
	Management();
	~Management();

	void Insert(Student &stu, CurriculumDesign &design);
	bool Delete(int stu_ID);
	string Edit(int stu_ID, int new_info);
	string Edit(int stu_ID, string type_info, string new_info);
	void SearchAllStudent();
	void SearchAllDesign();
	bool Search(int stu_ID);
	bool Search(string design_name);

	Student Get(int stu_ID);
	CurriculumDesign Get(string design_name);
	string* InfoToFile_Design();
	string* InfoToFile_Student();
	int numOfStudent() { return stu_list->Length(); }
	int numOfDesign() { return design_list->Length(); }
	int numOfMarkedDesign();
	int numOfPassDesign();
	void Mark(int stu_ID, Score score);
	void MultipleMark();
	void RankingList();

	void ReadFile(string *str_stu, string *str_design);
};

Management::Management()
{
	design = new BinaryTree<CurriculumDesign>;
	stu_list = new StudentList;
	design_list = new CurriculumDesignList;
}

Management::~Management()
{
	design_list->~CurriculumDesignList();
	stu_list->~StudentList();
	design->~BinaryTree();
}

void Management::Insert(Student &stu, CurriculumDesign &design)
{
	stu_list->Insert(stu);
	design_list->Insert(design);
}

bool Management::Delete(int stu_ID)
{
	/*
		���ж��Ƿ���stu_list�У�������ִ��ɾ��������
		��ɾ��design�е���Ϣ��ɾ��ʱӦ���ж��Ƿ���ڣ�
		��ɾ��design_list���Ӧ����Ϣ��
		���ɾ��stu_list��Ӧ����Ϣ��
	*/
	if (!stu_list->Search(Student(stu_ID))) return false;
	Student del_stu = stu_list->Get(Student(stu_ID));
	CurriculumDesign del_design = design_list->Get(CurriculumDesign(del_stu.get_design_name()));

	// test
	cout << del_stu.getInfo() << endl;
	cout << del_design.getInfo() << endl;

	if (del_design.get_design_score() != 0) design->Delete(del_design);
	design_list->Delete(del_design);
	stu_list->Delete(del_stu);

	return true;
}

int Management::numOfMarkedDesign()
{
	return design_list->GetPassLength();
}

string Management::Edit(int stu_ID, int new_info)
{
	Student stu(new_info);

	if (stu_list->Search(stu)) return "�޸�ʧ�ܣ��޸ĺ��ѧ��������ѧ���ظ�";

	stu_list->Edit(stu_ID, new_info);

	return "�޸ĳɹ���";
}

string Management::Edit(int stu_ID, string type_info, string new_info)
{
	if (!stu_list->Search(Student(stu_ID))) return "�޸�ʧ�ܣ�û���ҵ���ѧ��";
	Student new_stu = stu_list->Get(Student(stu_ID));
	CurriculumDesign new_design = design_list->Get(CurriculumDesign(new_stu.get_design_name()));
	stu_list->Delete(new_stu);
	design_list->Delete(new_design);

	if (type_info == "stu_name")
	{
		new_stu.set_stu_name(new_info);
		new_design.set_author(new_info);
	}
	else if (type_info == "stu_class")
		new_stu.set_stu_class(new_info);
	else if (type_info == "design_name")
	{
		new_stu.set_design_name(new_info);
		new_design.set_design_name(new_info);
	}
	else if (type_info == "dataStruct")
		new_design.set_design_dataStruct(new_info);
	else
		return "�޸�ʧ�ܣ�û��������Ϣ����";

	stu_list->Insert(new_stu);
	design_list->Insert(new_design);

	return "�޸ĳɹ�";
}

void Management::SearchAllStudent()
{
	if (stu_list->Length() == 0)
		cout << "\n\t\t\t<--��ǰû�п�����ʾ����Ϣ-->\n\n";
	else stu_list->Print();
}

void Management::SearchAllDesign()
{
	if (design_list->Length() == 0)
		cout << "\n\t\t\t<--��ǰû�п�����ʾ����Ϣ-->\n\n";
	else design_list->Print();
}

bool Management::Search(int stu_ID)
{
	return stu_list->Search(Student(stu_ID));
}

bool Management::Search(string design_name)
{
	return design_list->Search(CurriculumDesign(design_name));
}

Student Management::Get(int stu_ID)
{
	Student temp(stu_ID);
	return stu_list->Get(temp);
}

CurriculumDesign Management::Get(string design_name)
{
	CurriculumDesign temp(design_name);
	return design_list->Get(temp);
}

string* Management::InfoToFile_Design()
{
	string *info = design_list->writeToFile();
	return info;
}

string* Management::InfoToFile_Student()
{
	string *info = stu_list->writeToFile();
	return info;
}

int Management::numOfPassDesign()
{
	LinkedList<CurriculumDesign> obj = design_list->GetPass();
	return obj.Length();
}

void Management::Mark(int stu_ID, Score score)
{
	// ���������ݸ�ָ��ѧ�ŵ�ѧ���Ŀ��⣬�������ϵĿ�����ӽ�design����
	Student stu_target = this->Get(stu_ID);
	CurriculumDesign  design_target = this->Get(stu_target.get_design_name());

	design_list->Mark(design_target.get_design_name(), design_target.get_author(), score);
	design_target = this->Get(stu_target.get_design_name());
	design->Insert(design_target);

}

void Management::MultipleMark()
{
	int *ID = stu_list->getAllID();
	int length = stu_list->Length();

	for (int i = 0; i < length; i++)
	{
		title();
		int stu_ID = ID[i];
		Student target = Get(stu_ID);
		CurriculumDesign design_target = Get(target.get_design_name());
		if (design_target.get_design_score() != 0) continue;

		// Ϊѧ�����
		cout << endl;
		cout << target << endl;
		Score score = Grade();
		Mark(stu_ID, score);

		// ��ʾ��ֽ��
		title();
		cout << "**������ϣ�**\n";
		target = Get(stu_ID);
		design_target = Get(target.get_design_name());
		cout << target << endl;
		cout << design_target << endl;
		system("pause");
	}
}

void Management::RankingList()
{
	//design->PreOrder();
	design->InOrder();
	//design->PostOrder();
}

void Management::ReadFile(string *str_stu, string *str_design)
{
	int length_stu = str_stu->length(), length_design = str_design->length();

	for (int i = 0; i < length_stu; i++)
	{
		string stu_class, design_name, stu_ID, stu_name;
		istringstream iss(str_stu[i]);
		iss >> stu_class >> design_name >> stu_ID >> stu_name;

		Student stu(atoi(stu_ID.data()), stu_name, stu_class, design_name);
		stu_list->Insert(stu);
	}

	for (int i = 0; i < length_design; i++)
	{
		string design_dataStruct, design_name, author;
		string score_code, score_doc, score_reply, score_total;
		istringstream iss(str_design[i]);
		iss >> design_name >> design_dataStruct >> author;
		iss >> score_code >> score_doc >> score_reply >> score_total;

		CurriculumDesign temp(design_name, design_dataStruct, author);
		Score score(atof(score_code.data()), atof(score_doc.data()), atof(score_reply.data()));
		temp.set_design_score(score);
		design_list->Insert(temp);
		if (score.get_total() != 0)
			design->Insert(temp);
	}
}
