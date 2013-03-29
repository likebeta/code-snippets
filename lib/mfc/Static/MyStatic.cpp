// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_nBkMode=TRANSPARENT;
	m_bTrack=FALSE;
	m_bHover=FALSE;
	m_sTargetUrl="";//"huangdi915103@gmail.com";
	m_strCmd="";//"mailto:";
	m_clrTextColor = RGB(0,0,0);
	m_ptCenter=0;
	// ����֧��
	m_clrBkTextColor = ::GetSysColor(COLOR_3DFACE);
	m_Brush.Attach(GetStockObject(NULL_BRUSH));
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers
void CMyStatic::SetWindowText(LPCTSTR lpszString )    //��������
{
	CString str=lpszString;
// 	if (str!="")                                      //ʹ�ؼ���С��Ӧ�ı�,ֻ�ʺϼ�С
// 	{
// 		CClientDC  dc(this); 
// 		CRect  rcMe;
// 		GetWindowRect(&rcMe);
// 		
// 		CSize sz=dc.GetOutputTextExtent(str); //��ȡ�ַ�����Ϣ
// 		if (rcMe.Width()!=sz.cx || rcMe.Height()!=sz.cy)
// 		{
// 			CRect rcParentClient,rcParentWhole;
//  			GetParent()->GetClientRect(&rcParentClient);
// 			GetParent()->GetWindowRect(&rcParentWhole);
//  			int CaptionH=0;
// 			int CaptionW=0;
//  			if (rcParentClient.right!=rcParentWhole.Width() || rcParentClient.bottom!=rcParentWhole.Height())
//  			{
//  				CaptionH=rcParentWhole.Height()-rcParentClient.bottom-3;
//  				CaptionW=rcParentWhole.Width()-rcParentClient.right-3;
//  		      //CaptionW= GetSystemMetrics(SM_CXFRAME);
//  			  //CaptionH= GetSystemMetrics(SM_CYCAPTION);
//  			}
//  
//  			if (m_ptCenter.x==0 && m_ptCenter.y==0)
//  			{
//  				m_ptCenter.x=rcMe.CenterPoint().x;
//  				m_ptCenter.y=rcMe.top;
//  			}
//  			int x=m_ptCenter.x-sz.cx/2;  
//  			int y=m_ptCenter.y;
//      	    MoveWindow(x-rcParentWhole.left-CaptionW,y-rcParentWhole.top-CaptionH,sz.cx,sz.cy);
//  		}
//  	}
	CStatic::SetWindowText(str);
 }
void CMyStatic::SetTextColor(COLORREF clrText) // �����ı���ɫ
{
	m_clrTextColor=clrText;
	Invalidate();   //�����ػ�	
}
void CMyStatic::SetBackgroundColor(COLORREF clrBackgroundColor)  //���ÿؼ�������ɫ
{
	m_Brush.Detach();
	m_Brush.CreateSolidBrush(clrBackgroundColor);
	Invalidate(TRUE);
} 

void CMyStatic::SetBkColor(COLORREF clrBkTextColor)  //�����ı�������ɫ
{
	m_clrBkTextColor = clrBkTextColor;
    Invalidate();
}
void CMyStatic::EnableTrack(BOOL bEnable/* = false*/)  // �Ƿ�������.���������ؼ�ʱָ���л��Ĺ���
{
	  m_bTrack = bEnable;
	  Invalidate(TRUE);
}
void CMyStatic::SetLinkUrl(LPCTSTR lpszTargetUrl,LPCTSTR lpszCmd/* ="mailto:" */)   //���ó����Ӻ�����
{
	m_sTargetUrl = lpszTargetUrl;
	m_strCmd=lpszCmd;
}

void CMyStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTrack && m_sTargetUrl!="")
	{
		if (m_bHover)
		{
			CRect rec;
			GetClientRect(&rec);
			
			// ����뿪��LabelLink
			if (!rec.PtInRect(point))
			{
				m_bHover = FALSE;
				::ReleaseCapture();
			}
		}
		// ������LabelLink
		else
		{
			m_bHover = TRUE;
			SetCapture();
			
			// #define IDC_HAND  MAKEINTRESOURCE(32649)
			// ֱ������IDC_HAND��Ҫ���ͷ�ļ�
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));			
			Invalidate(TRUE);
		}
	}
  CStatic::OnMouseMove(nFlags, point);
}

void CMyStatic::OnClicked() 
{
	// TODO: Add your control notification handler code here
	if (m_sTargetUrl!="")
	{
		ShellExecute(NULL, "open",m_strCmd+m_sTargetUrl, NULL,NULL, SW_NORMAL); 
	}
}

void CMyStatic::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ModifyStyle(0,SS_NOTIFY | SS_CENTER);// SS_NOTIFYʹ�ؼ��ܹ����������Ϣ
	CStatic::PreSubclassWindow();
}

HBRUSH CMyStatic::CtlColor(CDC *pDC, UINT nCtlColor)
{
	pDC->SetBkMode(m_nBkMode);
	pDC->SetTextColor(m_clrTextColor);
	pDC->SetBkColor(m_clrBkTextColor);	
	return (HBRUSH)m_Brush;
}
void CMyStatic::SetBkMode(int iBkMode/*=TRANSPARENT*/)
{
	m_nBkMode=iBkMode;
}
