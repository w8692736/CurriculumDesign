#include "stdafx.h"
#include "ConnectionAccess.h"


ConnectionAccess::ConnectionAccess()
{
	// Open the connection with ACCESS
	;
}


ConnectionAccess::~ConnectionAccess()
{
	// Close the connection with ACCESS
}

void ConnectionAccess::Execute(string sql)
{
	// Execute the SQL statement
}


void ConnectionAccess::OnInitADOConn()
{
	::CoInitialize(NULL);
	try
	{
		HX_pConnection.CreateInstance(__uuidof(Connection));//�ȼ��� //HX_pConnection.CreateInstance("ADODB.Connection");  
															//�˾������λ�����ݿ������ķ�����Ϣ  
		_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\\�����ļ�\\C++�γ����\\CurriculumDesignManagement\\CurriculumDesignManagement\\CurriculumDesignManagement\\Database1.accdb;Persist Security Info=False ";
		//����//_bstr_t strConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Database1.accdb;Persist Security Info=False";//�˾������λ�����ݿ������ķ�����Ϣ  
		//����//_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Driver = { Microsoft Access Driver(*.mdb, *.accdb) }; DBQ =Database1.accdb;Persist Security Info=False ";  
		//�˾������λ�����ݿ������ķ�����Ϣ  
		//����master���ݿ⣬�����롣  
		HX_pConnection->Open(strConnect, "", "", adModeUnknown);    //�������ݿ�  

		cout << "���ӳɹ�,���������ָ��" << endl;
	}
	catch (_com_error e)
	{
		cout << e.Description() << endl;
	}

}

void ConnectionAccess::ExitConnect() {
	if (HX_pRecordset != NULL)
		HX_pRecordset->Close();
	HX_pConnection->Close();
	::CoUninitialize();
}