// BNS_APP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBNS_APPApp:
// �йش����ʵ�֣������ BNS_APP.cpp
//

class CBNS_APPApp : public CWinApp
{
public:
	CBNS_APPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBNS_APPApp theApp;