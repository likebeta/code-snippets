#if !defined(AFX_MYBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
#define AFX_MYBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window
#include "FICS.h"
class CMyButton : public CButton
{
// Construction
public:
	CMyButton();

	// Attributes
protected:
	//��ť��״̬
	BOOL m_bOver;	    //���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	BOOL m_bTracked;	//�����λ�ڰ�ť��,����һֱ����OnMouseHover��Ϣ
	CString m_strPathNormal; //����ʱ��İ�ť����
	CString m_strPathHover;  //��ý���ʱ�İ�ť�ı���
	BOOL m_bIsDrawImgBtn;    //�Ƿ���ͼƬΪ�����İ�ť
	Color m_clrTodStartNormal;
	Color m_clrBottomEndNormal;
	COLORREF m_clrBorderNormal;
	Color m_clrTodStartHover;
	Color m_clrBottomEndHover;
	COLORREF m_clrBorderHover;

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);
	void SetBtnBkImgPath(CString strNormal,CString strHover);
	void SetDrawImgBtn(BOOL bDrawImgBtn = TRUE);
	void SetNormalColors(Color clrTodStartNormal,Color clrBottomEndNormal,COLORREF clrBorderNormal);
	void SetHoverColors(Color clrTodStartHover,Color clrBottomEndHover,	COLORREF clrBorderHover);
	// Implementation
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CMyButton();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
