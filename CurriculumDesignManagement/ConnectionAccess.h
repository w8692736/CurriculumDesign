#pragma once

#include <iostream>
#include <string>
#include "stdafx.h"

#import"C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "adoEOF"), rename("BOF", "adoBOF")
using namespace ADODB;

using std::cin;
using std::cout;
using std::endl;
using std::string;


class ConnectionAccess
{
private:
	static _ConnectionPtr   HX_pConnection; // ���ݿ�ָ��  
	static _RecordsetPtr    HX_pRecordset; // ����ָ��  
	static _CommandPtr      HX_pCommand; // ��¼ָ��  
public:
	ConnectionAccess();
	~ConnectionAccess();

	void Execute(string sql);
	void static OnInitADOConn();
	void static ExitConnect();
};

