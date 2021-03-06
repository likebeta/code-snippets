#include "StdAfx.h"
#include "CollectorFrame.h"
#include "FetchWebPage.h"
int APIENTRY _tWinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPTSTR lpCmdLine, __in int nShowCmd )
{
// 	CFetchWebPage d;
// 	d.SetAgent(_T("127.0.0.1"),8087);
// 	d.FetchUrl(_T("http://www.btscg.com/forum-2-1.html"));
// 	return 0;

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("default.zip"));
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;
	CCollectorFrame* pFrame = new CCollectorFrame();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("酷盘便携版"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}