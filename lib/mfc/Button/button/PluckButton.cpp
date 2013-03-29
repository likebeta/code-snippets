// PluckButton.cpp : implementation file
//

#include "stdafx.h"
#include "OwnDrawButton.h"
#include "PluckButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPluckButton

CPluckButton::CPluckButton()
{
	m_style = KEY_STYLE_DOWN;
	b_InRect = false;
}

CPluckButton::~CPluckButton()
{
}


BEGIN_MESSAGE_MAP(CPluckButton, CButton)
	//{{AFX_MSG_MAP(CPluckButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPluckButton message handlers

void CPluckButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle( 0, BS_OWNERDRAW );		//���ð�ť����Ϊ�Ի�ʽ
}

void CPluckButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	m_ButRect = lpDrawItemStruct->rcItem;			//��ȡ��ť�ߴ�
	CPoint m_ptCentre = m_ButRect.CenterPoint();	//��ť���ĵ�
	switch( m_style )		//���ü�ͷ����
	{
	case KEY_STYLE_DOWN:
					m_pt[0].x = m_ptCentre.x-3;
					m_pt[0].y = m_ptCentre.y-2;
					m_pt[1].x = m_ptCentre.x+4;
					m_pt[1].y = m_ptCentre.y-2;
					m_pt[2].x = m_ptCentre.x;
					m_pt[2].y = m_ptCentre.y+2;
					break;
	case KEY_STYLE_UP:
					m_pt[0].x = m_ptCentre.x-4;
					m_pt[0].y = m_ptCentre.y+2;
					m_pt[1].x = m_ptCentre.x+4;
					m_pt[1].y = m_ptCentre.y+2;
					m_pt[2].x = m_ptCentre.x;
					m_pt[2].y = m_ptCentre.y-3;
					break;
	case KEY_STYLE_LEFT:
					m_pt[0].x = m_ptCentre.x+2;
					m_pt[0].y = m_ptCentre.y-4;
					m_pt[1].x = m_ptCentre.x+2;
					m_pt[1].y = m_ptCentre.y+4;
					m_pt[2].x = m_ptCentre.x-2;
					m_pt[2].y = m_ptCentre.y;
					break;
	case KEY_STYLE_RIGHT:
					m_pt[0].x = m_ptCentre.x-1;
					m_pt[0].y = m_ptCentre.y-4;
					m_pt[1].x = m_ptCentre.x-1;
					m_pt[1].y = m_ptCentre.y+4;
					m_pt[2].x = m_ptCentre.x+3;
					m_pt[2].y = m_ptCentre.y;
					break;
	}
	int nSavedDC = pDC->SaveDC();
	VERIFY( pDC );
	if( !(::GetWindowLong(m_hWnd,GWL_STYLE) & WS_DISABLED) )
	{
		if( !b_InRect )		//��겻�ڰ�ť��
		{
			NormalButton( pDC );
		}
		else		//����ڰ�ť��
		{
			PassButton( pDC );
		}
	}

	pDC->RestoreDC( nSavedDC );
}

//����ƶ���Ϣ����
void CPluckButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);

	if( !b_InRect || GetCapture()!=this )
	{
		b_InRect = true;
		SetCapture();
		Invalidate();
	}
	else
	{
		CRect rc;
		this->GetClientRect( &rc );
		if ( !rc.PtInRect(point) )
		{
			b_InRect = false;
			ReleaseCapture();
			Invalidate();
		}
	}
}

//��갴����Ϣ����
void CPluckButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	switch( m_style )	//���ð�ť���
	{
	case KEY_STYLE_DOWN:	m_style = KEY_STYLE_UP;		break;
	case KEY_STYLE_UP:		m_style = KEY_STYLE_DOWN;	break;
	case KEY_STYLE_LEFT:	m_style = KEY_STYLE_RIGHT;	break;
	case KEY_STYLE_RIGHT:	m_style = KEY_STYLE_LEFT;	break;
	}
	CButton::OnLButtonDown(nFlags, point);
	Invalidate();
}

//��������ť
void CPluckButton::NormalButton(CDC *pDC)
{
	CBrush Brush;
	Brush.CreateSolidBrush( RGB(178,189,200) );
	pDC->SelectObject( &Brush );
	pDC->Rectangle( &m_ButRect );		//������
	Brush.Detach();
	pDC->SelectStockObject( WHITE_BRUSH );
	CRgn rgn;
	rgn.CreatePolygonRgn( m_pt, 3, ALTERNATE );
	pDC->PaintRgn( &rgn );				//����ͷ
}

//����꾭��ʱ�İ�ť
void CPluckButton::PassButton(CDC *pDC)
{
	CBrush Brush;
	Brush.CreateSolidBrush( RGB(238,238,235) );
	pDC->SelectObject( &Brush );
	pDC->Rectangle( &m_ButRect );		//������
	Brush.Detach();
	pDC->SelectStockObject( BLACK_BRUSH );
	CRgn rgn;
	rgn.CreatePolygonRgn( m_pt, 3, ALTERNATE );
	pDC->PaintRgn( &rgn );				//����ͷ
}

//////////////////////////////////////////////////////////////////////
//�ӿں���

//���ð�ť���
void CPluckButton::SetPluckButStyle(int Style)
{
	m_style = Style;
}

//��ȡ��ť���
int CPluckButton::GetPluckButStyle()
{
	return m_style;
}