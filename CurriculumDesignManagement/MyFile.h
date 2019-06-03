#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class MyFile
{
public:
	MyFile();
	~MyFile();

	static string* read_Student();
	static string* read_Design();

	static void save_Student(string* info, int length);
	static void save_Design(string* info, int length);

	static int length_Student();
};

