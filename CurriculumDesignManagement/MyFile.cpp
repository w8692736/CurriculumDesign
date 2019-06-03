#include "stdafx.h"
#include "MyFile.h"


MyFile::MyFile()
{
}


MyFile::~MyFile()
{
}

void MyFile::save_Student(string* info, int length)
{
	std::ofstream fout("Student.txt", std::ios::out);
	if (!fout) cout << "�Ҳ����ļ�������ʧ��\n";
	else
	{
		for (int i = 0; i < length; i++)
		{
			fout <<( info[i] + "\n");
		}
		cout << "����ɹ���\n";
	}
	fout.close();
}

void MyFile::save_Design(string* info, int length)
{
	std::ofstream fout("Design.txt", std::ios::out);
	if (!fout) cout << "�Ҳ����ļ�������ʧ��\n";
	else
	{
		for (int i = 0; i < length; i++)
		{
			fout << (info[i] + "\n");
		}
		cout << "����ɹ���\n";
	}
	fout.close();
}

string* MyFile::read_Design()
{
	int length = length_Student();
	string *str = new string[length];
	string line, s1, s2, s3, s4, s5, s6, s7;
	int index = 0;

	std::ifstream inf("Design.txt");
	if (!inf) std::cout << "�Ҳ����ļ�����ȡʧ��\n";
	else
	{
		while (std::getline(inf, line))//"getline()" ends with a line break.
		{
			std::istringstream iss(line);
			iss >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7;
			str[index++] = s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5 + " " + s6 + " " + s7;
		}
	}
	return str;
}

string* MyFile::read_Student()
{
	int length = length_Student();
	string *str = new string[length];
	string line, s1, s2, s3, s4;
	int index = 0;

	std::ifstream inf("Student.txt");
	if (!inf) std::cout << "�Ҳ����ļ�����ȡʧ��\n";
	else
	{
		while (std::getline(inf, line))//"getline()" ends with a line break.
		{
			std::istringstream iss(line);
			iss >> s1 >> s2 >> s3 >> s4;
			str[index++] = s1 + " " + s2 + " " + s3 + " " + s4;
		}
	}
	return str;
}

int MyFile::length_Student()
{
	// ��ȡStudent�ı��е�����
	int length = 0;
	char ch;
	fstream fin("Student.txt", ios::in);
	while (fin.get(ch))if (ch == '\n')length++;

	return length;
}


