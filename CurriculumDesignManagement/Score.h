#pragma once
#include <iostream>
#include <string>
using namespace std;

class Score
{
private:
	double total;
	double code_score;
	double doc_score;
	double reply_score;
public:
	Score();
	Score(double code_score, double doc_score, double reply_score);
	~Score()
	{
		Mark(0, 0, 0);
	}

	// Getter &Setter

	double get_total() { return this->total; }

	double get_code_score() { return this->code_score; }
	void set_code_score(double new_score) { this->code_score = new_score; }

	double get_doc_score() { return this->doc_score; }
	void set_doc_score(double new_score) { this->doc_score = new_score; }

	double get_reply_score() { return this->reply_score; }
	void set_reply_score(double new_score) { this->reply_score = new_score; }

	// calculate
	void Mark(double code_score, double doc_score, double reply_score);
	void Mark(Score score);
	static string doubleToString(double num);
	void initialization();

	// show
	string getInfo();
	void Print();

	// override
	void operator=(const Score &right);
};

Score::Score()
{
	double init = 0;
	this->code_score = init;
	this->doc_score = init;
	this->reply_score = init;
	this->total = this->code_score + this->doc_score + this->reply_score;
}

Score::Score(double code_score, double doc_score, double reply_score)
{
	Mark(code_score, doc_score, reply_score);
}

void Score::Mark(double code_score, double doc_score, double reply_score)
{
	this->code_score = code_score;
	this->doc_score = doc_score;
	this->reply_score = reply_score;
	this->total = this->code_score*0.7 + this->doc_score*0.2 + this->reply_score*0.1;
}

void Score::Mark(Score score)
{
	this->code_score = score.code_score;
	this->doc_score = score.doc_score;
	this->reply_score = score.reply_score;
	this->total = this->code_score*0.7 + this->doc_score*0.2 + this->reply_score*0.1;
}

void Score::initialization()
{
	double init = 0;
	this->code_score = init;
	this->doc_score = init;
	this->reply_score = init;
	this->total = this->code_score + this->doc_score + this->reply_score;
}

string Score::getInfo()
{
	string result = "";

	result += "  代码得分：" + doubleToString(this->code_score);
	result += "，文档得分：" + doubleToString(this->doc_score);
	result += "，答辩得分：" + doubleToString(this->reply_score);
	result += "\n  总得分：" + doubleToString(this->total);

	return result;
}

void Score::Print()
{
	printf("->代码得分：%.2lf，文档得分：%.2lf，答辩得分：%.2lf\n", this->code_score, this->doc_score, this->reply_score);
	printf("  总得分：%.2lf", total);
}

string Score::doubleToString(double num)
{
	return to_string(num);
}

void Score::operator=(const Score &right)
{
	this->code_score = right.code_score;
	this->doc_score = right.doc_score;
	this->reply_score = right.reply_score;
	this->total = this->code_score*0.7 + this->doc_score*0.2 + this->reply_score*0.1;
}
