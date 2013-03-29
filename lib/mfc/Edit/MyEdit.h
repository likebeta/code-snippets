#if !defined(AFX_MYEDIT_H__7AE5DE9E_76C4_496A_AF5F_B39F3D703CA4__INCLUDED_)
#define AFX_MYEDIT_H__7AE5DE9E_76C4_496A_AF5F_B39F3D703CA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyEdit window

class CMyEdit : public CEdit
{
// Construction
public:
	CMyEdit();

// Attributes
public:
private:
	bool     m_bIsReadOnly;               //�Ƿ�ֻ��
	bool     m_bMouseOver;	             // ����Ƿ񾭹�
	bool     m_bFocus;                 	 // �Ƿ��н���

	COLORREF m_clrNormalFrmClr;	         // �ؼ��޽���ʱ,�ؼ��߿���ɫ
	COLORREF m_clrFocusFrmClr;     	     // �ؼ��н���ʱ,�ؼ��߿���ɫ
	COLORREF m_clrTextColor;	         // ������ɫ

	CBrush   m_TextBkBrush;	             // ���屳����ˢ
	CFont    m_ftEditFont;	             // ����
    int      m_nFontSize;                // �ֺ�
	COLORREF m_clrNormalBkColor;         // �޽���ʱ����ǳ��ɫ
    COLORREF m_clrFocusBkColor;          // �н���ʱ����ǳ��ɫ
	UINT     m_nVMargins;                // ��ֱ���¼��
// Operations
public:
	void     SetHMargins(UINT nLeft, UINT nRight);      //����ˮƽ���
	void     SetVMargins(UINT nVMargins);  //���ô�ֱ���
	
	void     SetEditFont(int nSize, LPCSTR lpszFontName = _T( "Arial" ));	    // Set font
	COLORREF SetNormalFrmClr( COLORREF clrNormalFrmClr );	                    // Set normal frame color	
	COLORREF GetNormalFrmClr() const;                                           // Get normal frame color
	COLORREF SetFocusFrmClr( COLORREF clrFocusFrmClr );	                        // Set focus frame color
	COLORREF GetFocusFrmClr() const;	                                        // Get focus frame color
	COLORREF SetTextColor( COLORREF clrTextColor );	                            // Set text color
	COLORREF GetTextColor() const;	                                            // Get text color
	COLORREF SetBkColor( COLORREF clrBkColor );	                                // Set back color
	COLORREF GetBkColor() const;                                                // Get text back color
	BOOL     ModifyStyle( DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0 );           //
	BOOL     ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	void     EnableDropFiles(BOOL bEnable = TRUE);
	
private:
    void     Draw(CDC *pDC);                                    //�������ƺ���  	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMyEdit();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDIT_H__7AE5DE9E_76C4_496A_AF5F_B39F3D703CA4__INCLUDED_)
