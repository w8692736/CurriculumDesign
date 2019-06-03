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

// 每添加一个学生信息就对应添加一个课题信息，课题的作者即为学生名
// 课题不可删除，每删除一个学生就对应删除一个课题
// 学生的信息最初先添加在链表里，在课题打分后再添加到二叉树中

class Management
{
private:
	BinaryTree<CurriculumDesign> *design; // 存储所有已打分的课设信息
	StudentList *stu_list; // 存储所有学生的信息
	CurriculumDesignList *design_list; // 存储所有课设的信息
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
		先判断是否在stu_list中，若有则执行删除操作。
		先删除design中的信息，删除时应先判断是否存在；
		再删除design_list里对应的信息；
		最后删除stu_list对应的信息。
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

	if (stu_list->Search(stu)) return "修改失败，修改后的学号与现有学号重复";

	stu_list->Edit(stu_ID, new_info);

	return "修改成功！";
}

string Management::Edit(int stu_ID, string type_info, string new_info)
{
	if (!stu_list->Search(Student(stu_ID))) return "修改失败，没有找到该学生";
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
		return "修改失败，没有这种信息类型";

	stu_list->Insert(new_stu);
	design_list->Insert(new_design);

	return "修改成功";
}

void Management::SearchAllStudent()
{
	if (stu_list->Length() == 0)
		cout << "\n\t\t\t<--当前没有可以显示的信息-->\n\n";
	else stu_list->Print();
}

void Management::SearchAllDesign()
{
	if (design_list->Length() == 0)
		cout << "\n\t\t\t<--当前没有可以显示的信息-->\n\n";
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
	// 将分数传递给指定学号的学生的课题，将打分完毕的课题添加进design表中
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

		// 为学生打分
		cout << endl;
		cout << target << endl;
		Score score = Grade();
		Mark(stu_ID, score);

		// 显示打分结果
		title();
		cout << "**评分完毕！**\n";
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
