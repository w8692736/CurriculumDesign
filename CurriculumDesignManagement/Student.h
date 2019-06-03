#pragma once
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Student
{
private:
	string stu_name;
	int stu_ID;
	string stu_class;
	string design_name;
public:
	Student();
	Student(int stu_ID, string stu_name = "NULL", string stu_class = "NULL",
		string design_name = "NULL") :
		stu_ID(stu_ID), stu_name(stu_name), stu_class(stu_class),
		design_name(design_name) {}
	Student(const Student &obj);
	~Student();

	// getter & setter
	string get_stu_name() { return this->stu_name; }
	void set_stu_name(string new_name) { this->stu_name = new_name; }

	int get_stu_ID() { return this->stu_ID; }
	void set_stu_ID(int new_ID) { this->stu_ID = new_ID; }

	string get_stu_class() { return this->stu_class; }
	void set_stu_class(string new_class) { this->stu_class = new_class; }

	string get_design_name() { return this->design_name; }
	void set_design_name(string new_name) { this->design_name = new_name; }

	string getInfo();
	string writeToFile();

	// overload
	friend bool operator<(Student &left, Student &right);
	friend bool operator>(Student &left, Student &right);
	friend bool operator==(Student &left, Student &right);
	friend ostream &operator<<(ostream &out, Student &temp);
};


Student::Student()
{
	this->stu_name = "NULL";
	this->stu_ID = -1;
	this->stu_class = "NULL";
	this->design_name = "NULL";
}

Student::Student(const Student &obj)
{
	this->stu_name = obj.stu_name;
	this->stu_ID = obj.stu_ID;
	this->stu_class = obj.stu_class;
	this->design_name = obj.design_name;
}

Student::~Student() {}

string Student::getInfo()
{
	string info = "";

	info = "学号：" + std::to_string(this->stu_ID) + "，姓名：" + this->stu_name + "，班级：" + this->stu_class
		+ "，课题名称：" + this->design_name;

	return info;
}

string Student::writeToFile()
{
	string str = "";

	str += this->stu_class + " " + this->design_name + " "
		+ to_string(this->stu_ID) + " " + this->stu_name;

	return str;
}

bool operator<(Student &left, Student &right)
{
	return left.stu_ID < right.stu_ID;
}

bool operator>(Student &left, Student &right)
{
	return left.stu_ID > right.stu_ID;
}

bool operator==(Student &left, Student &right)
{
	return left.stu_ID == right.stu_ID;
}

ostream &operator<<(ostream &out, Student &temp)
{
	out << temp.getInfo() << endl;
	return out;
}