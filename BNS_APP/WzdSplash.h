///****************************************************//
//***  WzdSplash���ͷ�ļ��������������Ϊ�ڳ���Ŀ�ͷ���һ��flash������

//* �Գ�������в�û��ֱ�ӵ����á�
#pragma once


// CWzdSplash

class CWzdSplash : public CWnd
{
	DECLARE_DYNAMIC(CWzdSplash)

public:
	CWzdSplash();
	virtual ~CWzdSplash();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmap m_bitmap;
	void Create (UINT nBitmapID);
	
};


