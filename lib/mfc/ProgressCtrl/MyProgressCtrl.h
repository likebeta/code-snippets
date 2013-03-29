#if !defined(AFX_MYPROGRESSCTRL_H__4C78DBBE_EFB6_11D1_AB14_203E25000000__INCLUDED_)
#define AFX_MYPROGRESSCTRL_H__4C78DBBE_EFB6_11D1_AB14_203E25000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MyProgressCtrl.h : header file
/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl window
#define MYBAR_STYLE_NORMAL 0
#define MYBAR_STYLE_XP 1
#define MYBAR_STYLE_WIN7 2
class CMyProgressCtrl : public CProgressCtrl
{
// Construction
public:
    CMyProgressCtrl();

// Attributes
public:

// Operations
public:
    int         SetPos(int nPos);
	int         GetPos();
    int         StepIt();
	int         SetStep(int nStep);
    void        SetRange(int nLower, int nUpper);
	void        GetRange(int& nLower, int& nUpper);
    int         OffsetPos(int nPos);                  //��nPosָ�������������ӽ������ؼ��ĵ�ǰλ��
    void        SetStartBarColor(COLORREF col);           //���ý�������ʼ��ɫ
	void        SetEndBarColor(COLORREF col);           //���ý�������ֹ��ɫ
    void        SetDlgBkColor(COLORREF col);            //���ý������ı���ɫ
    void        SetTextUnCoverColor(COLORREF col);    //��������û�и����ı�ʱ���ı�����ɫ
    void        SetTextCoveredColor(COLORREF col);      //�������������ı�ʱ���ı�����ɫ
	COLORREF    GetStartBarColor();                       //�õ�����������ʼ��ɫ
	COLORREF    GetEndBarColor();                       //�õ�����������ֹ��ɫ
	COLORREF    GetBkColor();                        //�õ��������ı���ɫ
	COLORREF    GetTextUnCoverColor();                //��������û�и����ı�ʱ���õ��ı�����ɫ
	COLORREF    GetTextCoveredColor();                  //�������������ı�ʱ���õ��ı�����ɫ	
    void        EnableShowText(BOOL bShowText = TRUE,BOOL bShowPercent = TRUE );       //�����Ƿ���ʾ���ֺͰٷֱ�(�ٷֱȽ���m_bShowTextΪTRUE,m_strTextΪ��ʱ��ʾ)
	int         SetBarStyle(int nbarStyle = MYBAR_STYLE_NORMAL);            //���ý������ķ��
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMyProgressCtrl)
protected:
	virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMyProgressCtrl();

// Generated message map functions
protected:
    int         m_nCurrentPos,                     //��������ǰλ��
                m_nStepSize,                //���������߶�
                m_nMax,                     //�������ؼ���Χ������
                m_nMin;                     //�������ؼ���Χ������
    CString     m_strText;                  //��������ʾ������
    BOOL        m_bShowText;                //�Ƿ���ʾ����
	BOOL        m_bShowPercent;             //�Ƿ���ʾ�ٷֱ�,m_bShowTextΪTRUE,m_strTextΪ��ʱ��ʾ

    COLORREF    m_clrStartBar,               //��������ʼλ����ɫ
		        m_clrEndBar,                 //��������ֹλ����ɫ
                m_clrDlgBk,                    //����������ɫ
                m_clrTextUnCover,              //������û�и����ı�ʱ���ı�����ɫ
                m_clrTextCovered;              //�����������ı����ı�����ɫ
	int         m_nBarStyle;                   //�������ķ��

    //{{AFX_MSG(CMyProgressCtrl)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    afx_msg LRESULT OnSetText(UINT cchTextMax, LPCTSTR szText);
    afx_msg LRESULT OnGetText(UINT cchTextMax, LPTSTR szText);

    DECLARE_MESSAGE_MAP()
protected:
	void DrawNormalStyleBar(CDC* pDC, const RECT& rectClient, const int& nMaxWidth);  //����һ�������
	void DrawXPStyleBar(CDC* pDC, const RECT& rectClient, const int& nMaxWidth);      //����xp��������
	void DrawWin7StyleBar(CDC* pDC, const RECT& rectClient, const int& nMaxWidth);      //����win7��������
	void DrawText(CDC* pDC, const RECT& rectClient, const int& nMaxWidth);                                                                       //��������
	void DrawXPStep(CDC* pDC, const RECT& rectClient, const int& nMaxWidth);
	void DrawXPBackgroup(CDC* pDC, const RECT& rectClient);
	void FillXPStepRect(CDC* pDC, const RECT &rc,COLORREF clrStepStart,float rStep,float gStep,float bStep);
private:
	//////////////////////////////////////////////////
	// CMemDC - memory DC
	//
	// Author: Keith Rule
	// Email:  keithr@europa.com
	// Copyright 1996-1997, Keith Rule
	//
	// You may freely use or modify this code provided this
	// Copyright is included in all derived versions.
	//
	// History - 10/3/97 Fixed scrolling bug.
	//                   Added print support.
	//
	// This class implements a memory Device Context
#ifndef _MEMDC_H_
#define _MEMDC_H_	
	class CMemDC : public CDC
	{
	public:
		
		// constructor sets up the memory DC
		CMemDC(CDC* pDC) : CDC()
		{
			ASSERT(pDC != NULL);
			
			m_pDC = pDC;
			m_pOldBitmap = NULL;
			m_bMemDC = !pDC->IsPrinting();  //�ж�m_MemDC�Ƿ�Ϊ�����ڴ�DC     
			if (m_bMemDC)    // Create a Memory DC
			{
				pDC->GetClipBox(&m_rect);
				CreateCompatibleDC(pDC);
				m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
				m_pOldBitmap = SelectObject(&m_bitmap);
				SetWindowOrg(m_rect.left, m_rect.top);
			}
			else        // Make a copy of the relevent parts of the current DC for printing
			{
				m_bPrinting = pDC->m_bPrinting;
				m_hDC       = pDC->m_hDC;
				m_hAttribDC = pDC->m_hAttribDC;
			}
		}
		// Destructor copies the contents of the mem DC to the original DC
		~CMemDC()
		{
			if (m_bMemDC) 
			{    
				// Copy the offscreen bitmap onto the screen.
				m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
					this, m_rect.left, m_rect.top, SRCCOPY);
				
				//Swap back the original bitmap.
				SelectObject(m_pOldBitmap);
			} 
			else 
			{
				// All we need to do is replace the DC with an illegal value,
				// this keeps us from accidently deleting the handles associated with
				// the CDC that was passed to the constructor.
				m_hDC = m_hAttribDC = NULL;
			}
		}
		
		// Allow usage as a pointer
		CMemDC* operator->() {return this;}
		// Allow usage as a pointer
		operator CMemDC*() {return this;}
		
	private:
		CBitmap  m_bitmap;      // Offscreen bitmap
		CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC
		CDC*     m_pDC;         // Saves CDC passed in constructor
		CRect    m_rect;        // Rectangle of drawing area.
		BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
	};	
#endif

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESSCTRL_H__4C78DBBE_EFB6_11D1_AB14_203E25000000__INCLUDED_)

