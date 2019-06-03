#pragma once
#include <iostream>
#include <string>
#include "Score.h"
using namespace std;

class CurriculumDesign
{
private:
	string design_name;
	string design_dataStruct;
	string author;
	Score design_score;
public:
	CurriculumDesign();
	CurriculumDesign(string design_name, string design_dataStruct = "NULL",
		string author = "NULL");
	~CurriculumDesign();

	string getInfo();
	string writeToFile();

	//getter & setter
	string get_design_name() { return this->design_name; }
	void set_design_name(string new_name) { this->design_name = new_name; }

	string get_design_dataStruct() { return this->design_dataStruct; }
	void set_design_dataStruct(string new_ds) { this->design_dataStruct = new_ds; }

	string get_author() { return this->author; }
	void set_author(string new_author) { this->author = new_author; }

	double get_design_score() { return this->design_score.get_total(); }
	void set_design_score(string type_score, double new_score);
	void set_design_score(Score score);

	// overload
	friend bool operator<(CurriculumDesign &left, CurriculumDesign &right);
	friend bool operator<(CurriculumDesign &left, double number);
	friend bool operator>(CurriculumDesign &left, CurriculumDesign &right);
	friend bool operator>(CurriculumDesign &left, double number);
	friend bool operator==(CurriculumDesign &left, CurriculumDesign &right);
	friend bool operator==(CurriculumDesign &left, double number);
	friend ostream &operator<<(ostream &out, CurriculumDesign &temp);
};

CurriculumDesign::CurriculumDesign()
{
	this->design_name = "NULL";
	this->design_dataStruct = "NULL";
	this->author = "NULL";
	this->design_score.initialization();
}

CurriculumDesign::CurriculumDesign(string design_name, string design_dataStruct,
	string author)
{
	this->design_name = design_name;
	this->design_dataStruct = design_dataStruct;
	this->author = author;
	this->design_score.initialization();
}

CurriculumDesign::~CurriculumDesign()
{
	;
}

void CurriculumDesign::set_design_score(string type_score, double new_score)
{
	if (type_score == "code_score") this->design_score.set_code_score(new_score);
	else if (type_score == "doc_score") this->design_score.set_doc_score(new_score);
	else if (type_score == "reply_score") this->design_score.set_reply_score(new_score);
}

void CurriculumDesign::set_design_score(Score score)
{
	this->design_score = score;
}

string CurriculumDesign::getInfo()
{
	string info = "";

	info = "->课题名称：《" + this->design_name + "》，作者：" + this->author + "，使用技术：" + this->design_dataStruct;
	if (this->design_score.get_total() != 0)
	{
		info += "\n  分数细则：\n" + this->design_score.getInfo() + "\n";
	}
	else info += "，尚未评分。\n";

	return info;
}

string CurriculumDesign::writeToFile()
{
	string str = "";

	str += this->design_name + " " + this->design_dataStruct + " " + this->author + " ";
	str += to_string(this->design_score.get_code_score()) + " ";
	str += to_string(this->design_score.get_doc_score()) + " ";
	str += to_string(this->design_score.get_reply_score()) + " ";
	str += to_string(this->design_score.get_total()) + " ";

	return str;
}

bool operator<(CurriculumDesign &left, CurriculumDesign &right)
{
	return left.get_design_score() < right.get_design_score();
}

bool operator<(CurriculumDesign &left, double number)
{
	return left.get_design_score() < number;
}

bool operator>(CurriculumDesign &left, CurriculumDesign &right)
{
	return left.get_design_score() > right.get_design_score();
}

bool operator>(CurriculumDesign &left, double number)
{
	return left.get_design_score() > number;
}

bool operator==(CurriculumDesign &left, CurriculumDesign &right)
{
	return ((left.get_design_name() == right.get_design_name()));
}

bool operator==(CurriculumDesign &left, double number)
{
	return left.get_design_score() == number;
}

ostream &operator<<(ostream &out, CurriculumDesign &temp)
{
	out << temp.getInfo() << endl;
	return out;
}
