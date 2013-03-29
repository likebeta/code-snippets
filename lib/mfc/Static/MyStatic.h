//MyStatic.h
#if !defined(AFX_MYSTATIC_H__78BB3B69_440F_4A81_80BE_A219A53A80EC__INCLUDED_)
#define AFX_MYSTATIC_H__78BB3B69_440F_4A81_80BE_A219A53A80EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif
/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();

// Attributes
public:

// Operations
public:
	// interface declaration
    void SetTextColor(COLORREF clrText);  // �����ı���ɫ
    void SetBackgroundColor(COLORREF clrBackgroundColor);  //���ÿؼ�������ɫ
	void SetBkColor(COLORREF clrBkTextColor);  //�����ı�������ɫ
    void EnableTrack(BOOL bEnable = FALSE);  // �Ƿ�������.���������ؼ�ʱָ���л��Ĺ���
    void SetLinkUrl(LPCTSTR lpszTargetUrl,LPCTSTR lpszCmd="mailto:");    // ����Ŀ�����ӵ�ַ������
	void SetBkMode(int iBkMode=TRANSPARENT);//�����ı���ʾģʽ
	void SetWindowText(LPCTSTR lpszString );    //�����ı�
protected:
	BOOL m_bHover;            //����Ƿ�λ�ڿռ�֮��
    BOOL m_bTrack;                 //�Ƿ���ٿؼ�������ʾС�֣�
    COLORREF m_clrTextColor;       //������ɫ
    COLORREF m_clrBkTextColor;  //���ֱ�����ɫ
    CBrush m_Brush;        //�ؼ�������ɫ��ˢ
    CString m_sTargetUrl; //������
	CString m_strCmd;   //����,��mailto,����ҳʱΪ""
	int m_nBkMode;    //������ʾ�������ģʽ
    CPoint m_ptCenter; //�ռ�ԭʼ����
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

public:
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	//}}AFX_MSG
    afx_msg HBRUSH CtlColor(CDC *pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__78BB3B69_440F_4A81_80BE_A219A53A80EC__INCLUDED_)
