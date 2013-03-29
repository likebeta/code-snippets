#include "FetchWebPage.h"
#include <process.h>
#include <fstream>
CFetchWebPage::CFetchWebPage()
{
	m_nBaseIndex = -1;
}

CFetchWebPage::~CFetchWebPage()
{
}

bool CFetchWebPage::FetchUrl(string strUrl,string& strContent,size_t& nByteLen)
{
	size_t nStart = strUrl.find("http://");
	if (nStart != string::npos)
	{
		strUrl = strUrl.replace(0,strlen("http://")-1,"");
	}

	string strHost;
	string strRequest;
	nStart = strUrl.find_first_of('/');
	if (nStart == string::npos)
	{
		strHost = strUrl;
		strRequest = "/";
	}
	else
	{
		strHost = strUrl.substr(0,nStart);
		strRequest = strUrl.substr(nStart);
	}

	// connect to server
	SOCKET sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		cout<<"socket create failed" << endl;
		return false;
	}

	string strHeader = "GET ";
	strHeader += strRequest + " HTTP/1.1";
	strHeader += "\r\nHost: ";
	strHeader += strHost.c_str();
	strHeader += "\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:15.0) Gecko/20100101 Firefox/15.0.1";
	strHeader += "\r\nAccept: */*";
	strHeader += "\r\nConnection: keep-alive\r\n\r\n";

	int nPort = 8087;
	string strHostName = "127.0.0.1";//strHost;

 	PHOSTENT pURL = gethostbyname(strHostName.c_str());

	SOCKADDR_IN addrUrl;
	addrUrl.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	addrUrl.sin_family = AF_INET;
	addrUrl.sin_port = htons(nPort);
	if (SOCKET_ERROR == connect(sock,reinterpret_cast<SOCKADDR*>(&addrUrl),sizeof(addrUrl)))
	{
		cout << "socket connect failed" << endl;
		closesocket(sock);
		return false;
	}

	if (SOCKET_ERROR == send(sock,strHeader.c_str(),strHeader.length(),0))
	{
		cout << "socket send failed" << endl;
		closesocket(sock);
		return false;
	}

	string strSrcHtml;
	size_t nTotleRead = 0;
	int nRead = 0;
	char szTmpRecv[4096+1] = {0};
	while ((nRead = recv(sock,szTmpRecv,4096,0)) > 0)
	{
		strSrcHtml.append(szTmpRecv,szTmpRecv+nRead);
		memset(szTmpRecv,'\0',sizeof(szTmpRecv));
		nTotleRead += nRead;
	}
	if (nTotleRead == 0)
	{
		return false;
	}

	// �ɹ�
	nStart = strSrcHtml.find("HTTP/1.1 200");
	if (nStart == string::npos)
	{
		return false;
	}
	nStart = strSrcHtml.find("\r\n\r\n");
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("\r\n\r\n");
	strContent.assign(strSrcHtml.begin() + nStart,strSrcHtml.end());
	nByteLen = nTotleRead - nStart;
// 	ofstream outF("c:/1.txt",ios::binary | ios::out | ios::trunc);
// 	outF.write(strContent.c_str(),nByteLen);
// 	outF.close();
	return true;
}

bool CFetchWebPage::ParseFormContent(string& strContent,string& strSql)
{
	strSql = "begin;";
	// ��ȡform��
	size_t nStart = strContent.find("<form method=");
	size_t nEnd = string::npos;
	if (nStart == string::npos)
	{
		return false;
	}		
	nEnd = strContent.find("</form>",nStart);
	if (nEnd == string::npos)
	{
		return false;
	}
	strContent = strContent.substr(nStart,nEnd - nStart + strlen("</form>"));
	
	// ѭ����ȡli��
	nEnd = 0;
	string strList;
	while(true)
	{
		nStart = strContent.find("<li>",nEnd);
		if (nStart == string::npos)
		{
			break;
		}
		nEnd = strContent.find("</li>",nStart);
		if (nEnd == string::npos)
		{
			break;
		}			
		strList = strContent.substr(nStart,nEnd - nStart + strlen("</li>"));
		if (ParseListContent(strList))
		{
			strSql += strList;
		}
	}
	if (strSql == "begin;")
	{
		return false;
	}
	strSql += "commit;";
	return true;
}

bool CFetchWebPage::ParseListContent(string& strList)
{
	// ��ȡ ���ӵ�ַ �� ͼƬ��ַ
	size_t nStart = strList.find("http://");
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("http://");
	size_t nEnd = strList.find("\"",nStart);
	if (nEnd == string::npos)
	{
		return false;
	}
	string strHref = strList.substr(nStart,nEnd - nStart);
	strList = "INSERT INTO pages VALUES(NULL,'" + strHref + "');";
	return true;
}

int CFetchWebPage::myCallback(void* para,int ncolumn,char** column_value,char** column_name)
{
	vector<string>* pVec = (vector<string>*)para;
	pVec->push_back(column_value[0]);
	return 0;
}

bool CFetchWebPage::ParsePageContent(sqlite3* db,string& strContent,const string& strUrl,string& strSql,string& strPrint)
{
	string strType,strTitle,strMegnet,strTorrent,strTorrentData,strImg,strImgData,strImgBase64,strText;
	// ��ȡtype, ����
	size_t nStart = strContent.find("<h1 class=\"ts\">");
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("<h1 class=\"ts\">");
	nStart = strContent.find("[",nStart);
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("[");
	size_t nEnd = strContent.find("]",nStart);
	if (nEnd == string::npos)
	{
		return false;
	}
	strType = strContent.substr(nStart,nEnd - nStart);
	
	// ��ȡtitle, ����
	nStart = strContent.find("\">",nEnd);
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("\">");
	nEnd = strContent.find("</a>",nStart);
	if (nEnd == string::npos)
	{
		return false;
	}
	strTitle = strContent.substr(nStart,nEnd - nStart);
	
	// ��ȡimg
	nStart = strContent.find("<div class=\"zb\">",nEnd);
	if (nStart != string::npos)
	{
		nStart = strContent.find("src=\"",nStart);
		if (nStart != string::npos)
		{
			nStart += strlen("src=\"");
			nEnd = strContent.find("\"",nStart);
			if (nEnd != string::npos)
			{
				strImg = strContent.substr(nStart,nEnd - nStart);
			}
		}	
	}

	// ��ȡtorrent, �Ǳ���
	nStart = strContent.find("class=\"yb\"",nEnd);
	if (nStart == string::npos)
	{
		return false;
	}
 
	// �������ڵ�λ��, ����torrent��magnet��λ�ò�ͬ
	size_t tmpPos = nStart;

	nEnd = strContent.find(".torrent\"",nStart);
	if (nEnd != string::npos)
	{
		nEnd += strlen(".torrent");
		strTorrent = strContent.substr(tmpPos,nEnd - nStart);
		nStart = strTorrent.rfind("\"");
		if (nStart != string::npos)
		{
			nStart += strlen("\"/");
			strTorrent = strTorrent.substr(nStart);
		}
	}

	// ��ȡmagnet, �Ǳ���
	nStart = tmpPos;
	nStart = strContent.find("href=\"magnet:",nStart);
	if (nStart != string::npos)
	{
		nStart += strlen("href=\"");
		nEnd = strContent.find("\"",nStart);
		if (nEnd != string::npos)
		{
			strMegnet = strContent.substr(nStart,nEnd - nStart);
		}
	}

	if (strMegnet.empty() && strTorrent.empty())
	{
		return false;
	}

	// ��ȡcontent,����
	nStart = strContent.find("<ul class=\"movielist\">",nEnd); 
	if (nStart == string::npos)
	{
		return false;
	}
	nStart += strlen("<ul class=\"movielist\">");
	nStart = strContent.find("<li",nStart);
	if (nStart == string::npos)
	{
		return false;
	}
	nEnd = strContent.find("id=\"tab2\"",nStart);
	if (nEnd == string::npos)
	{
		return false;
	}
	strText = strContent.substr(nStart,nEnd - nStart);
	nEnd = strText.rfind("</li>");
	if (nEnd == string::npos)
	{
		return false;
	}
	nEnd += strlen("</li>");
	strText = strText.substr(0,nEnd);
	FilterContent(strText); // ����һЩ����
	
	// �����������
	nStart = strUrl.find("/");
	if (nStart == string::npos)
	{
		return false;
	}
	string strBaseUrl = strUrl.substr(0,nStart+1);
	if (!strImg.empty())
	{
		strImg = strBaseUrl + strImg;
	}
	if (!strTorrent.empty())
	{
		strTorrent = strBaseUrl + strTorrent;
	}
	
	// ����img������
	size_t nImgLen = 0;
	if (!strImg.empty())
	{
		strPrint += "����ͼƬ: " + strImg + "\n";
		if (FetchUrl(strImg,strImgData,nImgLen))
		{
			strPrint += "���سɹ�\n";
		}
		else
		{
			strPrint += "����ʧ��\n";
		}
	}
	// ���ͼƬ���سɹ�,����һ��base64�����ʽ
	if (nImgLen != 0)
	{
		strImgBase64 = m_base64.Encode(reinterpret_cast<const unsigned char*>(strImgData.c_str()),nImgLen);
		int nTmpBegin = strImg.rfind(".");
		strImgBase64 = "data:image/" + strImg.substr(nTmpBegin+1)+";base64,"+strImgBase64;
	}

	// ����torrent����
	size_t nTorrentLen = 0;
	if (!strTorrent.empty())
	{
		strPrint += "��������: " + strTorrent + "\n";
		if (FetchUrl(strTorrent,strTorrentData,nTorrentLen))
		{
			strPrint += "���سɹ�\n";
		}
		else
		{
			strPrint += "����ʧ��\n";
		}
	}

	char* pSql = sqlite3_mprintf("INSERT INTO data VALUES(NULL,'%q','%q','%q','%q','%q',?,'%q','%q',?,'%q');",strType.c_str(),strTitle.c_str(),strUrl.c_str(),strMegnet.c_str(),strTorrent.c_str(),strImg.c_str(),strImgBase64.c_str(),strText.c_str());
	// ���sql
	strSql = pSql;
	sqlite3_free(pSql);

	sqlite3_stmt* stmt;
	if (SQLITE_OK != sqlite3_prepare(db,strSql.c_str(),strSql.length(),&stmt,NULL))
	{
		strPrint += "sqlite3_prepare failed: ";
		strPrint += sqlite3_errmsg(db);
		strPrint += "\n";
		return false;
	}
	if (SQLITE_OK != sqlite3_bind_blob(stmt,1,strTorrentData.c_str(),nTorrentLen,NULL))
	{
		strPrint += "sqlite3_bind_blob torrentdata failed: ";
		strPrint += sqlite3_errmsg(db);
		strPrint += "\n";
		return false;
	}	
	if (SQLITE_OK != sqlite3_bind_blob(stmt,2,strImgData.c_str(),nImgLen,NULL))
	{
		strPrint += "sqlite3_bind_blob imgdata failed: ";
		strPrint += sqlite3_errmsg(db);
		strPrint += "\n";
		return false;
	}

	EnterCriticalSection(&m_csDb);
	if (SQLITE_DONE != sqlite3_step(stmt))
	{
		strPrint += "sqlite3_step failed: ";
		strPrint += sqlite3_errmsg(db);
		strPrint += "\n";
		LeaveCriticalSection(&m_csDb);
		return false;
	}
	LeaveCriticalSection(&m_csDb);
	sqlite3_finalize(stmt);
	return true;
}
bool CFetchWebPage::FilterContent(string& strText)
{
	// ȥ������ ָ�� http://hd.cnscg.com/* ��a
	size_t nStart = 0;
	size_t nEnd = 0;
	while (true)
	{
		nStart = strText.find("href=\"http://hd.cnscg.com",nEnd);
		if (nStart == string::npos)
		{
			break;
		}
		nStart = strText.rfind("<a",nStart);
		if (nStart == string::npos)
		{
			break;
		}
		nEnd = strText.find("</a>",nStart);
		if (nStart == string::npos)
		{
			break;
		}
		nEnd += strlen("</a>");
		strText = strText.replace(nStart,nEnd - nStart,"");
		nEnd = nStart;
	}

	// ȥ������script��ǩ��������
	nEnd = 0;
	while (true)
	{
		nStart = strText.find("<script",nEnd);
		if (nStart == string::npos)
		{
			break;
		}
		nEnd = strText.find("</script>",nStart);
		if (nEnd == string::npos)
		{
			break;
		}
		nEnd += strlen("</script>");
		strText = strText.replace(nStart,nEnd - nStart,"");
		nEnd = nStart;
	}

	// ȥ������ img ����������a(�������)
	nEnd = 0;
	while (true)
	{
		nStart = strText.find("<img",nEnd);
		if (nStart == string::npos)
		{
			break;
		}
		size_t nTmpStart = strText.rfind("<a",nStart);
		if (nTmpStart != string::npos)
		{
			size_t nTmpEnd = strText.find("</a>",nTmpStart);
			if (nTmpEnd != string::npos)
			{
				if (nStart > nTmpStart && nStart < nTmpEnd) // ������ a ��
				{
					// ����a��ǩ
					nStart = nTmpStart;
					nEnd = nTmpEnd + strlen("</a>");
					strText = strText.replace(nStart,nEnd - nStart,"");
					nEnd = nStart;
					continue;
				}
			}
		}
		// ����img��ǩ, û���������ҵ�������a��ǩ
		nEnd = strText.find(">",nStart);
		if (nEnd == string::npos)
		{
			// ��������д�, ��֪զ����
			break;
		}
		nEnd += strlen(">");
		size_t nTmp = strText.find("</img>",nEnd);
		if (nTmp == nEnd + 1) // img��ǩΪ<img...></img>��ʽ 
		{
			nEnd = nTmp + strlen("</img>");
		}
		else   // img��ǩΪ<img...>��ʽ 
		{
		}
		strText = strText.replace(nStart,nEnd - nStart,"");
		nEnd = nStart;
	}

	// �������� <br />,<br>����<br/>
	nEnd = 0;
	string strBrs[1] = {/*"<br />\n<br />,*/"<br/>\n<br/>"/*,"<br>\n<br>"*/};
	string strBr[1] = {/*"<br />",*/"<br/>"/*,"<br>"*/};
	for (int i = 0; i != 1;++i)
	{
		while (true)
		{
			nStart = strText.find(strBrs[i],nEnd);
			if (nStart == string::npos )
			{
				break;
			}
			strText = strText.replace(nStart,strBrs[i].length(),strBr[i]);
			nEnd = nStart;
		}
	}
	return true;
}

unsigned int WINAPI CFetchWebPage::myThread(void* pVoid)
{
	CFetchWebPage* pThis = static_cast<CFetchWebPage*>(pVoid);
	return pThis->thread_run();
}

bool CFetchWebPage::Run()
{
	cout << "��ʼ����..........." << endl;
	WSADATA wsaData = {0};
	if(WSAStartup(MAKEWORD(2,2), &wsaData))
	{
		cout << "�׽��ֳ�ʼ��ʧ��!" << endl;
		return false;
	}
	//  ��data.db
	sqlite3* db;
	if (SQLITE_OK != sqlite3_open("data.db",&db))
	{
		cout << "��data.dbʧ��" << endl;
		return false;
	}
	string strSql = "CREATE TABLE IF NOT EXISTS forums (id INTEGER PRIMARY KEY AUTOINCREMENT,url TEXT,content TEXT);";
	if (SQLITE_OK != sqlite3_exec(db,strSql.c_str(),NULL,NULL,NULL))
	{
		cout << "����forums��ʧ��" << endl;
		sqlite3_close(db);
		return false;
	}
	strSql = "CREATE TABLE IF NOT EXISTS pages (id INTEGER PRIMARY KEY AUTOINCREMENT,url TEXT);";
	if (SQLITE_OK != sqlite3_exec(db,strSql.c_str(),NULL,NULL,NULL))
	{
		cout << "����pages��ʧ��" << endl;
		sqlite3_close(db);
		return false;
	}

	 cout << "download forums ?" << endl;
	if (getchar() == 'y')
	{
		string strContent;
		// ����forums
		cout << "��ʼ����forums�б�" <<endl;
		ofstream outStream("forumsfaildlist.txt",ios::out | ios::trunc | ios::binary);
		char szFormat[256];
		size_t nByteLen = 0;
		for (int i = 1; i != 222; ++i)
		{
			sprintf_s(szFormat,"www.btscg.com/forum-2-%d.html",i);
			cout << "\n��ʼ����"<< szFormat << endl;
			if (FetchUrl(szFormat,strContent,nByteLen))
			{
				cout << "���سɹ�" << endl;
				char* pSql = sqlite3_mprintf("INSERT INTO forums VALUES(NULL,'%q','%q');",szFormat,strContent.c_str());
				if (SQLITE_OK != sqlite3_exec(db,pSql,NULL,NULL,NULL))
				{
					cout << "���浽forumsʧ��" << endl;
				}
				else
				{
					cout << "���浽forums�ɹ�" << endl;
				}
				sqlite3_free(pSql);

				string strSqls;
				if (ParseFormContent(strContent,strSqls))
				{
					cout << "�����ɹ�" << endl;
					if (SQLITE_OK == sqlite3_exec(db,strSqls.c_str(),NULL,NULL,NULL))
					{
						cout << "���浽pages�ɹ�" << endl;
					}
					else
					{
						cout << "���浽pagesʧ��" << endl;
						outStream << szFormat << endl;
					}
				}
				else
				{
					cout << "����ʧ��" << endl;
					outStream << szFormat << endl;
				}
			}
			else
			{
				cout << "����ʧ��" << endl;
				outStream << szFormat << endl;
			}
		}
		outStream.close();
	}
	
	cout << "begin to download data ?" << endl;
	if (getchar() == 'n')
	{
		return true;
	}

	// �������д�����url
	strSql = "SELECT url FROM pages;";

	if (SQLITE_OK != sqlite3_exec(db,strSql.c_str(),myCallback,&m_UrlsVec,NULL))
	{
		cout << "��ѯpages��ʧ��" << endl;
		sqlite3_close(db);	
		return false;
	}
	sqlite3_close(db);

	// �����̴߳�������
	int nThreadNum = 1;
	m_nInterval = (m_UrlsVec.size() + nThreadNum - 1) / nThreadNum;
	HANDLE* phTreads = new HANDLE[nThreadNum];
	InitializeCriticalSection(&m_csDb);
	InitializeCriticalSection(&m_csIndex);
	InitializeCriticalSection(&m_csFile);
	for (int i = 0;i < nThreadNum;++i)
	{
		phTreads[i] = reinterpret_cast<HANDLE>(_beginthreadex(NULL,0,myThread,this,0,NULL));
	}
	DWORD dwResult = WaitForMultipleObjects(nThreadNum,phTreads,TRUE,INFINITE);
	DeleteCriticalSection(&m_csIndex);
	DeleteCriticalSection(&m_csDb);
	DeleteCriticalSection(&m_csFile);
	for (int i=0;i < nThreadNum;++i)
	{
		CloseHandle(phTreads[i]);
	}
	delete []phTreads;
	WSACleanup();
	cout << "�����������!" << endl;
	return true;
}

unsigned int CFetchWebPage::thread_run()
{
	vector<string>::size_type nBase = GetBaseIndex();
	// �� data.db
	sqlite3* dataDB;
	if (SQLITE_OK != sqlite3_open("data.db",&dataDB))
	{
		cout << "��data.dbʧ��" << endl;
		return false;
	}
	string strSql = "CREATE TABLE IF NOT EXISTS data (id INTEGER PRIMARY KEY AUTOINCREMENT,type TEXT,title TEXT,fromurl TEXT,magnet TEXT,torrent TEXT,torrentdata BLOB,img TEXT,imgBase64 TEXT,imgdata BLOB,content TEXT);";
	EnterCriticalSection(&m_csDb);
	if (SQLITE_OK != sqlite3_exec(dataDB,strSql.c_str(),NULL,NULL,NULL))
	{
		cout << "����data��ʧ��" << endl;
		sqlite3_close(dataDB);
		LeaveCriticalSection(&m_csDb);
		return false;
	}
	LeaveCriticalSection(&m_csDb);
	string strContent;
	size_t nByteLen = 0;
	string strPrint;
	ofstream outFsteam("failedlist.txt",ios::out | ios::binary | ios::app);
	vector<string>::iterator itBegin = m_UrlsVec.begin() + nBase;
	vector<string>::iterator itEnd = ((nBase + m_nInterval) >  m_UrlsVec.size()) ? m_UrlsVec.end() : (itBegin + m_nInterval);
	for ( ; itBegin != itEnd; ++itBegin)
	{
		strPrint = "\n��ʼ����" + (*itBegin) + "\n";
		if (FetchUrl(*itBegin,strContent,nByteLen))
		{
			strPrint += "���سɹ�\n";
			if (ParsePageContent(dataDB,strContent,*itBegin,strSql,strPrint))
			{
				strPrint += "�����ɹ�\n";
			}
			else
			{
				strPrint += "����ʧ��\n";
				EnterCriticalSection(&m_csFile);
				outFsteam << *itBegin << endl;
				LeaveCriticalSection(&m_csFile);
			}
		}
		else
		{
			strPrint += "����ʧ��\n";
			EnterCriticalSection(&m_csFile);
			outFsteam << *itBegin << endl;
			LeaveCriticalSection(&m_csFile);
		}
		cout << strPrint << endl;
	}
	sqlite3_close(dataDB);
	return 0;
}

vector<string>::size_type CFetchWebPage::GetBaseIndex()
{
	EnterCriticalSection(&m_csIndex);
	if (m_nBaseIndex == -1)
	{
		m_nBaseIndex = 0;
	}
	else
	{
		m_nBaseIndex += m_nInterval;
	}
	LeaveCriticalSection(&m_csIndex);
	return m_nBaseIndex;
}