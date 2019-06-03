// CurriculumDesignManagement.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "BinaryTree.h"
#include "CurriculumDesign.h"
#include "Management.h"
#include "Student.h"
#include "Score.h"
#include "MyFile.h"
using namespace std;

Management admin;

void title(); // 标题
void footer(); // 结束语
void menu(); // 菜单
void Insert(); // 添加信息
void Delete(); // 删除信息
void Edit(); // 修改信息
void Search(); // 查询信息
int Calc_numOfStudent() { return admin.numOfStudent(); } // 统计学生总人数
int Calc_numOfMarkedDesign() { return admin.numOfMarkedDesign(); } // 统计已打分的课程数
int Calc_numOfPassDesign() { return admin.numOfPassDesign(); } // 统计及格人数
void SimpleMark();
void MultipleMark();
Score Grade();
void Save(); // 保存文件
void Load(); // 读取文件
bool isNumber(string str); // 判断str是否为纯数字串

int main()
{
	string cmd = "";

	do
	{
		title();
		menu();
		cout << "您想做什么呢?\t";
		cin >> cmd;

		if (cmd == "0") // 退出系统
			break;
		else if (cmd == "1") // 添加信息
			Insert();
		else if (cmd == "2") // 删除信息
			Delete();
		else if (cmd == "3") // 修改信息
			Edit();
		else if (cmd == "4") // 查询信息，分单体查询和群体查询
			Search();
		else if (cmd == "5") // 统计信息，统计人数、已打分课题数、及格人数等
		{
			title();
			cout << "统计信息如下：\n";
			cout << "\t当前共有学生人数：" << Calc_numOfStudent() << "。" << endl;
			cout << "\t目前已有 " << Calc_numOfMarkedDesign() << " 份课题已评分。" << endl;
			cout << "\t其中有 " << Calc_numOfPassDesign() << " 份课题通过测试达到及格水平。\n";
			system("pause");
		}
		else if (cmd == "6") // 评分系统，给课题打分
		{
			title();
			cout << "本系统有两种打分模式：\n";
			cout << "\t\t[1]批量打分\t\t[2]单独打分\t\t[0]返回\n";
			cout << "*注：\n";
			cout << "->批量打分：为所有未打分的课题打分，当前尚有 "
				+ to_string((Calc_numOfStudent() - Calc_numOfMarkedDesign()))
				+ " 份课题尚未打分。\n";
			cout << "->单独打分：为某个尚未被打分的课题打分，或是重新某个学生的分数。\n";
			cout << "请选择打分模式：";
			cin >> cmd;

			if (cmd == "1") // 批量打分
			{
				MultipleMark();
			}
			else if (cmd == "2") // 单独打分
			{
				SimpleMark();
			}
			else if (cmd == "0") // 返回菜单
			{
				title();
				cout << "操作已取消\n";
				system("pause");
			}
			else
			{
				cout << "输入有误！操作已取消\n";
				system("pause");
			}
		}
		else if (cmd == "7") // 保存文件
			Save();
		else if (cmd == "8") // 读取文件
			Load();
	} while (true);

	footer();
	return 0;
}

void title()
{
	system("cls");
	cout << "***************************************************************************************\n"
		<< "*                                                                                     *\n"
		<< "*                                    Hello World                                      *\n"
		<< "*                              欢迎使用课程设计管理系统!                              *\n"
		<< "*                                                                                     *\n"
		<< "*                                                                                     *\n"
		<< "***************************************************************************************\n";
}

void footer()
{
	system("cls");
	cout << "***************************************************************************************\n"
		<< "*                                                                                     *\n"
		<< "*                                                                                     *\n"
		<< "*                                    感谢您的使用！                                   *\n"
		<< "*                                                                                     *\n"
		<< "*                                                                                     *\n"
		<< "***************************************************************************************\n";
}

void menu()
{
	cout << "\t\t[1]添加学生\t\t[2]删除学生\t\t[3]修改信息\n"
		<< "\t\t[4]查询学生\t\t[5]信息统计\t\t[6]评分系统\n"
		<< "\t\t[7]保存文件\t\t[8]读取文件\t\t[0]退出系统\n";
}

void Insert()
{
	string cmd;
	int stu_ID;
	string stu_name, stu_class, design_name, design_dataStruct;
	title();
	cout << "请输入学生的学号（学号必须为纯数字）：";
	do
	{
		cin >> cmd;
		if (isNumber(cmd)) break;
		else cout << "学号必须为纯数字！请重新输入：";
	} while (true);
	stu_ID = atoi(cmd.data());

	cout << "请输入学生的姓名：";
	cin >> stu_name;

	cout << "请输入学生的班级：";
	cin >> stu_class;

	cout << "请输入学生课题的题目：";
	cin >> design_name;

	cout << "请输入该课题所使用的技术：\n";
	cout << "\t[1]顺序表\t[2]单链表\t[3]二叉树\t[4]图\n";
	do
	{
		cin >> cmd;
		if (cmd == "1") design_dataStruct = "顺序表";
		else if (cmd == "2") design_dataStruct = "单链表";
		else if (cmd == "3") design_dataStruct = "二叉树";
		else if (cmd == "4") design_dataStruct = "图";
		else
		{
			cout << "输入有误！请重新输入：";
			continue;
		}
		break;
	} while (true);

	Student new_stu(stu_ID, stu_name, stu_class, design_name);
	CurriculumDesign new_design(design_name, design_dataStruct, stu_name);

	admin.Insert(new_stu, new_design);
	cout << "添加完成！\n";
	cout << new_stu << endl;

	system("pause");

}

void Delete()
{
	string cmd;
	title();

	cout << "请输入要删除的学生的学号：";
	do
	{
		cin >> cmd;
		if (isNumber(cmd)) break;
		cout << "输入有误！请重新输入：";
	} while (true);

	if (admin.Delete(atoi(cmd.data()))) cout << "删除成功！\n";
	else cout << "删除失败！没有找到这个学生\n";

	system("pause");
}

void Edit()
{
	title();
	string cmd = "";

	cout << "\t\t[1]学生信息\t\t[2]课题信息\t\t[0]返回\n";
	cout << "请选择您想要编辑的信息：";
	cin >> cmd;


	if (cmd == "0")
	{
		title();
		cout << "操作已取消\n";
	}
	else if (cmd == "1")
	{
		int stu_ID;
		cout << "请输入学生的学号：";
		cin >> stu_ID;
		if (!admin.Search(stu_ID))
		{
			cout << "该学生不存在！操作已取消\n";
			system("pause");
			return;
		}
		Student stu = admin.Get(stu_ID);

		title();
		cout << stu << endl << endl;

		cout << "\t\t[1]姓名\t\t\t[2]班级\t\t\t[3]课题名称\n"
			<< "\t\t[4]学号\t\t\t[0]返回\n";
		cout << "请问您想要修改哪一项呢？\t";
		cin >> cmd;
		title();

		if (cmd == "1")
		{
			cout << "**请注意，修改名字的同时也会修改对应课题的作者名**\n";
			string new_name;
			cout << "请输入新的名字：";
			cin >> new_name;
			cout << admin.Edit(stu_ID, "stu_name", new_name) << endl;
		}
		else if (cmd == "2")
		{
			string new_class;
			cout << "请输入新的班级：";
			cin >> new_class;
			cout << admin.Edit(stu_ID, "stu_class", new_class) << endl;
		}
		else if (cmd == "3")
		{
			cout << "**请注意，修改学生课题名字的同时也会修改对应课题的名字**\n";
			string new_name;
			cout << "请输入新的课题名称：";
			cin >> new_name;
			cout << admin.Edit(stu_ID, "design_name", new_name) << endl;
		}
		else if (cmd == "4")
		{
			string new_ID;
			cout << "**请注意，学号必须为数字且不可与其他人重复**\n";
			cout << "请输入新的学号：";

			cin >> new_ID;
			if (!isNumber(new_ID))
			{
				cout << "输入有误！操作已取消\n";
				system("pause");
				return;
			}

			cout << admin.Edit(stu_ID, atoi(new_ID.data()));
		}
		else if (cmd == "0")
		{
			cout << "操作已取消\n";
		}
		else
		{
			title();
			cout << "输入有误！操作已取消\n";
		}
	}
	else if (cmd == "2")
	{
		string stu_ID;
		cout << "\t\t[1]课题名称\t\t[2]实现技术\t\t[0]返回\n";
		cin >> cmd;
		if (cmd == "0") cout << "操作已取消\n";
		else
		{
			cout << "请输入该课题作者的学号：";
			do
			{
				cin >> stu_ID;
				if (isNumber(stu_ID))break;
				cout << "输入必须为纯数字！请重新输入：";
			} while (true);

			if (cmd == "1")
			{
				string new_name;

				cout << "**请注意，修改课题名称后也会修改对应学生信息中的课题名称**\n";
				cout << "请输入新的课题名称：";
				cin >> new_name;

				cout << admin.Edit(atoi(stu_ID.data()), "design_name", new_name) << endl;
			}
			else if (cmd == "2")
			{
				string new_dataStruct;
				cout << "请输入修改后的内容：";
				cin >> new_dataStruct;

				cout << admin.Edit(atoi(stu_ID.data()), "dataStruct", new_dataStruct) << endl;
			}
			else
			{
				cout << "输入有误！操作已取消\n";
			}
		}
	}
	else
	{
		title();
		cout << "输入有误！操作已取消\n";
	}

	system("pause");
}

void Search()
{
	string cmd;
	title();
	cout << "\t\t[1]查询学生信息\t\t[2]查看全体学生\t\t[3]查看所有课题\n";
	cout << "\t\t[4]查看课题排行\t\t[0]返回\n";
	cout << "请选择查询模式：";

	cin >> cmd;
	if (cmd == "1")
	{
		cout << "请输入要查找的学生的学号：";
		do
		{
			cin >> cmd;
			if (isNumber(cmd))break;
			else cout << "学号必须为纯数字！请重新输入：";
		} while (true);

		int stu_ID = atoi(cmd.data());
		Student stu = admin.Get(stu_ID);
		if (stu.get_stu_ID() == -1) cout << endl << "<--该学生不存在-->" << endl;
		else cout << "->" << stu << endl;
	}
	else if (cmd == "2")
	{
		title();
		cout << "当前学生信息如下：\n\n";
		admin.SearchAllStudent();
		cout << endl;
	}
	else if (cmd == "3")
	{
		title();
		cout << "当前课题信息如下：\n\n";
		admin.SearchAllDesign();
		cout << endl;
	}
	else if (cmd == "4")
	{
		title();
		admin.RankingList();
	}
	else if (cmd == "0");
	else cout << "输入有误！请重新输入：";

	system("pause");

}

Score Grade()
{
	cout << endl;
	cout << "**本打分系统可以让您为所有的课题打分，分数范围在0~100之间，由多个部分的评分组成**\n";
	cout << "**其中，代码得分占70%，文档得分占20%，答辩得分占10%**\n\n";

	string str_code_score; // 代码得分字符串
	string str_doc_score; // 文档得分字符串
	string str_reply_score; // 答辩得分字符串
	double code_score = 0; // 代码得分
	double doc_score = 0; // 文档得分
	double reply_score = 0; // 答辩得分

							// 读取代码得分
	cout << "->该课题的代码得分为(0-100)：";
	do
	{
		cin >> str_code_score;
		if (isNumber(str_code_score))
		{
			code_score = atof(str_code_score.data());
			if (code_score >= 0 && code_score <= 100) break;
			else cout << "输入的分数必须在0-100之间！请重新输入：";
		}
		else cout << "输入必须为0-100之间的数字！请重新输入：";
		code_score = 0;
	} while (true);

	// 读取文档得分
	cout << "->该课题的文档得分为(0-100)：";
	do
	{
		cin >> str_doc_score;
		if (isNumber(str_doc_score))
		{
			doc_score = atof(str_doc_score.data());
			if (doc_score >= 0 && doc_score <= 100) break;
			else cout << "输入的分数必须在0-100之间！请重新输入：";
		}
		else cout << "输入必须为0-100之间的数字！请重新输入：";
		doc_score = 0;
	} while (true);

	// 读取答辩得分
	cout << "->该课题的答辩得分为(0-100)：";
	do
	{
		cin >> str_reply_score;
		if (isNumber(str_reply_score))
		{
			reply_score = atof(str_reply_score.data());
			if (reply_score >= 0 && reply_score <= 100) break;
			else cout << "输入的分数必须在0-100之间！请重新输入：";
		}
		else cout << "输入必须为0-100之间的数字！请重新输入：";
		reply_score = 0;
	} while (true);

	// 将分数保存储至score类对象中返回
	Score finalScore(code_score, doc_score, reply_score);
	return finalScore;
}

bool isNumber(string str)
{
	// 判断str是否为纯数字串
	int length = str.length();
	if (length == 0) return false;

	for (int i = 0; i < length; i++)
		if (!isdigit(str[i])) return false;

	return true;
}

void SimpleMark()
{
	title();
	string cmd;
	// 获取目标学生
	int stu_ID;
	cout << "请输入学生的学号（学号必须为纯数字）：";
	do
	{
		cin >> cmd;
		if (isNumber(cmd)) break;
		else cout << "学号必须为纯数字！请重新输入：";
	} while (true);

	stu_ID = atoi(cmd.data());
	if (!admin.Search(stu_ID))
	{
		cout << "该学生不存在！操作已取消\n";
		system("pause");
		return;
	}
	Student target = admin.Get(stu_ID);
	CurriculumDesign design_target = admin.Get(target.get_design_name());

	// 为学生打分
	if (design_target.get_design_score() == 0)
	{
		// 为未评分的课题打分
		cout << endl;
		cout << target << endl;
		Score score = Grade();
		admin.Mark(stu_ID, score);


	}
	else
	{
		// 为已评分的课题重新打分
		cout << "该课题已评分，您可以重新打分：\n";
		cout << endl;
		cout << target << endl;
		Score score = Grade();
		admin.Mark(stu_ID, score);
	}

	// 显示打分结果
	title();
	cout << "**评分完毕！**\n";
	target = admin.Get(stu_ID);
	design_target = admin.Get(target.get_design_name());
	cout << target << endl;
	cout << design_target << endl;
	system("pause");

}

void MultipleMark()
{
	string cmd;
	title();
	cout << "**请注意，一旦开始批量打分，在完成所有打分之前都不能停止，确定要继续吗？**\n";
	cout << "\t\t[1]确定\t\t[0]返回\n";
	cin >> cmd;

	if (cmd == "1")
	{
		title();
		admin.MultipleMark();
		title();
		cout << "评分已全部完成！\n";
		system("pause");
	}
	else if (cmd == "2")
		cout << "操作已取消\n";
	else
		cout << "输入有误！操作已取消\n";

	return;
}

void Save()
{
	title();
	MyFile::save_Student(admin.InfoToFile_Student(), admin.numOfStudent());
	MyFile::save_Design(admin.InfoToFile_Design(), admin.numOfDesign());
	cout << "保存完毕！\n";
	system("pause");
}

void Load()
{
	title();
	string *str_design = MyFile::read_Design();
	string *str_stu = MyFile::read_Student();
	admin.ReadFile(str_stu, str_design);
	cout << "读取完毕！\n";
	system("pause");
}