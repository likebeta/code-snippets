/////////////////////////////////////////////////////////////////////////////
//CPluckButton:�������ڰ�ť
//
//��Dreamweaver��Flash���������һ���������ڵİ�ť��������ʹ���ڳߴ緢��
//�仯������ť���Ƿ���������״�������ġ�
//
//�÷���
//���ڶԻ����з���һ����ť�ؼ���������ı�������״����Ϊϸ��״��
//��Ϊ��ť������������͸�ΪCPluckButton;
//���ڶԻ����OnInitDialog()��������SetPluckButStyle()�������ð�ť��ʼ���
//
//���ߣ�����
//                   2004-12-18
////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUCKBUTTON_H__397B334A_9686_4EF6_9070_3F6591BCB24F__INCLUDED_)
#define AFX_PLUCKBUTTON_H__397B334A_9686_4EF6_9070_3F6591BCB24F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PluckButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPluckButton window

//��ť��񣨰���ͷ���򻮷֣�
#define  KEY_STYLE_DOWN  1
#define  KEY_STYLE_UP    2
#define  KEY_STYLE_LEFT  3
#define  KEY_STYLE_RIGHT 4

class CPluckButton : public CButton
{
// Construction
public:
	CPluckButton();

private:
	int    m_style;			//��ť���
	BOOL   b_InRect;		//�������־
	CRect  m_ButRect;		//��ť�ߴ�
	POINT  m_pt[3];			//��ͷ����

	void NormalButton(CDC *pDC);	//��������ť
	void PassButton(CDC *pDC);		//����꾭��ʱ�İ�ť

// Attributes
public:
	void SetPluckButStyle(int Style);	//���ð�ť���
	int  GetPluckButStyle();			//��ȡ��ť���

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPluckButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPluckButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPluckButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLUCKBUTTON_H__397B334A_9686_4EF6_9070_3F6591BCB24F__INCLUDED_)
