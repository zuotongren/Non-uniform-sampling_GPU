// WzdSplash.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BNS_APP.h"
#include "WzdSplash.h"


// CWzdSplash

IMPLEMENT_DYNAMIC(CWzdSplash, CWnd)

CWzdSplash::CWzdSplash()
{

}

CWzdSplash::~CWzdSplash()
{
}


BEGIN_MESSAGE_MAP(CWzdSplash, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()
// CWzdSplash ��Ϣ�������
///////////////////////////////////
//
//���ܣ�����λͼ��Ϣ
//
///////////////////////////////////////
void CWzdSplash::Create(UINT nBitmapID)
{
	m_bitmap.LoadBitmap(nBitmapID);
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
    CreateEx(0,AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),NULL, WS_POPUP | WS_VISIBLE, 0, 0, bitmap.bmWidth, bitmap.bmHeight, NULL , NULL);  
    
}
void CWzdSplash::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);
	dc.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,&dcComp,0,0,SRCCOPY);
}
//******************************************************//
//
//
//���ܣ���ʱ����Ӧ����
//
//********************************************************//
void CWzdSplash::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnTimer(nIDEvent);
	KillTimer(0);          //�رն�ʱ��
	DestroyWindow();       //��������

}
