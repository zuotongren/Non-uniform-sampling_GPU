// Out.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BNS_APP.h"
#include "Out.h"


// COut �Ի���

IMPLEMENT_DYNCREATE(COut, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(COut, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

// {579F2844-8045-43A8-B145-FD1BD5D53629}
IMPLEMENT_OLECREATE_EX(COut, "BNS_APP.Out",
	0x579f2844, 0x8045, 0x43a8, 0xb1, 0x45, 0xfd, 0x1b, 0xd5, 0xd5, 0x36, 0x29)



// COut::COutFactory::UpdateRegistry -
// ��ӻ��Ƴ� COut ��ϵͳע�����

BOOL COut::COutFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ����ҳ���͵��ַ�����Դ���� ID �滻����ġ�0����

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, 0);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// COut::COut - ���캯��

// TODO: ����ҳ������ַ�����Դ���� ID �滻����ġ�0����

COut::COut() :
	COlePropertyPage(IDD, 0)
{

}



// COut::DoDataExchange - ��ҳ�����Լ��ƶ�����

void COut::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// COut ��Ϣ�������
