#include "post.h"
#include <fstream>
#include "tools.h"
int main()
{
	WSADATA wsaData = {0};
	if(WSAStartup(MAKEWORD(2,2), &wsaData))
	{
		cout << "�׽��ֳ�ʼ��ʧ��!" << endl;
		return false;
	}
	vector<CATEGORY_DATA*> vec;
	CPost post("www.likebeta.net/xmlrpc.php","admin","www.fuck1.com",1);
	post.Run();
	cout << "�����Ѿ����" << endl;
	WSACleanup();
	system("pause");
	return 0;
}