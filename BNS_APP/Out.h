#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� COlePropertyPage��"
#endif 

// COut : ����ҳ�Ի���

class COut : public COlePropertyPage
{
	DECLARE_DYNCREATE(COut)
	DECLARE_OLECREATE_EX(COut)

// ���캯��
public:
	COut();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};
