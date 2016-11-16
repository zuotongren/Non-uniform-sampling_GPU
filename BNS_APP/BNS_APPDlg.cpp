// BNS_APPDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "BNS_APP.h"
#include "BNS_APPDlg.h"
#include "cdib.h"
#include <fstream>
#include "math.h"
#include "Windows.h"
#include "WzdSplash.h"
#include "Out.h"
#include "afx.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_LINE	300
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBNS_APPDlg �Ի���




CBNS_APPDlg::CBNS_APPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBNS_APPDlg::IDD, pParent)
	, m_EDIT_BN(0)
	, m_EDIT_EN(0)
	, m_speed(0)
	, m_Now(0)
	, m_CompensatePhase(FALSE)
	, m_L0(0)
	, m_i0(0)
	, m_r0(0)
	, m_Width_m(0)
	, m_Len_m(0)
	, m_frame(0)
	, m_T(0)
	, m_now_frame(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBNS_APPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_Picture);
	DDX_Text(pDX, IDC_EDIT_Begin_Num, m_EDIT_BN);
	DDX_Text(pDX, IDC_EDIT_End_Num, m_EDIT_EN);
	DDX_Text(pDX, IDC_EDIT_Time, m_speed);
	DDX_Text(pDX, IDC_EDIT_Now, m_Now);
	DDX_Control(pDX, IDC_COMPENSATE_PHASE_CHECKBOX, m_CompensatePhaseCheckbox);
	DDX_Control(pDX, IDC_START_STOP_BUTTON, m_StartStopButton);
	DDX_Control(pDX, IDC_SLM_PWR_BUTTON, m_SlmPwrButton);
	DDX_Check(pDX, IDC_COMPENSATE_PHASE_CHECKBOX, m_CompensatePhase);
	DDX_Control(pDX, IDC_BUTTON_UP, m_UP);
	DDX_Control(pDX, IDC_BUTTON_Down, m_DOWN);
	DDX_Text(pDX, IDC_EDIT1, m_L0);
	DDX_Text(pDX, IDC_EDIT2, m_i0);
	DDX_Text(pDX, IDC_EDIT3, m_r0);
	DDX_Text(pDX, IDC_EDIT8, m_Width_m);
	DDX_Text(pDX, IDC_EDIT10, m_Len_m);
	DDX_Text(pDX, IDC_EDIT9, m_frame);
	DDX_Control(pDX, IDC_BUTTON_YuSheZhi, m_Prepare_value);
	DDX_Control(pDX, IDC_BUTTON_Open, m_Open);
	DDX_Control(pDX, IDC_BUTTON_KaiShi, m_Begin);
	DDX_Control(pDX, IDC_BUTTON_Out, m_out);
	DDX_Control(pDX, IDC_BUTTON_Save, m_Save);
	DDX_Control(pDX, IDC_ADD, m_Load);
	DDX_Control(pDX, IDC_BUTTON_Add, m_Add);
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	DDX_Text(pDX, IDC_EDIT5, m_now_frame);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CBNS_APPDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Open, &CBNS_APPDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_START_STOP_BUTTON, &CBNS_APPDlg::OnBnClickedStartStopButton)
	ON_BN_CLICKED(IDC_SLM_PWR_BUTTON, &CBNS_APPDlg::OnBnClickedSlmPwrButton)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CBNS_APPDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_Down, &CBNS_APPDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_COMPENSATE_PHASE_CHECKBOX, &CBNS_APPDlg::OnBnClickedCompensatePhaseCheckbox)
//	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_EDIT_Begin_Num, &CBNS_APPDlg::OnEnChangeEditBeginNum)
//	ON_EN_CHANGE(IDC_EDIT_End_Num, &CBNS_APPDlg::OnEnChangeEditEndNum)
	ON_BN_CLICKED(IDC_BUTTON_YuSheZhi, &CBNS_APPDlg::OnBnClickedButtonYushezhi)
	ON_BN_CLICKED(IDC_BUTTON_KaiShi, &CBNS_APPDlg::OnBnClickedButtonKaishi)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CBNS_APPDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_Out, &CBNS_APPDlg::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_ADD, &CBNS_APPDlg::OnBnClickedAdd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Add, &CBNS_APPDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CBNS_APPDlg::OnBnClickedButtonGo)
END_MESSAGE_MAP()


// CBNS_APPDlg ��Ϣ�������

BOOL CBNS_APPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    CWzdSplash wndSplash;                     
	wndSplash.Create(IDB_BITMAP1);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();
	wndSplash.SetTimer(0,40000,NULL);
	Sleep(2000);
	srand((unsigned)time(NULL));                //ʱ��������
	m_hicn1=AfxGetApp()->LoadIcon(IDI_ICON1);   
	m_Add.SetIcon(m_hicn1);
	m_hicn2=AfxGetApp()->LoadIcon(IDI_ICON2);
	m_DOWN.SetIcon(m_hicn2);
	Page_0=0;
	key=false;
	Down_Up=1;
	Pixel=1;
	Mosaic_Pixel=Mosaic;
 
	INFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256*sizeof(RGBQUAD));    //BMP�ļ���Ϣͷ����
	(*INFO).bmiHeader.biSize=0x28;
	(*INFO).bmiHeader.biWidth=512;
	(*INFO).bmiHeader.biHeight=512;
	(*INFO).bmiHeader.biPlanes=0x01;
	(*INFO).bmiHeader.biBitCount=0x08;
	(*INFO).bmiHeader.biCompression=0x00;
	(*INFO).bmiHeader.biSizeImage=0x00;
	(*INFO).bmiHeader.biXPelsPerMeter=0x800;
	(*INFO).bmiHeader.biYPelsPerMeter=0x800;
	(*INFO).bmiHeader.biClrUsed=0x00;
	(*INFO).bmiHeader.biClrImportant=0x00;
	for(int i=0;i<256;i++)
	{
		(*INFO).bmiColors[i].rgbRed=i;
		(*INFO).bmiColors[i].rgbGreen=i;
		(*INFO).bmiColors[i].rgbBlue=i;
		(*INFO).bmiColors[i].rgbReserved=0;
	}



    m_StartStopButton.EnableWindow(false);
	m_SlmPwrButton.EnableWindow(false);
	m_UP.EnableWindow(false);
	m_DOWN.EnableWindow(false);
	m_Add.EnableWindow(false);
	m_Save.EnableWindow(false);
	m_Load.EnableWindow(false);
	m_out.EnableWindow(false);
	UpdateData(false);
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBNS_APPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBNS_APPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBNS_APPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////
//
//��������OnBnClickedButtonOpen()
//
//������������
//
//�������ܣ���һ������ʾ���ļ��������һЩ��Ϣ�����ļ������ļ���λ����
//
//��������ֵ����
//
////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDC *pDC;             //����һ�����ָ��
	//pDC=m_Picture.GetDC();//�õ�Picture control �ľ�� 
	biWidth=POINT;        //�õ���λ���Ĵ�С��Ϣ
	biHeight=POINT;
    TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*|��λ���ļ���*.4wf��|*.4wf||");   	 // ���ù�����
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE, NULL, NULL,0, szFilter, this);   //����һ��CFileDiloge����  
  
    // ��ʾ���ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   //��������ļ�
	{
	   // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭���� 
		strFilePath = fileDlg.GetPathName(); //�õ��ļ�·����
		SetDlgItemText(IDC_EDIT_Path, strFilePath); //���ļ�·��������ӡ������
	}

	//----�Զ�д��ʽ����Ҫ���ص��ļ�����Ҫ���ص��ļ����Զ�������ʽ�洢�ģ���----//

	//----���˳���򿪡��򣬽����ݼ��ص��ڴ��С�

	if (file.Open(strFilePath,  CFile::modeRead))
	{
			file.SeekToBegin();
			Page=(file.GetLength()-sizeof(file_head))/(8*biWidth)-511;     //�����λ��֡��
			CS_Page.Format(_T("file long %d "),Page);       //��ӡ��λ��֡����Ϣ
			SetDlgItemText(IDC_EDIT_Page,CS_Page);  

            //----      ����̬��������ڴ档ʵ������һ����ά������--------//

            //----  ��СΪ��Page*biWidth*biHeigth�����������е����-------//

            //----  һ���ڶ�������֮ǰ�����ǲ���֪��Ҫ�����������------//

            //----- ���ö�̬������Խ�ʡ�ռ䣬����֤����İ�ȫ��----------//

		    // ---- ������ʹ�ý���֮�󣬿��Ծ�����ͷ��ڴ�ռ䡣----------//

			ColorBuff=new double[512*(Page+511)];           
			/*for(int i=0;i<Page;i++)                        
			{                                              
				ColorBuff[i]=new unsigned char[biWidth*biHeight];
			                                              
			}*/
			file.Read(&file_head,sizeof(file_head));
			file.Read(ColorBuff,8*512*(Page+511));
			m_L0=file_head.m_L0;
	        m_i0=file_head.m_i0;
	        m_r0=file_head.m_r0;
	        m_speed=file_head.m_speed;
	        m_frame=file_head.m_frame;
	        m_Width_m=file_head.m_Width_m;
	        m_Len_m=file_head.m_Len_m;
	        m_T=file_head.m_T;
			file.Close();
			UpdateData(Up);
			if(m_Width<POINT)                  //����һ��512*512�����飬���ڵ����ɵ���λ��С��512ʱ���⽫��ת��Ϊ512*512
			{
				ColorBuff_512=new unsigned __int8[POINT*POINT];
			    for(int i=0;i<POINT*POINT;i++)
			    {
				ColorBuff_512[i]=0;
			    }

			}
			key=true;//��һ��bool���ͱ�������Ϊtrue ֪ͨϵͳ�Ѿ�Ϊ��̬��������ڴ�
			MessageBox(_T("ͼƬװ����ɣ�"),MB_OK,MB_ICONASTERISK);
			m_Begin.EnableWindow(false);//������ʼ����ť����Ϊ������
	        m_Prepare_value.EnableWindow(false);
	        m_SlmPwrButton.EnableWindow(false);
			m_UP.EnableWindow(true);
			m_DOWN.EnableWindow(true);
			m_Add.EnableWindow(true);
			m_out.EnableWindow(true);
			m_Load.EnableWindow(true);


			//���ļ��������֮���ϵ簴ť�Ϳ�������������
	}

}
//////////////////////////////////////////////////////////////////////
//
//��������OnBnClickedStartStopButton()
//
//��������
//
//����ֵ����
//
//�������ܣ���ʼ/ֹͣ����ͼƬ��ť
//
//
////////////////////////////////////////////////////////////////////

void CBNS_APPDlg::OnBnClickedStartStopButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString SpSt;
	m_StartStopButton.GetWindowText(SpSt);
	//����һ��CString����������ÿ�ʼ/ֹͣ��ť��״̬��Ϣ
	UpdateData(Down);//����������õĲ������ݸ��������
	Page_0=m_Now;    //Page_0�����������Ҫ�����ǽ�Ҫ��ʾ��λ���ı�š�����Page_0==0����Ҫ��ʾ����λ�����ǵ�һ����λ����
	
    //-----��ȷ����ťΪ��START������ʼ��ʱ����ʼ������λ�����ݡ�--//
	if (0==SpSt.Compare(_T("START")))  
	{
		if(m_speed==0&&m_frame==0)
		{
			MessageBox(_T("��ѡ��ʱ��ʱ��") ,MB_OK,MB_ICONEXCLAMATION);//���û���趨��ʱ��ʱ�䣬�����ѣ������ء�
	        return;
	    }
		Pixel=floor((1/m_frame)*(POINT/m_Width_m)*m_speed);  //���ݷ��ٺ�֡�ʻ����������λ�������
	    m_SlmPwrButton.EnableWindow(false);
		m_Add.EnableWindow(false);
		m_UP.EnableWindow(false);
		m_DOWN.EnableWindow(false);

		//-------��λ����ʾ��Ϣ���������ǲ��Գ�ֵ����ǿ��Ҫ���û��趨�ġ�---//

		//---�������ݲ����ܳ�����0--Page�������Χ�����Գ���Դ����˴���----//

		if(m_EDIT_BN==0&&m_EDIT_EN==0)   //���δ���г�ֵ�趨���򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-1��
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	   /*else if(m_EDIT_EN>=m_EDIT_BN)
	       {
			   MessageBox(_T("ע�⣺������Ҫ���ڿ�ʼ�ţ�����") ,MB_OK,MB_ICONEXCLAMATION);
			   return;
		   }*/
	   else if(m_EDIT_BN>=Page)//�����ֵ����ֵ������Page-�����򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-1��
	       {
			   m_EDIT_BN=0;
			   m_EDIT_EN=Page-1;
			   UpdateData(false);
		       Page_0=m_EDIT_BN;
		       Page_end=m_EDIT_EN;
		    }                                 //
	   Page_0=m_EDIT_BN;
	   Page_end=m_EDIT_EN;
	   while(Page_0< m_EDIT_EN)//Page_0 != m_EDIT_EN
		{
			QueryPerformanceCounter(&M_Begin);//�õ�ϵͳ��ǰ������ֵ
			if(!QueryPerformanceFrequency(&Frequence))//�õ�ϵͳʱ��Ƶ��
			{
				MessageBox(_T("�Բ������ĵ��Բ�֧�ָ߾��ȼ�������"),MB_OK,MB_ICONEXCLAMATION);
				return;
			}

			TimeToL.QuadPart= Frequence.QuadPart*(1000000/m_frame-2600)/1000000;//ͨ��Ƶ�ʻ���΢��������Ӧ����������CPU�йأ���1��=1000000΢�
			My_Delay(TimeToL);                                  //��ʱ ��λ��΢��
			LoadHardBoard();                                    //������λ����Ӳ��
			QueryPerformanceCounter(&M_End);                    //�õ�ϵͳ��ǰ������ֵ
			m_now_frame=int ((Frequence.QuadPart)*1.0/((M_End.QuadPart-M_Begin.QuadPart)*1.0));//�õ���λ������֡�ʡ�֡�ʵ��Ǽ��㹫ʽΪ��֡��=ϵͳƵ��/��������ֵ����
			UpdateData(false);
		}

		m_StartStopButton.SetWindowText(_T("STOP"));
	  
	}
	if (0==SpSt.Compare(_T("STOP")))  
	{
		m_StartStopButton.SetWindowText(_T("START"));
    	m_SlmPwrButton.EnableWindow(true);
		m_UP.EnableWindow(true);
		m_DOWN.EnableWindow(true);
		m_Save.EnableWindow(true);
	}

}

///////////////////////////////////////////////////////////
//
//
//
//
//
//
//���ܣ���Դ���ذ�ť������Ӳ�����ϵ�/���繦�ܡ�
//
//
/////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedSlmPwrButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	for(int board = 0; board < NumBoards; board++)    //���Ӳ������������һ�����ϵ�/���������
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		bool bPowerOn = (bool)!pBoard->theBoard->GetPower();//���Ӳ����Դ���
		pBoard->theBoard->SetPower(bPowerOn);               //�ϵ�/����

		if(pBoard->theBoard->GetPower())
		{
				m_SlmPwrButton.SetWindowText(_T("OFF POWER"));
		    m_StartStopButton.EnableWindow(true);
			m_out.EnableWindow(false);
			m_UP.EnableWindow(false);
			m_DOWN.EnableWindow(false);
		}
		
		else
		{
			m_SlmPwrButton.SetWindowText(_T("ON POWER"));
		    m_StartStopButton.EnableWindow(false);
			m_out.EnableWindow(true);
			m_UP.EnableWindow(true);
			m_DOWN.EnableWindow(true);

		}
			
	}

}

void CBNS_APPDlg::OnBnClickedButtonGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(Down);
	if(m_frame==0)
		{
			MessageBox(_T("��ѡ��֡��") ,MB_OK,MB_ICONEXCLAMATION);//���û���趨��ʱ��ʱ�䣬�����ѣ������ء�
	        return;
	    }
	if(m_speed==0)
		{
			MessageBox(_T("��ѡ�����") ,MB_OK,MB_ICONEXCLAMATION);//���û���趨��ʱ��ʱ�䣬�����ѣ������ء�
	        return;
	    }
	if(m_Width_m==0)
		{
			MessageBox(_T("��ѡ����λ�����") ,MB_OK,MB_ICONEXCLAMATION);//���û���趨��ʱ��ʱ�䣬�����ѣ������ء�
	        return;
	    }

	Pixel=(1/m_frame)*(POINT/m_Width_m)*m_speed;
	CString Stop_Up;
	m_UP.GetWindowText(Stop_Up);
	//����һ��CString����������ÿ�ʼ/ֹͣ��ť��״̬��Ϣ
	if (0==Stop_Up.Compare(_T("Go")))  
	{
		SetTimer(1,floor(1000.0/m_frame),NULL); //����IDΪ1�Ķ�ʱ������ʱ����λΪ ms;
		m_UP.SetWindowText(_T("STOP"));
	}
	if (0==Stop_Up.Compare(_T("STOP")))  
	{
		KillTimer(1);
		m_UP.SetWindowText(_T("Go"));
	}

}
void CBNS_APPDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(true);
	//QueryPerformanceFrequency(&Frequence);//�õ�ϵͳʱ��Ƶ��
	//QueryPerformanceCounter(&M_Begin);//�õ�ϵͳ��ǰ������ֵ
	//QueryPerformanceCounter(&M_End);
	//m_frame=((M_End.QuadPart-M_Begin.QuadPart)*1.0)/(Frequence.QuadPart*1.0);//�õ���λ������֡�ʡ�֡�ʵ��Ǽ��㹫ʽΪ��֡��=ϵͳƵ��/��������ֵ����
	// 
	Down_Up=1;
	Page_0=m_Now;
	Page_0++;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //���δ���г�ֵ�趨���򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-1��
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0>m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0>m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
	
}

void CBNS_APPDlg::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Down_Up=0;
	Page_0=m_Now;
	Page_0--;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //���δ���г�ֵ�趨���򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-1��
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0<m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0<m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}

	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
}

void CBNS_APPDlg::OnBnClickedCompensatePhaseCheckbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

}
///////////////////////////////////////////////////////////////////
//
//��������ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512)
//
//����������unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512 
//         
//
//�������ܣ���һ��С��POINT��#define POINT 512������λ��ת��Ϊ��˵��ճ�����ܸ�Ϊǡ���㣩POINT����λ����
//
//
//��������ֵ����
//
//
//////////////////////////////////////////////////////////////////
void CBNS_APPDlg::ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512)
{   
	int i,j,s=0;
    for(i=(POINT-biWidth)/2; i<(POINT+biWidth)/2; i++)
      for( j=(POINT-biHeight)/2 ; j<(POINT+biHeight)/2 ; j++)

         ColorBuff_512[i*POINT+j]=ColorBuff1[s++];
}


//////////////////////////////////////////////////////////////////////////////////
//
//  LoadSequence()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function will load a series of two images to the PCI board memory. The
//			 first image is written to the first frame of memory in the hardware, and the
//			 second image is written to the second frame of memory in the hardware. 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void  CBNS_APPDlg::LoadSequence(double *ColorBuff1)
{
	unsigned __int8  *ColorBuff2;
	ColorBuff2=new unsigned __int8[POINT*POINT];

	for(int j=0;j<POINT*POINT;j++)
	{
		ColorBuff2[j]=char(255*ColorBuff1[j]);
	}
	int i;

	//loop through each PCIe board found, read in the calibrations for that SLM
	//as well as the images in the sequence list, and store the merged image/calibration
	//data in an array that will later be referenced
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		//if the user has a nematic SLM and the user is viewing the SLM through an interferometer,
		//then the user has the option to correct for SLM imperfections by applying a predetermined 
		//phase compensation. BNS calibrates every SLM before shipping, so every SLM ships with its own
		//custom phase correction file. This step is either reading in that correction file, or setting
		//the data in the array to 0 for users that don't want to correct or for users with amplitude
		//devices
		if(m_CompensatePhase)
		{
			ReadAndScaleBitmap(pBoard->PhaseCompensationData, pBoard->PhaseCompensationFileName);
			ReadAndScaleBitmap(pBoard->SystemPhaseCompensationData, pBoard->SystemPhaseCompensationFileName);
		}
		else
		{
			memset(pBoard->PhaseCompensationData, 0, ImgHeight*ImgWidth);
			memset(pBoard->SystemPhaseCompensationData, 0, ImgHeight*ImgWidth);
		}
        if(m_Width<ImgHeight)
		{

			ChangeTo512(ColorBuff2,ColorBuff_512);
			int total;
		//Superimpose the SLM phase compensation, the system phase compensation, and
		//the image data and then store the image in the FrameOne Array
		    for(i = 0; i< ImgHeight*ImgWidth; i++)
		      {
			        total = ColorBuff_512[i] + 
					pBoard->PhaseCompensationData[i] + 
					pBoard->SystemPhaseCompensationData[i];
			        ColorBuff_512[i] = total%256;
		      }
		    pBoard->theBoard->WriteFrameBuffer(ColorBuff_512);
		}
		else 
		{
			int total;
		//Superimpose the SLM phase compensation, the system phase compensation, and
		//the image data and then store the image in the FrameOne Array
		    for(i = 0; i< ImgHeight*ImgWidth; i++)
		     {
			        total = ColorBuff1[i] + 
					pBoard->PhaseCompensationData[i] + 
					pBoard->SystemPhaseCompensationData[i];
			        ColorBuff1[i] = total%256;
		     }
		    pBoard->theBoard->WriteFrameBuffer(ColorBuff2);

		}
		
		
	}
}


//////////////////////////////////////////////////////////////////////////////////
//
//  OnClose()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function is used clean up everything at the close of the program.
//			 This function is called when the user clicks on the little X in the 
//			 upper corner of the screen. MAKE SURE THAT THE SLM POWER IS OFF 
//			 BEFORE LEAVING THE PROGRAM!!!
//			 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::ToOnClose() 
{
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		//first set the SLM power off, then deconstruct the board class
		pBoard->theBoard->SetPower(false);
		if (pBoard->theBoard)
			delete pBoard->theBoard;

		//clean up allocated memory to avoid memory leaks (this isn't technically necessary,
		//but it is good practice)
		delete []pBoard->PhaseCompensationData;
		delete []pBoard->SystemPhaseCompensationData;
		delete []pBoard->LUT;
		delete pBoard;
	}

	//close out the dialog
	//CDialog::OnClose();
}
//////////////////////////////////////////////////////////////////////////////////
//
//  OnOK()
//
//  Inputs: none
//
//  Returns: none
//
//  Purpose: This function is used so that you don't accidentally exit the program
//			 by hitting the enter button. This function now causes nothing to happen if enter
//			 is clicked. It forces the user to purposely exit the program using
//			 the exit button which will ensure that the proper shutdown procedure
//			 of the hardware is followed. This will prevent possible accidental damage
//			 to the hardware and or SLM
//			 
//
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnOK() 
{

}


//////////////////////////////////////////////////////////////////////////////////
//
//  ReadAndScaleBitmap()
//
//  Inputs: empty array to fill, the file name to read in
//
//  Returns: true if no errors, otherwise false
//
//  Purpose: This function will read in the bitmap and x axis flip it. If there is a 
//			 problem reading in the bitmap, then we fill the array with zeros. This 
//			 function then calls ScaleBitmap so that we can scale the 
//			 bitmap to an images size based on the board type.
//			 ��ȡ.BMP��ʽ��ͼƬ��Ϣ
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
bool CBNS_APPDlg::ReadAndScaleBitmap(unsigned char *Image, CString fileName)      //�õ�ͼƬ������ֵ
{
	int width, height, bytespixel;

	//need a tmpImage because we cannot assume that the bitmap we 
	//read in will be of the correct dimensions
	unsigned char* tmpImage;

	//get a handle to our file
	CFile *pFile = new CFile();
	if (pFile == NULL)
		MessageBox(_T("Error allocating memory for pFile,ReadandScaleBitmap"), _T("MEMORY ERROR"), MB_ICONERROR);
	//if it is a bmp file and we can open it
	if (pFile->Open(fileName, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		//read in the bitmap dimensions
		CDib dib;
		dib.Read(pFile);
		width = dib.GetDimensions().cx;
		height = dib.GetDimensions().cy;
		bytespixel = dib.m_lpBMIH->biBitCount;                  //ɫ��ֵ
		pFile->Close();
		delete pFile;
		
		//allocate our tmp array based on the bitmap dimensions
		tmpImage = new unsigned char[height*width];

		//flip the image right side up (INVERT)
		for (int i=0; i<height; i++)
		{
			for (int j=0; j<width; j++)
			{
				if (bytespixel == 4)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*(height/2)+(j/2)];
				if (bytespixel == 8)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*height+j];
				if (bytespixel == 16)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*2*height+j*2];
				if (bytespixel == 24)
					tmpImage[((height-1)-i)*height+j] = dib.m_lpImage[i*3*height+j*3];
			}
		}
 
		dib.~CDib();
	}
	//we could not open the file or the file was not a .bmp file
	else 
	{
		//depending on if we are trying to read a bitmap to download
		//or if we are trying to read it for the screen, memset
		//the array to zero and return false
		memset(Image, '0', ImgWidth*ImgHeight);
		return false;
	}

	//scale the bitmap
	unsigned char* ScaledImage = ScaleBitmap(tmpImage, height, ImgHeight);

	//copy the scaled bitmap into the array passed into the function
	memcpy(Image, ScaledImage, ImgWidth*ImgHeight);

	//delete our tmp array to avoid mem leaks
	delete []tmpImage;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
//
//  ScaleBitmap()
//
//  Inputs: none
//
//  Returns: the array that holds the image to scale, the current bitmap size, the final
//			 bitmap size
//
//  Purpose: This will scale the bitmap from whatever size it is initially to a 128x128
//			 if load is set to false. Otherwise the images is scaled to a 512x512 if 
//			 the board type is set to 512ASLM or 256x256 if the board type is set to
//			 256ASLM.
//           ��ͼƬ��Ϣ�����������ѹ��
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
unsigned char * CBNS_APPDlg::ScaleBitmap(unsigned char* InvertedImage, int BitmapSize, int FinalBitmapSize)
{	
	int height = BitmapSize;
	int width = BitmapSize;

	//make an array to hold the scaled bitmap
	unsigned char* ScaledImage = new unsigned char[FinalBitmapSize*FinalBitmapSize];
	if (ScaledImage == NULL)
		AfxMessageBox(_T("Error allocating memory for CFile,LoadSIFRec"), MB_OK);
	//EXPAND THE IMAGE to FinalBitmapSize
	if (height < FinalBitmapSize)
	{
		int r, c, row, col, Index;
		int Scale = FinalBitmapSize/height;

		for (row = 0; row < height; row++)
		{
			for (col = 0; col < width; col++)
			{
				for (r = 0; r < Scale; r++)
				{
					for(c = 0; c < Scale; c++)
					{
						Index = ((row*Scale)+r)*FinalBitmapSize + (col*Scale)+c;
						ScaledImage[Index] = InvertedImage[row*height+col];
					}
				}
			}
		}
	}
	//SHRINK IT DOWN
	else if (height > FinalBitmapSize)
	{
		int Scale = height/FinalBitmapSize;
		for (int i = 0; i<height; i+=Scale)
			for (int j=0; j<width; j+=Scale)
				ScaledImage[(i/Scale)+FinalBitmapSize*(j/Scale)] = InvertedImage[i+height*j];
	}
	//if the image is the correct size already, just copy the array over
	else
		memcpy(ScaledImage, InvertedImage, FinalBitmapSize*FinalBitmapSize);
	
	return(ScaledImage);

}

//////////////////////////////////////////////////////////////////////////////////
//
//  ReadLUTFile()
//
//  Inputs: the name of the LUT file to read, and an array to store the file in
//
//  Returns: true if read successfully, false if linear.lut was generated
//
//  Purpose: This will read in the LUT file. This is a look up table that we process 
//			 our images through. What it does is map the pixel values to the values
//			 specified by the LUT. For example with Linear.LUT we have a direct 
//			 mapping, so if the pixel value is 255, Linear.LUT will keep it at 255.
//			 However, skew.LUT will alter the pixel values. With skew.LUT if the 
//			 initial pixel value is 60, then it is mapped to a value of 139. 
//           ��ȡ���ı��ļ�
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
bool CBNS_APPDlg::ReadLUTFile( unsigned char *LUTBuf, CString LUTPath)
{
	FILE *stream;
	int i, seqnum, ReturnVal, tmpLUT;
	bool errorFlag;

	//set the error flag to indicate that there are no errors so far, and open
	//the LUT file
	errorFlag=false;
	stream = fopen("LUTPath","r");
	if ((stream != NULL)&&(errorFlag == false))
	{
		//read in all 256 values
		for (i=0; i<256; i++)
		{
		   ReturnVal=fscanf(stream, "%d %d", &seqnum, &tmpLUT); 
		   if (ReturnVal!=2 || seqnum!=i || tmpLUT<0 || tmpLUT>255)
		   {
			   	fclose(stream);
				errorFlag=true;
				break;
		   }
		   LUTBuf[i] = (unsigned char) tmpLUT;
		}
		fclose(stream);
	}
	//if there was an error reading in the LUT, then default to a linear LUT
	if ((stream == NULL)||(errorFlag == true))                    
	{
		for (i=0; i<256; i++)
			LUTBuf[i]=i;
		return false;
	}

	return TRUE;
}

////////////////////////////////////////////////////
//
//��������My_Delay(LARGE_INTEGER Interval)
//
//����������LARGE_INTEGER Interval
//
//�������ܣ�ʵ��΢�뼶��Ķ�ʱ
//
//��������ֵ����
//
/////////////////////////////////////////////////////////
void CBNS_APPDlg::My_Delay(LARGE_INTEGER Interval)
{
    LARGE_INTEGER pricious, current;                      
	QueryPerformanceCounter(&pricious);
	current = pricious;
	while(current.QuadPart -pricious.QuadPart < Interval.QuadPart)
		QueryPerformanceCounter(&current);
}
///////////////////////////////////////
//
//��������
//
//����������
//
//�������ܣ�����λ�����ݼ��ص�Ӳ���ϵĲ�����������ʵ�ֳ����������
//
//��������ֵ����
//
///////////////////////////////////////////////////
void CBNS_APPDlg::LoadHardBoard()
{
    if(Page_0==Page_end)
	{
		LoadSequence(ColorBuff+Page_0*512);
		Page_0=m_EDIT_BN;
	}
	else
	{
		LoadSequence(ColorBuff+Page_0*512);
		Page_0+=Pixel;
	}
	m_Now=Page_0;
	UpdateData(false);

}
////////////////////////////////////////
//
//��������OnTimer(UINT_PTR nIDEvent)
//
//������������Ϣ
//
//�������ܣ�ʵ�ֺ��뼶��Ķ�ʱ������Ϣ��ʽ������ʱ��������ִ����Ӧ����
//
//��������ֵ����
//
//
/////////////////////////////////////////////////
//void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	UpdateData(TRUE);
//	if(m_EDIT_BN==m_EDIT_EN)
//	{
//		Display_Picture(ColorBuff[Page_0]);
//		LoadSequence(ColorBuff[Page_0]);
//		KillTimer(1);
//	}
//	if(m_EDIT_BN>m_EDIT_EN)//������ʾ
//	{
//		if(Page_0==Page_end)
//		{
//			Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//			Page_0=m_EDIT_BN;
//		}
//		else
//		{
//		    Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//		    Page_0--;
//		}
//
//	}
//	if(m_EDIT_BN<m_EDIT_EN)
//	{
//		if(Page_0==Page_end)
//		{
//			Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//			Page_0=m_EDIT_BN;
//		}
//		else
//		{
//		    Display_Picture(ColorBuff[Page_0]);
//			LoadSequence(ColorBuff[Page_0]);
//		    Page_0++;
//		}
//	}
//
//	m_Now=Page_0;
//	UpdateData(false);
//	//CDialogEx::OnTimer(nIDEvent);
//}
///////////////////////////////////////////////////////////////////////////
//
//��������Display_Picture(unsigned __int8 *ColorBuff1)
//
//����������unsigned __int8 *ColorBuff1
//
//��������ֵ����
//
//
//�������ܣ�ʵ�ֶ�ȡͼ�����ݵ���ʾ
//
//
/////////////////////////////////////////////////////////////////////////////
void  CBNS_APPDlg::Display_Picture(double *ColorBuff1)
{
	unsigned __int8  *ColorBuff2;
	ColorBuff2=new unsigned __int8[POINT*POINT];

	for(int j=0;j<POINT*POINT;j++)
	{
		ColorBuff2[j]=char(255*(ColorBuff1[j]/(2*PI)));
	}
	CRect picture;
	CDC *pDC;
	m_Picture.GetClientRect(&picture);
	pDC=m_Picture.GetDC();
	 /*if((int(m_Width*m_Rr))<POINT)
		{
			ChangeTo512(ColorBuff2,ColorBuff_512);
			SetDIBitsToDevice(pDC->m_hDC, 0, 0, 512, 512, 0,0, 0, 512, ColorBuff_512, (BITMAPINFO *)INFO, 0);
	    }
	 else*/
    SetDIBitsToDevice(pDC->m_hDC, 0, 0, 512, 512, 0,0, 0, 512, ColorBuff2, (BITMAPINFO *)INFO, 0);
	delete []ColorBuff2;
}

void CBNS_APPDlg::OnBnClickedButtonYushezhi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString SPV;
	m_Prepare_value.GetWindowText(SPV);
	if(0==SPV.Compare(_T("Ԥ��ֵ")))
	{
		m_L0=10;
	    m_i0=0.01;
	    m_r0=0.1;
	    m_Width_m=1;
	    m_Len_m=1;
		m_speed=1;
		m_frame=100;
		m_T=1;
	    UpdateData(false);
	    m_Prepare_value.SetWindowText(_T("ȷ��"));
	}
	if(0==SPV.Compare(_T("ȷ��")))
	{
		UpdateData(true);
		m_Prepare_value.SetWindowText(_T("Ԥ��ֵ"));
	}


}

/***************************************************/
//
//��������integral(double(CNUFFTDlg:: *fun)(double), double a, double b)
//
//���������CNUFFTDlg:: *fun)(double), double a, double b ��������ںͻ������䣩
//
//����� ���ֽ����double���ͣ�
//
//����˵�������ֺ�����ʵ����ϵ������һ�����䣨�����������˵ĵ�Ի��ֽ����Ӱ�죩�ϵĻ���
//
//
/******************************************************/
double CBNS_APPDlg::integral(double(CBNS_APPDlg::*fun)(double), double a, double b)      //��fun��a��b���䶨����
{
	double s, h;
	int i;
	s = ((this->*fun)(a)+(this->*fun)(b)) / 2.0;
	int N = 100;
	h = (b - a) / N;
	for (i = 1; i<N; i++)
		s += (this->*fun)(a + i*h);
	return(s*h);
}
/**************************************************************/
//
//��������psdevalfunKolspf(double x)
//
//���������double x �������Ա�����
//
//�����double���͵ĺ��������
//
//�������ܣ�����ʵ��
//
/****************************************************************/
double CBNS_APPDlg::psdevalfunKolspf(double x)
{
	double Kolspf;
	//double r0 = 0.1;
	Kolspf = pow(0.023*pow(m_r0, (-5.0 / 3))*pow(x, (-11.0 / 3)), 0.5);
	return Kolspf;
}
/***************************************************************/
//
//
//
//
//
//
//
//
//
//
/****************************************************************/
long double CBNS_APPDlg::psdevalfun(double f0, double f1, double f2, int samppoints)
{

	double theoryresult = integral(&CBNS_APPDlg::psdevalfunKolspf, f0, f2);
	double discreresult = psdevalfunKolspf(f1)*(f2 - f0);
	double psderror = abs((theoryresult - discreresult)) / (samppoints / f1);
	return psderror;
}
void CBNS_APPDlg::OnBnClickedButtonKaishi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	////---------------------ע��˵����---------------------/////
	//    
	//              ������ע��λ���Ҳࡢ�ϲ�                /////
	//
	//         �Ҳ�ע���ԡ�//����ʼ��������ɫΪ��ɫ         /////
	//
	//                                 ��////////////////////// 
	//     �ϲ�ע���ԡ�//--..--//������  //
    //                                   :  ע������...
	//
	//                                   //////////////////////
	//
	//
	UpdateData(Down);
	if(m_L0==0||m_i0==0||m_r0==0||m_Len_m==0||m_Width_m==0||m_speed==0||m_frame==0)//���û�н��в������ã��ⷵ�ظó���ֱ�������������
	{
		MessageBox(_T("���ʼ������") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}
	file_head.m_L0=m_L0;
	file_head.m_i0=m_i0;
	file_head.m_r0=m_r0;
	file_head.m_speed=m_speed;
	file_head.m_frame=m_frame;
	file_head.m_Width_m=m_Width_m;
	file_head.m_Len_m=m_Len_m;
	file_head.m_T=m_T;

	Mosaic_Pixel=Mosaic;
	m_Len=int(m_Len_m*m_Rr);        //����λ���ĳ�����߶ȣ���λ �ף��任�����س߶ȣ���λ pixel��
	m_Width=int(m_Width_m*m_Rr);    //����λ���Ŀ�����߶ȣ���λ �ף��任�����س߶ȣ���λ pixel��
	double Efc_S=floor(m_Len/((1/m_frame)*(POINT/m_Width_m)*m_speed));  //���ݷ��ٺ�֡�ʼ���õ� һ������λ����Ч������
	T_Len= int(ceil(m_T*60/((1/m_frame)*Efc_S)));                       //������Ҫ������λ������Ҫ����ƴ�ӵ�ԭʼ��λ������
	m_Progress.SetRange32(0,T_Len+2);
	m_Progress.SetPos(0);
	m_Progress.SetStep(1); 
	double dx,dy;
	int Nf;
	double Dp;
	double ka0;
	double ka_H,ka_L;
	dy=dx=double(m_Width_m)/POINT;
	Nf=Samp_point/2-1;
	Dp=1000*m_Len_m;
	ka0=2*PI/m_L0;
	ka_L=2*PI/Dp;
	ka_H=PI/dx/1.1;

    double **f_area;
	f_area = new double *[Nf + 1];
	for (int i = 0; i <  Nf+ 1; i++)
	{
		f_area[i] = new double[Nf + 1];
	}
	double *f_sequence;
	f_sequence = new double [Nf + 1];


	Sequencer(f_sequence,f_area,ka_L,ka_H,Nf);
	double aaa=f_sequence[Nf];

	
	double *ka_dbside;
	ka_dbside = new double[2 * Nf + 2];
	for (int i = 0; i < Nf+1; i++)
	{
		ka_dbside[i] = -1*f_sequence[Nf - i];

	}
	for (int i = Nf; i < 2 * Nf+ 1; i++)
	{
		ka_dbside[i] = f_sequence[i-Nf];
		
	}
	ka_dbside[2 * Nf+ 1] = 0.0;

	m_Progress.StepIt();//������+1

	double xishu;
    xishu=0.490*(pow(m_r0, -(5.0 / 3.0)));
	double **PSD_sample;
	PSD_sample = new double *[(Nf + 1)];
	for (int i = 0; i < Nf+1; i++)
	{
		PSD_sample[i] = new double[Nf + 1];
	}
	for (int i = 0; i < Nf + 1; i++)
		for(int j=0;j< Nf + 1;j++)
	     {	
			 if(i==0 && j==0)
			 {
				 PSD_sample[0][0]=0.0;
			 }
			 else
			 {
                PSD_sample[i][j] =xishu*pow((pow(f_sequence[i],2.0)+pow(f_sequence[j],2.0)),-(11.0/6.0));      
			 }
		}	
	
	double **Spectrum_temp1;
	Spectrum_temp1 = new double *[Nf + 1];
	for (int i = 0; i < Nf + 1; i++)
	{
		Spectrum_temp1[i] = new double[Nf + 1];
	}
	for (int i = 0; i < Nf + 1; i++)
		for (int j = 0; j <  Nf + 1; j++)
		{
			Spectrum_temp1[i][j] = sqrt(PSD_sample[i][j]*f_area[i][j]);
		}
	double **Spectrum1;//��Spectrum_temp1[][]����һ��ƴ�� ��* *    ת��Ϊ��A~  A'
	                   //                                   * A��          A'~ A��

	Spectrum1 = new double*[2 *  Nf + 1];
	for (int i = 0; i < 2 *  Nf + 1; i++)
	{
		Spectrum1[i] = new double[2 *  Nf + 1];
	}
	for (int i = 0; i<2 *  Nf + 1; i++)
		for (int j = 0; j<2 *  Nf + 1; j++)
		{
			Spectrum1[i][j] = 0.0;//��ʼ��Ϊ0.0
		}
	for (int i = 0; i <  Nf + 1; i++)
		for (int j = 0; j <  Nf + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[ Nf - i][ Nf - j];
		}
	for (int i = 0; i <  Nf; i++)
		for (int j =  Nf + 1; j < 2 *  Nf + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[ Nf - i][j -  Nf];
		}
	for (int i =  Nf + 1; i < 2 *  Nf + 1; i++)
		for (int j = 0; j <  Nf + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[i -  Nf][ Nf - j];
		}
	for (int i =  Nf; i < 2 *  Nf + 1; i++)
		for (int j =  Nf; j < 2 *  Nf + 1; j++)
		{
			Spectrum1[i][j] = Spectrum_temp1[i -  Nf][j -  Nf];
		}
	for (int i = 0; i <  Nf + 1; i++)  //ɾ���м䲻��ʹ�õı�������
	{
		delete[]Spectrum_temp1[i];
	}
	delete[]Spectrum_temp1;


	m_Progress.StepIt();//������+1

	A_P = new double*[m_Width];    //ΪA_P���붯̬���飬A_P������������ɵ���λ�����ݵ�ָ��
	for (int i = 0; i<m_Width; i++)
	{
		A_P[i] = new double[m_Len];

	}
	double **End_AP;
	End_AP = new double*[POINT];
	for (int i = 0; i<POINT; i++)
	{
		End_AP[i] = new double[Mosaic_Pixel];
	}

	double *C_end;
	C_end=new double[Mosaic_Pixel];
	for(int k=0;k<Mosaic_Pixel;k++)
	{
		C_end[k]=pow(cos(PI*k/(2.0*Mosaic_Pixel)),2.0);//��λ��ĩβƴ��ϵ������
	}
	double *C_Bg;
	C_Bg=new double[Mosaic_Pixel];
	for(int k=0;k<Mosaic_Pixel;k++)
	{
		C_Bg[k]=pow(sin(PI*k/(2.0*Mosaic_Pixel)),2.0);//��λ����ͷƴ��ϵ������
	}

	Create_File();
	//Sleep(2000);
	//Create_File_1();
	//Sleep(2000);
	//Create_File_2();
	save_headata();

	/**************************************/
	//
	//�����forѭ��ʵ������λ�������ɺ�ƴ��
	//
	/*************************************/
	Mosaic_Pixel=0;
	for(int s=0;s<3;s++)
	{
		Summation(Spectrum1,ka_dbside, Nf);

	    save_data(A_P);	
		m_Progress.StepIt();//������+1
	}
	//Summation(Spectrum1,ka_dbside, Nf);
	//for (int i = m_Len-Mosaic_Pixel; i<m_Len; i++)
	//   for (int j = 0; j<POINT; j++)
	//	 {
	//		End_AP[j][i-(m_Len-Mosaic_Pixel)]=A_P[j][i];
	//	 }
	//save_data(A_P);	
 //   m_Progress.StepIt();//������+1
	//for(int kkk=1;kkk<50;kkk++)//T_Len-1
	// {
	//  Summation(Spectrum1,ka_dbside, Nf);
	//  for(int i=0;i<POINT;i++)
	//	 for(int j=0;j<Mosaic_Pixel;j++)
	//	   {
	//		 A_P[i][j]=A_P[i][j]*C_Bg[j]+End_AP[i][j]*C_end[j];
	//	   }
	//  for (int i = m_Len-Mosaic_Pixel; i<m_Len; i++)
	//	 for (int j = 0; j<POINT; j++)
	//	    {
 //             End_AP[j][i-(m_Len-Mosaic_Pixel)]=A_P[j][i];
	//	    }
	//save_data(A_P);
	//m_Progress.StepIt();//������+1
 //   }

	//Summation(Spectrum1,ka_dbside, Nf);
	//for(int i=0;i<POINT;i++)
	// for(int j=0;j<Mosaic_Pixel;j++)
	//	{
	//		A_P[i][j]=A_P[i][j]*C_Bg[j]+End_AP[i][j]*C_end[j];
	//    }
	//Mosaic_Pixel=0;
	//save_data(A_P);
	MessageBox(_T("�����������,�ѱ���...") ,MB_OK,MB_ICONEXCLAMATION);
	m_Prepare_value.EnableWindow(true);
	m_Open.EnableWindow(true);

//	m_Prepare_value.EnableWindow(false);
//	m_Open.EnableWindow(false);
//	m_progress.SetRange32(0,m_N*3+m_Zn*8);
//	m_progress.SetPos(0);
//	m_progress.SetStep(1); 
//	m_progress_file.SetRange32(0,m_N);
//	m_progress_file.SetPos(0);
//	m_progress_file.SetStep(1);		
//  m_progress.StepIt();     ////--N:0 Zn:1---///
//	progress.SetPos(m_N*3+m_Zn*8);
	  


}
/****************************************************************/
//
//
//
//
//
//
//
//
//
//
/*******************************************************************/
void CBNS_APPDlg::Summation(double **Spectrum1,double *ka_dbside, int Nf)

{
	double_complex **whiteno;
	whiteno = new double_complex *[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		whiteno[i] = new double_complex[2 * Nf + 1];
	}
	for (int i = 0; i<2 * Nf + 1; i++)
		for (int j = 0; j<2 * Nf + 1; j++)
		{
			whiteno[i][j].real = 0.0;
			whiteno[i][j].imag = 0.0;
		}

	Whitenoise(Nf, Nf, whiteno); //���ø�˹���������ɺ���
	double_complex **Rand_Spect;
	Rand_Spect = new double_complex*[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		Rand_Spect[i] = new double_complex[2 * Nf + 1];
	}
	for (int i = 0; i < 2 * Nf + 1; i++)
		for (int j = 0; j < 2 * Nf + 1; j++)
		{
			Rand_Spect[i][j].real = Spectrum1[i][j] * whiteno[i][j].real;
			Rand_Spect[i][j].imag = Spectrum1[i][j] * whiteno[i][j].imag;
		}

	/*double **Rand_Spect_real;
	Rand_Spect_real = new double*[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		Rand_Spect_real[i] = new double[2 * Nf + 1];
	}
	double **Rand_Spect_imag;
	Rand_Spect_imag = new double*[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		Rand_Spect_imag[i] = new double[2 * Nf + 1];
	}
	for (int i = 0; i < 2 * Nf + 1; i++)
		for (int j = 0; j < 2 * Nf + 1; j++)
		{
			Rand_Spect_real[i][j] = Rand_Spect[i][j].real;
			Rand_Spect_imag[i][j] = Rand_Spect[i][j].imag;
		}
	save_data_1(Rand_Spect_real);
	save_data_2(Rand_Spect_imag);*/
    double_complex **Rand_Spect_new;
	Rand_Spect_new = new double_complex*[2 * Nf + 2];
	for (int i = 0; i < 2 * Nf + 2; i++)
	{
		Rand_Spect_new[i] = new double_complex[2 * Nf + 2];
	}
	for (int i = 0; i < 2 * Nf + 1; i++)
		for (int j = 0; j < 2 * Nf + 1; j++)
		{
			Rand_Spect_new[i][j] = Rand_Spect[i][j];
		}
	for(int i=0;i<2 * Nf + 2;i++)
	{
		Rand_Spect_new[i][2 * Nf + 1].real = 0.0;
		Rand_Spect_new[i][2 * Nf + 1].imag = 0.0;
		Rand_Spect_new[2 * Nf + 1][i].real = 0.0;
		Rand_Spect_new[2 * Nf + 1][i].imag = 0.0;
	}
	//for (int i = 0; i < 2 * Nf + 1; i++)  //ɾ���м䲻��ʹ�õı�������
	//{
	//	delete[]Rand_Spect[i];
	//}
	//delete[]Rand_Spect;

	double_complex *Rand_Spect_Lin;
	Rand_Spect_Lin = new double_complex[(2 * Nf + 2)*(2 * Nf + 2)];
	for (int i = 0; i < 2 * Nf + 2; i++)
		for (int j = 0; j < 2 * Nf + 2 ; j++)
		{
			Rand_Spect_Lin[( 2 * Nf +2 )*i+j]=Rand_Spect_new[i][j];
		}
    

	for (int i = 0; i < 2 * Nf + 1; i++)  //ɾ���м䲻��ʹ�õı�������
	{
		delete[]whiteno[i];
	}
	delete[]whiteno;

	/*double ** Spematx;
	Spematx = new double*[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		Spematx[i] = new double[2 * Nf + 1];
	}
	for (int i = 0; i < 2 * Nf + 1; i++)
		for (int j = 0; j < 2 * Nf + 1; j++)
		{
			Spematx[i][j] = ka_dbside[i];
		}
	double ** Spematy;
	Spematy = new double*[2 * Nf + 1];
	for (int i = 0; i < 2 * Nf + 1; i++)
	{
		Spematy[i] = new double[2 * Nf + 1];
	}
	for (int i = 0; i < 2 * Nf + 1; i++)
		for (int j = 0; j < 2 * Nf + 1; j++)
		{
			Spematy[i][j] = ka_dbside[j];
		}*/
	/*double dx ,dy;
	dx = 1.0 / m_Rr;
	dy = dx;*/

	double_complex *Phase_Lin;
	Phase_Lin=new double_complex [Samp_point*POINT];
	for(int k=0;k<Samp_point*POINT;k++)
	{
		Phase_Lin[k].real=0.0;
		Phase_Lin[k].imag=0.0;

	}
	double_complex **Phase;
	Phase = new double_complex * [m_Width];
	for (int i = 0; i < m_Width; i++)
	{
		Phase[i] = new double_complex[m_Len];
	}
	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			Phase[i][j].real = 0.0;
			Phase[i][j].imag = 0.0;
		}

	double **P;
	P = new double * [m_Width];
	for (int i = 0; i < m_Width; i++)
	{
		P[i] = new double[m_Len];
	}
	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			P[i][j] = 0.0;
		}
/*************	Simulation by CPU *******************/
    //long double sum_real=0.0;
	//long double sum_imag=0.0;
	//double sum1=0.0;
	//double sum2=0.0;
	//double sum3=0.0;
	//double sum4=0.0;
	//for (int i = 0; i < m_Width; i++) //m_Widthѡ��С��512
	//	for (int j = 0; j <m_Len; j++)//m_Lenѡ��С��512
	//	{
	//		sum_real=0.0;
	//        sum_imag=0.0;
	//		for (int m = 0; m < 2*Nf+1 ; m++)
	//			for (int n = 0; n < 2 * Nf+1 ; n++)
	//			{ 
	//				sum1=Rand_Spect[m][n].real*(cos(ka_dbside[m]*((i+1)*dx)+ka_dbside[n]*((j+1)*dy)));
	//				sum2=Rand_Spect[m][n].imag*(sin(ka_dbside[m]*((i+1)*dx)+ka_dbside[n]*((j+1)*dy)));
	//				sum3=Rand_Spect[m][n].real*(sin(ka_dbside[m]*((i+1)*dx)+ka_dbside[n]*((j+1)*dy)));
	//				sum4=Rand_Spect[m][n].imag*(cos(ka_dbside[m]*((i+1)*dx)+ka_dbside[n]*((j+1)*dy)));
	//				sum_real +=sum1-sum2;
	//				sum_imag +=sum3+sum4;
	//			}
	//		P[i][j] = sqrt(pow(sum_real,2)+pow(sum_imag,2));
	//	 }
    //  save_data(P);
/*************	Simulation by CPU *******************/


/*************	Simulation by GPU *******************/
	int j=0;
	cudaError_t cudaStatus;
	for (int i = 0; i < m_Width; i++) //m_Widthѡ��С��512	
	{
	   //QueryPerformanceCounter(&M_Begin);//�õ�ϵͳ��ǰ������ֵ
    //   QueryPerformanceFrequency(&Frequence);//�õ�ϵͳʱ��Ƶ��
	   cudaStatus=cuda_Phase(Phase_Lin,Rand_Spect_Lin,ka_dbside,i,m_Width_m);
	   for(int k=0 ;k< Samp_point * POINT; k++)
	   {
            j=k/Samp_point;
			Phase[i][j].imag += Phase_Lin[k].imag;
			Phase[i][j].real += Phase_Lin[k].real;
	   } 
	//QueryPerformanceCounter(&M_End);                    //�õ�ϵͳ��ǰ������ֵ
	//double time_GPU	=((M_End.QuadPart-M_Begin.QuadPart)*1.0)/((Frequence.QuadPart)*1.0);//�õ���λ������֡�ʡ�֡�ʵ��Ǽ��㹫ʽΪ��֡��=ϵͳƵ��/��������ֵ����
	}
	delete[]Phase_Lin;//ɾ��Phase_Lin

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			P[i][j] = sqrt(pow(Phase[i][j].imag,2.0)+pow(Phase[i][j].real,2.0));
		}

	for (int i = 0; i < m_Width; i++)  //ɾ���м䲻��ʹ�õı�������
	{
		delete[]Phase[i];
	}
	delete[]Phase;
	
	double min ,max;
	min= P[0][0];
	max= P[0][0];
	for (int i = 0; i < m_Width; i++)
		for (int j=0; j < m_Len; j++)
		{
			if (P[i][j] < min);
			{
			   min = P[i][j];
			}
			if(P[i][j]>max)
			{
				max=P[i][j];
			}
		}

	double kk=pow(6.88*(pow(m_Width_m/m_r0,5.0/3.0)),0.5);
	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			A_P[i][j] = P[i][j];
			//A_P[i][j] =kk*((P[i][j]-min)/(max-min));// Mod_double(kk*((Phase[i][j]-min)/(max-min)),2*PI);
		}
	/*************	Simulation by GPU *******************/


}
    void CBNS_APPDlg::Sequencer(double* f_sequence,double ** f_area,double ka_L,double ka_H,int Nf )
	{
		double * f_fix;
	    f_fix = new double [Nf+3];

			double alpha = pow((ka_H/ka_L),(1.0/(Nf-1)));
			f_sequence[0]=0.0;
			f_fix[0]=0.0;
			f_fix[1]=0.0;
			for(int loop=1;loop<Nf+1;loop++)
			{
				f_sequence[loop]=ka_L*pow(alpha,(loop-1.0));
				f_fix[loop+1]=f_sequence[loop];
		     }
			f_fix[Nf+2]=f_fix[Nf+1]*alpha;
	     
		for(int i=0;i<Nf+1;i++)
			for(int j=0;j<Nf+1;j++)
			{
				f_area[j][i]=(f_fix[i]-f_fix[i+2])*(f_fix[j]-f_fix[j+2])/4;
			}
			f_area[0][0]=4*f_area[0][0];
		for(int i=1;i<Nf+1;i++)
		{
			f_area[0][i]=4*f_area[0][i];
			f_area[i][0]=4*f_area[i][0];
		}



	}
/**************************************************************/
//
//
//
//
//
//
//
//
/***************************************************************/
void CBNS_APPDlg::Norseque2(double *sequencex, int com_x, double *sequencey, int com_y, double **f_area)
{
	double *f_fixx;
	f_fixx = new  double[com_x + 3];
	for (int i = 0; i < com_x + 1; i++)
	{
		f_fixx[i] = sequencex[i];
	}
	f_fixx[com_x + 1] = sequencex[com_x] + 10;
	f_fixx[com_x + 2] = sequencex[com_x] + 50;
	double *f_fixy;
	f_fixy = new  double[com_y + 3];
	for (int i = 0; i < com_y + 1; i++)
	{
		f_fixy[i] = sequencey[i];
	}
	f_fixy[com_y + 1] = sequencey[com_y] + 10;
	f_fixy[com_y + 2] = sequencey[com_y] + 50;
	for (int loop_x = 0; loop_x < com_x + 1; loop_x++)
		for (int loop_y = 0; loop_y < com_y + 1; loop_y++)
		{
			if (loop_x == 0 || loop_y == 0 || loop_x == com_x || loop_y == com_y)
			{
				f_area[loop_x][loop_y] = 0.0;
			}
			else
			{
				f_area[loop_x][loop_y] = (f_fixx[loop_x - 1] - f_fixx[loop_x + 1])*(f_fixy[loop_y - 1] - f_fixy[loop_y + 1]) / 4;
			}
		}

	//-----ʲô���壿--//
	/*for (int i = 0; i < com_y;i++)
	{
	f_area[0][i] = 4 * f_area[0][i];
	}
	for (int i = 1; i < com_x; i++)
	{
	f_area[i][0] = 4 * f_area[i][0];
	}*/

}
/*************************************************************/
//
//������:double CNUFFTDlg::Min(double *ka_dbside, int point)
//
//�������:double *ka_dbside, int point (һά����,���鳤��)
//
//�������: double����,һά�������Сֵ
//
//��������:�ҳ�һά�������Сֵ
//
/****************************************************************/
double CBNS_APPDlg::Min(double *ka_dbside, int point)
{
	double min;
	min = ka_dbside[0];
	for (int i = 0; i < point; i++)
	{
		if (ka_dbside[i] < min)
		{
			min = ka_dbside[i];
		}
	}
	return min;
}
/*************************************************************/
//
//������:double CNUFFTDlg::Max(double *ka_dbside, int point)
//
//�������:double *ka_dbside, int point (һά����,���鳤��)
//
//�������: double����,һά��������ֵ
//
//��������:�ҳ�һά��������ֵ
//
/****************************************************************/
double CBNS_APPDlg::Max(double *ka_dbside, int point)
{
	double max;
	max = ka_dbside[0];
	for (int i = 0; i < point; i++)
	{
		if (ka_dbside[i]>max)
		{
			max = ka_dbside[i];
		}
	}
	return max;
}
/*************************************************************/
//
//������:double CNUFFTDlg::Mod_double(double dividend, double divisor)
//
//�������:double dividend, double divisor (������������)
//
//�������: double����,���������Գ���ʣ�µ�ģ
//
//��������:��һ��������һ������ģֵ�������ͱ���������ʹ������
//
/****************************************************************/
double CBNS_APPDlg::Mod_double(double dividend, double divisor)
{
	double sum, Decimals, mod_sum;

	double integer;
	sum = dividend / divisor;
	integer = floor(sum);
	Decimals = sum - integer;
	mod_sum = Decimals*divisor;
	return mod_sum;
}
float CBNS_APPDlg::Mod_float(float dividend, double divisor)
{
	float sum, Decimals, mod_sum;

	float integer;
	sum = dividend / divisor;
	integer = floor(sum);
	Decimals = sum - integer;
	mod_sum = Decimals*divisor;
	return mod_sum;
}
/*************************************************************/
//
//������:void fftshift������
//
//���������double_complex **matrix_old, double_complex **matrix_new, int row, int column
//
//�����������
//
//�������ܣ�ʵ�ֶ�һ����ά����� �죨����ԭ�����һ���֣� ת��
//
/*********************************************************************/
void CBNS_APPDlg::fftshift(double_complex **matrix_old, double_complex **matrix_new, int row, int column)
{
	for (int i = 0; i < row; i++)                 //forѭ��Ϊ����λ�ṹ��������ת��
	{
		for (int j = 0; j<column; j++)
		{
			if ((i <= (row / 2 - 1)) && (j <= (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i + row / 2][j + column / 2];
			if ((i <= (row / 2 - 1)) && (j>(column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i + row / 2][j - column / 2];
			if ((i >(row / 2 - 1)) && (j <= (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i - row / 2][j + column / 2];
			if ((i > (row / 2 - 1)) && (j > (column / 2 - 1)))
				matrix_new[i][j] = matrix_old[i - row / 2][j - column / 2];
		}
	}
}
//*******************************************//
//
//
//��������randn����
//
//�����������
//
//��������������
//
//�������ܣ����������׼��̫�ֲ��������
//
//*******************************************//
double CBNS_APPDlg::randn()
{
	double u1 = double(rand() % 1024) / 1024, u2 = double(rand() % 1024) / 1024, r;
	while (u1 == 0)
	{
		u1 = double(rand() % 1024) / 1024;
	}
	r = sqrt(-2.0*(log(u1) / log(e)))*cos(2 * PI*u2);
	return r;
}
/********************************************************////
//
//
//���ܣ����һ����ϵͳʱ�����������ַ���
//
//
//*******************************************************////
CString CBNS_APPDlg::rands()
{
	CString R_string;
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	R_string = m_time.Format(_T("%Y-%m-%d-%H_%M_%S"));
	return R_string;

}
//************************************************************//
//
//��������Whitenoise(int com_x, int com_y,double_complex **whitenoise)
//
//���������int com_x, int com_y,
//
//�����double_complex **whitenoise
//
//�������ܣ���˹���������ɺ���������һ�������˹��������������
//
//**************************************************************//
void CBNS_APPDlg::Whitenoise(int com_x, int com_y,double_complex **whitenoise)
{
	double contant = 1.0 / sqrt(2.0);
	double_complex **noise1;
	noise1 = new double_complex *[(com_x+1)];
	for (int i = 0; i < com_x+1; i++)
	{
		noise1[i] = new double_complex[(com_y+1)];
	}
	for (int i = 0; i < com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			noise1[i][j].real = contant*randn();
			noise1[i][j].imag = contant*randn();
		}
	double_complex **noise2;
	noise2 = new double_complex *[com_x ];
	for (int i = 0; i < com_x ; i++)
	{
		noise2[i] = new double_complex[com_y ];
	}
	for (int i = 0; i < com_x ; i++)

		for (int j = 0; j < com_y ; j++)
		{
			noise2[i][j].real = contant*randn();
			noise2[i][j].imag = contant*randn();
		}
	//************************************//
	//
	//noise3 ����noise1��ת180�ȵõ���
	//
	//************************************//
	double_complex **noise3;
	noise3 = new double_complex *[com_x + 1];
	for (int i = 0; i < com_x + 1; i++)
	{
		noise3[i] = new double_complex[com_y + 1];
	}
	for (int i = 0; i < com_x + 1; i++)
		for (int j = 0; j < com_y + 1; j++)
		{
			noise3[i][j].real = noise1[com_x - i][com_y - j].real;
			noise3[i][j].imag = noise1[com_x - i][com_y - j].imag;
		}
	//************************************//
	//
	//noise4 ����noise2��ת180�ȵõ���
	//
	//************************************//
	double_complex **noise4;
	noise4 = new double_complex *[com_x];
	for (int i = 0; i < com_x; i++)
	{
		noise4[i] = new double_complex[com_y];
	}
	for (int i = 0; i < com_x; i++)
		for (int j = 0; j < com_y; j++)
		{
			noise4[i][j].real = noise2[com_x - 1 - i][com_y - 1 - j].real;
			noise4[i][j].imag = noise2[com_x - 1 - i][com_y - 1 - j].imag;

		}
	for (int i = 0; i < 2 * com_x + 1; i++)
		for (int j = 0; j < 2 * com_y + 1; j++)
		{
			if (i < com_x &&j < com_y)
			{
				whitenoise[i][j].real = noise2[i][j].real;
				whitenoise[i][j].imag = noise2[i][j].imag;
			}
			else if (i <= com_x &&j >= com_y)
			{
				whitenoise[i][j].real = noise1[i][j - com_y].real;
				whitenoise[i][j].imag = noise1[i][j - com_y].imag;
			}
			else if (i >= com_x &&j <= com_y)
			{
				whitenoise[i][j].real = noise3[i - com_x][j].real;
				whitenoise[i][j].imag = (-1)*noise3[i - com_x][j].imag;
			}
			else if (i > com_x &&j > com_y)
			{
				whitenoise[i][j].real = noise4[i - com_x - 1][j - com_y - 1].real;
				whitenoise[i][j].imag = (-1)*noise4[i - com_x - 1][j - com_y - 1].imag;
			}

		}
	whitenoise[com_x][com_y].real = 0.0;
	whitenoise[com_x][com_y].imag = 0.0;
			for (int i = 0; i < com_x; i++)
			{
				delete []noise1[i];
				delete []noise2[i];
				delete []noise3[i];
				delete []noise4[i];
			}
			delete[]noise1[com_x];
			delete[]noise3[com_x];
			delete[]noise1;
			delete[]noise2;
			delete[]noise3;
			delete[]noise4;
		
}

void CBNS_APPDlg::Create_File()
{
	//*********************************************************//
	//  ����һ�����ļ��У����������λ������  
	FileToSavePath = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // ���ַ��ĳ���;
	char * pstr = new char[strsize]; //����ռ�;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // �ַ����Ѿ���ԭ����CString ת������ const char*   */
	system("md " + FileToSavePath);
	CFile File_1(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //�����ļ���׼���洢����
	File_1.Close();

}
void CBNS_APPDlg::Create_File_1()
{
	//*********************************************************//
	//  ����һ�����ļ��У����������λ������  
	FileToSavePath_1 = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // ���ַ��ĳ���;
	char * pstr = new char[strsize]; //����ռ�;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // �ַ����Ѿ���ԭ����CString ת������ const char*   */
	system("md " + FileToSavePath_1);
	CFile File_1(FileToSavePath_1 + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //�����ļ���׼���洢����
	File_1.Close();

}
void CBNS_APPDlg::Create_File_2()
{
	//*********************************************************//
	//  ����һ�����ļ��У����������λ������  
	FileToSavePath_2 = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // ���ַ��ĳ���;
	char * pstr = new char[strsize]; //����ռ�;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // �ַ����Ѿ���ԭ����CString ת������ const char*   */
	system("md " + FileToSavePath_2);
	CFile File_1(FileToSavePath_2 + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //�����ļ���׼���洢����
	File_1.Close();

}

void CBNS_APPDlg::save_headata()
{

	if (File.Open(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		File.Write((char*)&file_head, sizeof(file_head));    //�����ɵ�����д��Ӳ����
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("��Ҫ�򿪵��ļ�������") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}
/***********************************************************/
//
//
//
//
//
//
//
//
/**************************************************************/
void CBNS_APPDlg::save_data_1(double **A_P)
{

	if (File.Open(FileToSavePath_1 + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		for (int i = 0; i<Samp_point-1; i++)
		 for (int j = 0; j<Samp_point-1; j++)
		  {
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //�����ɵ�����д��Ӳ����
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("��Ҫ�򿪵��ļ�������") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}


void CBNS_APPDlg::save_data_2(double **A_P)
{

	if (File.Open(FileToSavePath_2 + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		for (int i = 0; i<Samp_point-1; i++)
		 for (int j = 0; j<Samp_point-1; j++)
		  {
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //�����ɵ�����д��Ӳ����
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("��Ҫ�򿪵��ļ�������") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}
/***********************************************************/
//
//
//
//
//
//
//
//
/**************************************************************/
void CBNS_APPDlg::save_data(double **A_P)
{

	if (File.Open(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		for (int i = 0; i<m_Len-Mosaic_Pixel; i++)
		 for (int j = 0; j<m_Width; j++)
		  {
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //�����ɵ�����д��Ӳ����
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("��Ҫ�򿪵��ļ�������") ,MB_OK,MB_ICONEXCLAMATION);
		return ;
	}

	

}
///////////////////////////////////////////////////////////
//
//
//
//
//
//
//�������ܣ���һ����λ�����浽Ӳ�̵��У���ʽΪBMP��
//
//
//
///////////////////////////////////////////////////////////////////
void CBNS_APPDlg::Save_Pic_BMP(double *PictureBuff,int page,int Height,int Width)
{
	DWORD File_Size;                        //BMP��ʽ���ļ�ͷ��С
	RGB=new RGBQUAD[256];                   //��ɫ����Ϣ
	CString filename="Picture";             //������Ҫ�����BMPͼƬ
	CString Now_Page;                       //��Ҫ�����ͼƬҳ����Ҳ��ͼƬ����һ���֣�
	CString PictureToSavePath;              //��Ҫ���ͼƬ��·����
	unsigned char Buwei=0;                  //��ɫ��ĵ���λΪ0x00;
	Now_Page.Format(_T("%d"),page);         //��ʽ��ͼƬҳ�룬����ֵ��Now_Page
	File_Size=Height*Width+sizeof(fileheader)+sizeof(infoheader)+256*4;   //��ȡBMP�ļ�ͷ��Сֵ
	for(int i=0;i<=255;i++)                 //����ɫ�帳ֵ
	{
		RGB[i].rgbRed=i;
		RGB[i].rgbGreen=i;
		RGB[i].rgbBlue=i;
	}
	//------����ΪBMP��ʽ���ļ�ͷ������Ϣֵ-----//
	//------������Ϣ�ɲο��� http://wenku.baidu.com/view/4cc859eb0975f46527d3e160.html   -----//
	fileheader.bfType='MB';
	fileheader.bfSize=File_Size;
	fileheader.bfReserved1=0x00;
	fileheader.bfReserved2=0x00;
	fileheader.bfOffBits=sizeof(fileheader)+sizeof(infoheader)+256*4;
	infoheader.biSize=0x28;
	infoheader.biWidth=Width;
	infoheader.biHeight=Height;
	infoheader.biPlanes=0x01;
	infoheader.biBitCount=0x08;
	infoheader.biCompression=0x00;
	infoheader.biSizeImage=0x00;
	infoheader.biXPelsPerMeter=0x00;
	infoheader.biYPelsPerMeter=0x00;
	infoheader.biClrUsed=0x100;
	infoheader.biClrImportant=0x00;
    PictureToSavePath=GetPathToSave();
	CFile file(PictureToSavePath+(_T("\\"))+filename+Now_Page+".BMP", CFile::modeCreate | CFile::modeWrite);    //�����ļ���׼���洢����
	file.SeekToBegin();
	file.Write((char*)&fileheader,sizeof(fileheader));         //дλͼ�ļ�ͷ
	file.Write((char*)&infoheader,sizeof(infoheader));         //дλͼ��Ϣͷ
	for(int i=0;i<=255;i++)                                    //дλͼ��ɫ��
	{

		file.Write((char*)&RGB[i].rgbBlue,sizeof(RGB[i].rgbBlue));
		file.Write((char*)&RGB[i].rgbGreen,sizeof(RGB[i].rgbGreen));
		file.Write((char*)&RGB[i].rgbRed,sizeof(RGB[i].rgbRed));
		file.Write((char*)&Buwei,1);
	}
	double min,max;
	min=PictureBuff[0];
	max=PictureBuff[0];
	for(int i=1;i<512*512;i++)
	{
		if(PictureBuff[i]<min)
		{
			min=PictureBuff[i];
		}
		if(PictureBuff[i]>max)
		{
			max=PictureBuff[i];
		}
	}
	unsigned __int8  ColorBuff1[512*512];
	for(int j=0;j<512*512;j++)
	{
		ColorBuff1[j]=char(2*PI*(PictureBuff[j]/(max-min)));
	}
		  for(int j=0;j<Height*Width;j++)                      //дλͼ����
		    {
				 file.Write((char*)&ColorBuff1[j],sizeof(ColorBuff1[j])); 
                
		    }
		  file.Close();                                        //�ر��ļ�
   MessageBox(_T("ͼƬ�ѱ��棡") ,MB_OK,MB_ICONEXCLAMATION);

}
//////////////////////////////////////////////////////////////
//
//
//
//��������:��������桱��ť����ʼ����Save_Pic_BMP(unsigned char *PictureBuff,int page,int Height,int Width)
//          
//         ���������ͼƬ�ı���
//
//
/////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Save_Pic_BMP(ColorBuff+Page_0*512,Page_0,biHeight,biWidth);

}
////////////////////////////////////////////////////////
//
//
//�������ܣ���һ������·�����̺�+·��+�ļ���+��չ������
//          ���ļ�·�����̺�+·������ȡ����
//
//
//////////////////////////////////////////////////////////
CString CBNS_APPDlg::GetPathToSave()
{
	char Drive[10],Dir[40],Fname[40],Ext[10];    //����char �������� ���ڴ�Ž�������·���õ��ģ��̷���·�����ļ�������չ��
	CString drive;
	CString dir;
	_splitpath(strFilePath,Drive,Dir,Fname,Ext);//�������򿪡���ť��õľ���·����
	drive=Drive;                                //���̷���Ϣ��ֵ��drive,ʵ�� char ����ת CString ����
	dir=Dir;                                    //·����Ϣ
	return drive+dir;                           //�����̷�+·��
}
//*******************************************************//
//
//
//���ܣ���ѡ�˰�ť���˳����򡢸�ʽ������
//
//
//*******************************************************//
void CBNS_APPDlg::OnBnClickedButtonOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	COut ProgramToOut;
	INT_PTR nRes;
	nRes=ProgramToOut.DoModal();
	switch (nRes)
	{
	case (IDOK):
		{
		  if(key==true)
		   {
			delete []ColorBuff;
			if(m_Len<ImgHeight)
			{
				delete []ColorBuff_512;          //ɾ������
			}
		   }
		ToOnClose();   //ɾ����Ӳ������ʱ���ɵ�����
		OnCancel();    //�˳�����
		return;
		}
	case (IDCANCEL):       //��ʽ������
		{
		 if(key==true)
		  { 
			delete []ColorBuff; //ɾ�����ص��ڴ��е���λ������
			if(m_Len<ImgHeight)
			{ 
				delete []ColorBuff_512;         //ɾ������
			}
		  }
		 key=false;
		 m_Begin.EnableWindow(true);
		 m_Prepare_value.EnableWindow(true);
		 m_UP.EnableWindow(false);
		 m_DOWN.EnableWindow(false);
		 m_Add.EnableWindow(false);
		 m_StartStopButton.EnableWindow(false);//ʹ���ϵ硱����START������UP������DOWN���������桱��ť���ڲ�����״̬��
		 m_SlmPwrButton.EnableWindow(false);
		 m_Save.EnableWindow(false);
		 m_EDIT_BN=0; 
	     m_EDIT_EN=0;
         m_speed=0;                //����������ϵĶ�ʱ�Ȳ������㡣
	     m_frame=0.0;
	     m_Now=0;
		 m_L0=0;
		 m_i0=0;
		 m_r0=0;
		 m_Width_m=0;
		 m_Len_m=0;
		 m_T=0;
		 UpdateData(false);
		 return;        //��ʽ���������֮�󷵻�������
		}
	default:
		{
			return; //����������
		}
	}
}


void CBNS_APPDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//BNS CODE
	//Usually the following parameters are read in from the registry,
	//for simpicity they are hard-coded. Use the ReadRegistry() function in Blink
	//to read these values from the registry.
	CString BoardName = _T("PCIe512");
	LC_Type = 1; //0 = Ferroelectric LC, 1 = Nematic LC
	FrameRate =  5; //Frame rate is measured in Hz and can range from 1 - 1000 Hz
	TrueFrames = 6;

	CBNSPCIeFactory boardFactory;
	char buffer[_MAX_PATH];
	char buffer1[_MAX_PATH];
	bool VerifyHardware = true;
	bool Initialize = true;
	bool TestEnable = false;
	bool RAMWriteEnable = false;
	
	//open communication with our first PCIe board
	Board_Entry *pBoard = new Board_Entry;
	pBoard->theBoard = boardFactory.BuildBoard(BoardName, buffer, buffer1, Initialize, TestEnable, RAMWriteEnable, &VerifyHardware);
	
	//build paths to the calibrations for this SLM
	CString SLMSerialNum = _T("slm616");
	pBoard->LUTFileName.Format(_T("%s.LUT"), SLMSerialNum);
	pBoard->PhaseCompensationFileName.Format(_T("%s.bmp"), SLMSerialNum);
	pBoard->SystemPhaseCompensationFileName.Format(_T("Blank.bmp"));

	//allocate arrays for this SLM
	ImgWidth = pBoard->theBoard->BoardSpec()->FrameWidth;
	ImgHeight = pBoard->theBoard->BoardSpec()->FrameHeight;
	pBoard->LUT = new unsigned char[256];
	pBoard->PhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];
	pBoard->SystemPhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];

	//add this information to the board list
	BoardList.AddTail(pBoard);

	//read the LUT file and write it to the hardware. Images are processed through
	//the LUT in the hardware.
	ReadLUTFile(pBoard->LUT, pBoard->LUTFileName);
	pBoard->theBoard->WriteLUT(pBoard->LUT);

	//set true frames for this SLM. If we are working with an FLC SLM then 
	//True Frames must be calculated based on hardware parameters and on the Frame rate
	if(LC_Type == 0) //FLC
	{
		//for an FLC SLM Frame Rate and TrueFrames are related.
		float TimeIncrement = (pBoard->theBoard->BoardSpec()->TimeIncrement)*1e-7;
		float fTrueFrames = 1.0/(FrameRate*2.0*TimeIncrement);
		TrueFrames = (int)fTrueFrames;
	}


	pBoard->theBoard->SetTrueFrames(TrueFrames);

	//set the LC Type
	pBoard->theBoard->SetLCType(LC_Type);

	//check how many PCIe boards are present so that we can loop through the 
	//remaining boards, and open communication with them.
	NumBoards = pBoard->theBoard->BoardSpec()->NumDevices;

	//open communication and repeat the above process with the rest of our PCIe boards
	Initialize = false;
	for(int board = 2; board <= NumBoards; board++)
	{
		Board_Entry *pBoard = new Board_Entry;
		pBoard->theBoard = boardFactory.BuildBoard(BoardName, buffer, buffer1, Initialize, TestEnable, RAMWriteEnable, &VerifyHardware);
		
		//build paths to the calibrations for this SLM
		CString SLMSerialNum = _T("slm616");
		pBoard->LUTFileName.Format(_T("%s.LUT"), SLMSerialNum);
		pBoard->PhaseCompensationFileName.Format(_T("%s.bmp"), SLMSerialNum);
		pBoard->SystemPhaseCompensationFileName.Format(_T("Blank.bmp"));

		//allocate arrays for this SLM
		pBoard->LUT = new unsigned char[256];
		pBoard->PhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];
		pBoard->SystemPhaseCompensationData = new unsigned char[ImgHeight*ImgWidth];		
		BoardList.AddTail(pBoard);

		//read the LUT file and write it to the hardware. Images are processed through
		//the LUT in the hardware.
		ReadLUTFile(pBoard->LUT, pBoard->LUTFileName);
		pBoard->theBoard->WriteLUT(pBoard->LUT);

		//set True Frames for this SLM
		pBoard->theBoard->SetTrueFrames(TrueFrames);

		//set the LC Type
		pBoard->theBoard->SetLCType(LC_Type);
	}
	for(int board = 0; board < NumBoards; board++)
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		bool bPower = (bool)pBoard->theBoard->GetPower();
		if(bPower)
		pBoard->theBoard->SetPower(!(bPower));
	}
	m_SlmPwrButton.SetWindowText(_T("ON POWER"));          //��ʼ���ϵ�ؼ�Ϊ��"ON POWER",��ʾ�ȴ��ϵ�״̬��
	m_StartStopButton.SetWindowText(_T("START"));         //��ʼ����ʼ�ؼ�������Ϊ��START��,��ʾ�ȴ�������λ�����ݡ�
	if(LC_Type == 1)
		m_CompensatePhaseCheckbox.ShowWindow(false);      //���Һ��Ϊ������Һ������ʹ�ò�����
	else
		m_CompensatePhaseCheckbox.ShowWindow(true);       //����ʹ�ò�����
	m_SlmPwrButton.EnableWindow(true);
	m_Load.EnableWindow(false);

}


void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (Down_Up)
	{
	case 1:
		UpdateData(true);
	Page_0=m_Now;
	Page_0+=Pixel;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //���δ���г�ֵ�趨���򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-1��
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0>m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0>m_EDIT_BN)
	       {

		      Page_0=m_EDIT_EN;
	       }
	}
	
	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	 m_Now=Page_0;
	 UpdateData(false);
	 m_Save.EnableWindow(true);
	 
		break;
	case 0:
		UpdateData(true);
	Page_0=m_Now;
	Page_0-=Pixel;;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //���δ���г�ֵ�趨���򽫳�ֵ����Ϊ0����ֵ����Ϊ��Page-Pixel��
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	if(m_EDIT_EN>m_EDIT_BN)
	{
		if(Page_0<m_EDIT_BN)
	       {
		      Page_0=m_EDIT_EN;
	       }
	}
	if(m_EDIT_EN<m_EDIT_BN)
	{
		if(Page_0<m_EDIT_EN)
	       {
		      Page_0=m_EDIT_BN;
	       }
	}

	 Display_Picture(ColorBuff+Page_0*512);
	 //LoadSequence(ColorBuff[Page_0]);
	
	 m_Now=Page_0;
	 UpdateData(false);
		break;
	default:   
        break;
	}

}