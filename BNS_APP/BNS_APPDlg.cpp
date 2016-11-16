// BNS_APPDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBNS_APPDlg 对话框




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


// CBNS_APPDlg 消息处理程序

BOOL CBNS_APPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CWzdSplash wndSplash;                     
	wndSplash.Create(IDB_BITMAP1);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();
	wndSplash.SetTimer(0,40000,NULL);
	Sleep(2000);
	srand((unsigned)time(NULL));                //时间数种子
	m_hicn1=AfxGetApp()->LoadIcon(IDI_ICON1);   
	m_Add.SetIcon(m_hicn1);
	m_hicn2=AfxGetApp()->LoadIcon(IDI_ICON2);
	m_DOWN.SetIcon(m_hicn2);
	Page_0=0;
	key=false;
	Down_Up=1;
	Pixel=1;
	Mosaic_Pixel=Mosaic;
 
	INFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256*sizeof(RGBQUAD));    //BMP文件信息头数据
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
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBNS_APPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBNS_APPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////
//
//函数名：OnBnClickedButtonOpen()
//
//函数参数：无
//
//函数功能：打开一副待显示的文件，并获得一些信息，如文件名、文件单位数。
//
//函数返回值：无
//
////////////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDC *pDC;             //定义一个句柄指针
	//pDC=m_Picture.GetDC();//得到Picture control 的句柄 
	biWidth=POINT;        //得到相位屏的大小信息
	biHeight=POINT;
    TCHAR szFilter[] = _T("所有文件(*.*)|*.*|相位屏文件（*.4wf）|*.4wf||");   	 // 设置过滤器
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, NULL, NULL,0, szFilter, this);   //创建一个CFileDiloge对象  
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   //如果打开了文件
	{
	   // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里 
		strFilePath = fileDlg.GetPathName(); //得到文件路径名
		SetDlgItemText(IDC_EDIT_Path, strFilePath); //将文件路径名“打印”出来
	}

	//----以读写方式打开需要加载的文件（需要加载的文件是以二进制形式存储的），----//

	//----如果顺利打开。则，将数据加载到内存中。

	if (file.Open(strFilePath,  CFile::modeRead))
	{
			file.SeekToBegin();
			Page=(file.GetLength()-sizeof(file_head))/(8*biWidth)-511;     //获得相位屏帧数
			CS_Page.Format(_T("file long %d "),Page);       //打印相位屏帧数信息
			SetDlgItemText(IDC_EDIT_Page,CS_Page);  

            //----      给动态数组分配内存。实际上是一个三维的组数--------//

            //----  大小为：Page*biWidth*biHeigth。这样做是有道理的-------//

            //----  一、在定义数组之前，我们并不知道要定义多大的数组------//

            //----- 采用动态数组可以节省空间，并保证程序的安全。----------//

		    // ---- 二、在使用结束之后，可以尽快的释放内存空间。----------//

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
			if(m_Width<POINT)                  //申请一个512*512的数组，用于当生成的相位屏小于512时，这将其转化为512*512
			{
				ColorBuff_512=new unsigned __int8[POINT*POINT];
			    for(int i=0;i<POINT*POINT;i++)
			    {
				ColorBuff_512[i]=0;
			    }

			}
			key=true;//将一个bool类型变量设置为true 通知系统已经为动态数组分配内存
			MessageBox(_T("图片装载完成！"),MB_OK,MB_ICONASTERISK);
			m_Begin.EnableWindow(false);//将“开始”按钮设置为不可用
	        m_Prepare_value.EnableWindow(false);
	        m_SlmPwrButton.EnableWindow(false);
			m_UP.EnableWindow(true);
			m_DOWN.EnableWindow(true);
			m_Add.EnableWindow(true);
			m_out.EnableWindow(true);
			m_Load.EnableWindow(true);


			//当文件加载完毕之后，上电按钮就可以正常工作。
	}

}
//////////////////////////////////////////////////////////////////////
//
//函数名：OnBnClickedStartStopButton()
//
//参数：无
//
//返回值：无
//
//函数功能：开始/停止加载图片按钮
//
//
////////////////////////////////////////////////////////////////////

void CBNS_APPDlg::OnBnClickedStartStopButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString SpSt;
	m_StartStopButton.GetWindowText(SpSt);
	//设置一个CString变量，来获得开始/停止按钮的状态信息
	UpdateData(Down);//将面板上设置的参数传递给程序变量
	Page_0=m_Now;    //Page_0这个变量很重要，它是将要显示相位屏的标号。例如Page_0==0；则将要显示的相位屏就是第一幅相位屏。
	
    //-----当确定按钮为“START”（开始）时，开始加载相位屏数据。--//
	if (0==SpSt.Compare(_T("START")))  
	{
		if(m_speed==0&&m_frame==0)
		{
			MessageBox(_T("请选择定时器时间") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
		Pixel=floor((1/m_frame)*(POINT/m_Width_m)*m_speed);  //根据风速和帧率换算出来的相位屏间隔数
	    m_SlmPwrButton.EnableWindow(false);
		m_Add.EnableWindow(false);
		m_UP.EnableWindow(false);
		m_DOWN.EnableWindow(false);

		//-------相位屏显示信息，本程序是不对初值进行强制要求用户设定的。---//

		//---但，数据并不能超过“0--Page”这个范围，所以程序对此作了处理----//

		if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
	      {
            m_EDIT_BN=0;
			m_EDIT_EN=Page-1;
			UpdateData(false);
		    Page_0=0;
		    Page_end=Page-1;
	      }
	   /*else if(m_EDIT_EN>=m_EDIT_BN)
	       {
			   MessageBox(_T("注意：结束号要大于开始号！！！") ,MB_OK,MB_ICONEXCLAMATION);
			   return;
		   }*/
	   else if(m_EDIT_BN>=Page)//如果初值或终值超出（Page-），则将初值设置为0，终值设置为（Page-1）
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
			QueryPerformanceCounter(&M_Begin);//得到系统当前计数器值
			if(!QueryPerformanceFrequency(&Frequence))//得到系统时钟频率
			{
				MessageBox(_T("对不起，您的电脑不支持高精度计数器！"),MB_OK,MB_ICONEXCLAMATION);
				return;
			}

			TimeToL.QuadPart= Frequence.QuadPart*(1000000/m_frame-2600)/1000000;//通过频率换算微妙数到对应的数量（与CPU有关），1秒=1000000微妙；
			My_Delay(TimeToL);                                  //延时 单位：微秒
			LoadHardBoard();                                    //加载相位屏到硬件
			QueryPerformanceCounter(&M_End);                    //得到系统当前计数器值
			m_now_frame=int ((Frequence.QuadPart)*1.0/((M_End.QuadPart-M_Begin.QuadPart)*1.0));//得到相位屏加载帧率。帧率的是计算公式为：帧率=系统频率/（计数差值）；
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
//功能：电源开关按钮。控制硬件的上电/掉电功能。
//
//
/////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedSlmPwrButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	for(int board = 0; board < NumBoards; board++)    //监测硬件个数，并逐一进行上电/掉电操作。
	{
		//get a handle to the board
		POSITION pos = BoardList.FindIndex(board);
		Board_Entry* pBoard = BoardList.GetAt(pos);

		bool bPowerOn = (bool)!pBoard->theBoard->GetPower();//获得硬件电源情况
		pBoard->theBoard->SetPower(bPowerOn);               //上电/掉电

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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(Down);
	if(m_frame==0)
		{
			MessageBox(_T("请选择帧率") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
	if(m_speed==0)
		{
			MessageBox(_T("请选择风速") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }
	if(m_Width_m==0)
		{
			MessageBox(_T("请选择相位屏宽度") ,MB_OK,MB_ICONEXCLAMATION);//如果没有设定定时器时间，则提醒，并返回。
	        return;
	    }

	Pixel=(1/m_frame)*(POINT/m_Width_m)*m_speed;
	CString Stop_Up;
	m_UP.GetWindowText(Stop_Up);
	//设置一个CString变量，来获得开始/停止按钮的状态信息
	if (0==Stop_Up.Compare(_T("Go")))  
	{
		SetTimer(1,floor(1000.0/m_frame),NULL); //启动ID为1的定时器，定时器单位为 ms;
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
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	//QueryPerformanceFrequency(&Frequence);//得到系统时钟频率
	//QueryPerformanceCounter(&M_Begin);//得到系统当前计数器值
	//QueryPerformanceCounter(&M_End);
	//m_frame=((M_End.QuadPart-M_Begin.QuadPart)*1.0)/(Frequence.QuadPart*1.0);//得到相位屏加载帧率。帧率的是计算公式为：帧率=系统频率/（计数差值）；
	// 
	Down_Up=1;
	Page_0=m_Now;
	Page_0++;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	Down_Up=0;
	Page_0=m_Now;
	Page_0--;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

}
///////////////////////////////////////////////////////////////////
//
//函数名：ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512)
//
//函数参数：unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512 
//         
//
//函数功能：将一幅小于POINT（#define POINT 512）的相位屏转化为（说成粘贴可能更为恰当点）POINT的相位屏。
//
//
//函数返回值：无
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
//			 读取.BMP格式的图片信息
//  Modifications:
//
/////////////////////////////////////////////////////////////////////////////////////
bool CBNS_APPDlg::ReadAndScaleBitmap(unsigned char *Image, CString fileName)      //得到图片的数据值
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
		bytespixel = dib.m_lpBMIH->biBitCount;                  //色深值
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
//           将图片信息进行拉伸或者压缩
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
//           读取查阅表文件
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
//函数名：My_Delay(LARGE_INTEGER Interval)
//
//函数参数：LARGE_INTEGER Interval
//
//函数功能：实现微秒级别的定时
//
//函数返回值：无
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
//函数名：
//
//函数参数：
//
//函数功能：将相位屏数据加载到硬件上的步骤打包起来，实现程序的明了性
//
//函数返回值：无
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
//函数名：OnTimer(UINT_PTR nIDEvent)
//
//函数参数：消息
//
//函数功能：实现毫秒级别的定时，以消息形式触发定时器函数，执行相应程序
//
//函数返回值：无
//
//
/////////////////////////////////////////////////
//void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	UpdateData(TRUE);
//	if(m_EDIT_BN==m_EDIT_EN)
//	{
//		Display_Picture(ColorBuff[Page_0]);
//		LoadSequence(ColorBuff[Page_0]);
//		KillTimer(1);
//	}
//	if(m_EDIT_BN>m_EDIT_EN)//逆序显示
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
//函数名：Display_Picture(unsigned __int8 *ColorBuff1)
//
//函数参数：unsigned __int8 *ColorBuff1
//
//函数返回值：无
//
//
//函数功能：实现读取图像数据的显示
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
	// TODO: 在此添加控件通知处理程序代码
	CString SPV;
	m_Prepare_value.GetWindowText(SPV);
	if(0==SPV.Compare(_T("预设值")))
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
	    m_Prepare_value.SetWindowText(_T("确定"));
	}
	if(0==SPV.Compare(_T("确定")))
	{
		UpdateData(true);
		m_Prepare_value.SetWindowText(_T("预设值"));
	}


}

/***************************************************/
//
//函数名：integral(double(CNUFFTDlg:: *fun)(double), double a, double b)
//
//输入参数：CNUFFTDlg:: *fun)(double), double a, double b （函数入口和积分区间）
//
//输出： 积分结果（double类型）
//
//函数说明：积分函数，实现联系函数在一个区间（明显区间两端的点对积分结果无影响）上的积分
//
//
/******************************************************/
double CBNS_APPDlg::integral(double(CBNS_APPDlg::*fun)(double), double a, double b)      //求fun在a，b区间定积分
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
//函数名：psdevalfunKolspf(double x)
//
//输入参数：double x （函数自变量）
//
//输出：double类型的函数因变量
//
//函数功能：函数实现
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
	// TODO: 在此添加控件通知处理程序代码
	////---------------------注释说明：---------------------/////
	//    
	//              本程序注释位子右侧、上侧                /////
	//
	//         右侧注释以“//”开始，字体颜色为蓝色         /////
	//
	//                                 “////////////////////// 
	//     上侧注释以“//--..--//”或则  //
    //                                   :  注释内容...
	//
	//                                   //////////////////////
	//
	//
	UpdateData(Down);
	if(m_L0==0||m_i0==0||m_r0==0||m_Len_m==0||m_Width_m==0||m_speed==0||m_frame==0)//如果没有进行参数设置，这返回该程序，直到参数设置完成
	{
		MessageBox(_T("请初始化参数") ,MB_OK,MB_ICONEXCLAMATION);
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
	m_Len=int(m_Len_m*m_Rr);        //将相位屏的长物理尺度（单位 米）变换到像素尺度（单位 pixel）
	m_Width=int(m_Width_m*m_Rr);    //将相位屏的宽物理尺度（单位 米）变换到像素尺度（单位 pixel）
	double Efc_S=floor(m_Len/((1/m_frame)*(POINT/m_Width_m)*m_speed));  //根据风速和帧率计算得到 一副长相位屏有效的屏数
	T_Len= int(ceil(m_T*60/((1/m_frame)*Efc_S)));                       //生成需要长的相位屏而需要进行拼接的原始相位屏个数
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

	m_Progress.StepIt();//进度条+1

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
	double **Spectrum1;//将Spectrum_temp1[][]进行一个拼接 【* *    转化为【A~  A'
	                   //                                   * A】          A'~ A】

	Spectrum1 = new double*[2 *  Nf + 1];
	for (int i = 0; i < 2 *  Nf + 1; i++)
	{
		Spectrum1[i] = new double[2 *  Nf + 1];
	}
	for (int i = 0; i<2 *  Nf + 1; i++)
		for (int j = 0; j<2 *  Nf + 1; j++)
		{
			Spectrum1[i][j] = 0.0;//初始化为0.0
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
	for (int i = 0; i <  Nf + 1; i++)  //删除中间不再使用的变量数组
	{
		delete[]Spectrum_temp1[i];
	}
	delete[]Spectrum_temp1;


	m_Progress.StepIt();//进度条+1

	A_P = new double*[m_Width];    //为A_P申请动态数组，A_P是用来存放生成的相位屏数据的指针
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
		C_end[k]=pow(cos(PI*k/(2.0*Mosaic_Pixel)),2.0);//相位屏末尾拼接系数函数
	}
	double *C_Bg;
	C_Bg=new double[Mosaic_Pixel];
	for(int k=0;k<Mosaic_Pixel;k++)
	{
		C_Bg[k]=pow(sin(PI*k/(2.0*Mosaic_Pixel)),2.0);//相位屏开头拼接系数函数
	}

	Create_File();
	//Sleep(2000);
	//Create_File_1();
	//Sleep(2000);
	//Create_File_2();
	save_headata();

	/**************************************/
	//
	//下面的for循环实现了相位屏的生成和拼接
	//
	/*************************************/
	Mosaic_Pixel=0;
	for(int s=0;s<3;s++)
	{
		Summation(Spectrum1,ka_dbside, Nf);

	    save_data(A_P);	
		m_Progress.StepIt();//进度条+1
	}
	//Summation(Spectrum1,ka_dbside, Nf);
	//for (int i = m_Len-Mosaic_Pixel; i<m_Len; i++)
	//   for (int j = 0; j<POINT; j++)
	//	 {
	//		End_AP[j][i-(m_Len-Mosaic_Pixel)]=A_P[j][i];
	//	 }
	//save_data(A_P);	
 //   m_Progress.StepIt();//进度条+1
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
	//m_Progress.StepIt();//进度条+1
 //   }

	//Summation(Spectrum1,ka_dbside, Nf);
	//for(int i=0;i<POINT;i++)
	// for(int j=0;j<Mosaic_Pixel;j++)
	//	{
	//		A_P[i][j]=A_P[i][j]*C_Bg[j]+End_AP[i][j]*C_end[j];
	//    }
	//Mosaic_Pixel=0;
	//save_data(A_P);
	MessageBox(_T("数据生成完毕,已保存...") ,MB_OK,MB_ICONEXCLAMATION);
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

	Whitenoise(Nf, Nf, whiteno); //调用高斯白噪声生成函数
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
	//for (int i = 0; i < 2 * Nf + 1; i++)  //删除中间不再使用的变量数组
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
    

	for (int i = 0; i < 2 * Nf + 1; i++)  //删除中间不再使用的变量数组
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
	//for (int i = 0; i < m_Width; i++) //m_Width选择小于512
	//	for (int j = 0; j <m_Len; j++)//m_Len选择小于512
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
	for (int i = 0; i < m_Width; i++) //m_Width选择小于512	
	{
	   //QueryPerformanceCounter(&M_Begin);//得到系统当前计数器值
    //   QueryPerformanceFrequency(&Frequence);//得到系统时钟频率
	   cudaStatus=cuda_Phase(Phase_Lin,Rand_Spect_Lin,ka_dbside,i,m_Width_m);
	   for(int k=0 ;k< Samp_point * POINT; k++)
	   {
            j=k/Samp_point;
			Phase[i][j].imag += Phase_Lin[k].imag;
			Phase[i][j].real += Phase_Lin[k].real;
	   } 
	//QueryPerformanceCounter(&M_End);                    //得到系统当前计数器值
	//double time_GPU	=((M_End.QuadPart-M_Begin.QuadPart)*1.0)/((Frequence.QuadPart)*1.0);//得到相位屏加载帧率。帧率的是计算公式为：帧率=系统频率/（计数差值）；
	}
	delete[]Phase_Lin;//删除Phase_Lin

	for (int i = 0; i < m_Width; i++)
		for (int j = 0; j < m_Len; j++)
		{
			P[i][j] = sqrt(pow(Phase[i][j].imag,2.0)+pow(Phase[i][j].real,2.0));
		}

	for (int i = 0; i < m_Width; i++)  //删除中间不再使用的变量数组
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

	//-----什么意义？--//
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
//函数名:double CNUFFTDlg::Min(double *ka_dbside, int point)
//
//输入参数:double *ka_dbside, int point (一维数组,数组长度)
//
//输出参数: double类型,一维数组的最小值
//
//函数功能:找出一维数组的最小值
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
//函数名:double CNUFFTDlg::Max(double *ka_dbside, int point)
//
//输入参数:double *ka_dbside, int point (一维数组,数组长度)
//
//输出参数: double类型,一维数组的最大值
//
//函数功能:找出一维数组的最大值
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
//函数名:double CNUFFTDlg::Mod_double(double dividend, double divisor)
//
//输入参数:double dividend, double divisor (被除数，除数)
//
//输出参数: double类型,被除数除以除数剩下的模
//
//函数功能:求一个数对另一个数的模值（除数和被除数可以使负数）
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
//函数名:void fftshift（）；
//
//输入参数：double_complex **matrix_old, double_complex **matrix_new, int row, int column
//
//输出参数：无
//
//函数功能：实现对一个二维矩阵的 快（快是原矩阵的一部分） 转换
//
/*********************************************************************/
void CBNS_APPDlg::fftshift(double_complex **matrix_old, double_complex **matrix_new, int row, int column)
{
	for (int i = 0; i < row; i++)                 //for循环为将相位结构函数进行转化
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
//函数名：randn（）
//
//输入参数：无
//
//输出参数：随机数
//
//函数功能：生成满足标准正太分布的随机数
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
//功能：获得一个由系统时间来决定的字符串
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
//函数名：Whitenoise(int com_x, int com_y,double_complex **whitenoise)
//
//输入参数：int com_x, int com_y,
//
//输出：double_complex **whitenoise
//
//函数功能：高斯白噪声生成函数，生成一个满足高斯函数的噪声矩阵
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
	//noise3 是由noise1旋转180度得到的
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
	//noise4 是由noise2旋转180度得到的
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
	//  创建一个新文件夹，用来存放相位屏数据  
	FileToSavePath = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // 宽字符的长度;
	char * pstr = new char[strsize]; //分配空间;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // 字符串已经由原来的CString 转换成了 const char*   */
	system("md " + FileToSavePath);
	CFile File_1(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //创建文件，准备存储数据
	File_1.Close();

}
void CBNS_APPDlg::Create_File_1()
{
	//*********************************************************//
	//  创建一个新文件夹，用来存放相位屏数据  
	FileToSavePath_1 = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // 宽字符的长度;
	char * pstr = new char[strsize]; //分配空间;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // 字符串已经由原来的CString 转换成了 const char*   */
	system("md " + FileToSavePath_1);
	CFile File_1(FileToSavePath_1 + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //创建文件，准备存储数据
	File_1.Close();

}
void CBNS_APPDlg::Create_File_2()
{
	//*********************************************************//
	//  创建一个新文件夹，用来存放相位屏数据  
	FileToSavePath_2 = _T("d:\\DPSfile\\DPS") + rands();

	/*const size_t strsize = (FileToSavePath.GetLength() + 1) * 2; // 宽字符的长度;
	char * pstr = new char[strsize]; //分配空间;
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, FileToSavePath, _TRUNCATE);
	int n = atoi((const char*)pstr); // 字符串已经由原来的CString 转换成了 const char*   */
	system("md " + FileToSavePath_2);
	CFile File_1(FileToSavePath_2 + _T("\\Dynamic_phase_screen.4wf"), CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone);    //创建文件，准备存储数据
	File_1.Close();

}

void CBNS_APPDlg::save_headata()
{

	if (File.Open(FileToSavePath + _T("\\Dynamic_phase_screen.4wf"),  CFile::modeReadWrite))
	{
		File.SeekToEnd();
		File.Write((char*)&file_head, sizeof(file_head));    //将生成的数据写到硬盘中
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
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
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //将生成的数据写到硬盘中
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
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
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //将生成的数据写到硬盘中
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
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
		   File.Write((char*)&A_P[j][i], sizeof(A_P[i][j]));    //将生成的数据写到硬盘中
		  }
	    File.Close();
	}
	else
	{
		
		MessageBox(_T("您要打开的文件不存在") ,MB_OK,MB_ICONEXCLAMATION);
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
//函数功能：将一幅相位屏保存到硬盘当中（格式为BMP）
//
//
//
///////////////////////////////////////////////////////////////////
void CBNS_APPDlg::Save_Pic_BMP(double *PictureBuff,int page,int Height,int Width)
{
	DWORD File_Size;                        //BMP格式的文件头大小
	RGB=new RGBQUAD[256];                   //调色板信息
	CString filename="Picture";             //命名将要保存的BMP图片
	CString Now_Page;                       //将要保存的图片页数（也是图片名的一部分）
	CString PictureToSavePath;              //将要半寸图片的路径。
	unsigned char Buwei=0;                  //调色板的第四位为0x00;
	Now_Page.Format(_T("%d"),page);         //格式化图片页码，并赋值给Now_Page
	File_Size=Height*Width+sizeof(fileheader)+sizeof(infoheader)+256*4;   //获取BMP文件头大小值
	for(int i=0;i<=255;i++)                 //给调色板赋值
	{
		RGB[i].rgbRed=i;
		RGB[i].rgbGreen=i;
		RGB[i].rgbBlue=i;
	}
	//------以下为BMP格式的文件头具体信息值-----//
	//------具体信息可参考： http://wenku.baidu.com/view/4cc859eb0975f46527d3e160.html   -----//
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
	CFile file(PictureToSavePath+(_T("\\"))+filename+Now_Page+".BMP", CFile::modeCreate | CFile::modeWrite);    //创建文件，准备存储数据
	file.SeekToBegin();
	file.Write((char*)&fileheader,sizeof(fileheader));         //写位图文件头
	file.Write((char*)&infoheader,sizeof(infoheader));         //写位图信息头
	for(int i=0;i<=255;i++)                                    //写位图调色板
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
		  for(int j=0;j<Height*Width;j++)                      //写位图数据
		    {
				 file.Write((char*)&ColorBuff1[j],sizeof(ColorBuff1[j])); 
                
		    }
		  file.Close();                                        //关闭文件
   MessageBox(_T("图片已保存！") ,MB_OK,MB_ICONEXCLAMATION);

}
//////////////////////////////////////////////////////////////
//
//
//
//函数功能:点击“保存”按钮，开始调用Save_Pic_BMP(unsigned char *PictureBuff,int page,int Height,int Width)
//          
//         函数，完成图片的保存
//
//
/////////////////////////////////////////////////////////////
void CBNS_APPDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	Save_Pic_BMP(ColorBuff+Page_0*512,Page_0,biHeight,biWidth);

}
////////////////////////////////////////////////////////
//
//
//函数功能：将一个绝对路径（盘号+路径+文件名+扩展名）中
//          的文件路径（盘号+路径）提取出来
//
//
//////////////////////////////////////////////////////////
CString CBNS_APPDlg::GetPathToSave()
{
	char Drive[10],Dir[40],Fname[40],Ext[10];    //定义char 类型数组 用于存放解析绝对路径得到的：盘符、路径、文件名、扩展名
	CString drive;
	CString dir;
	_splitpath(strFilePath,Drive,Dir,Fname,Ext);//解析“打开”按钮获得的绝对路径。
	drive=Drive;                                //将盘符信息赋值给drive,实现 char 类型转 CString 类型
	dir=Dir;                                    //路径信息
	return drive+dir;                           //返回盘符+路径
}
//*******************************************************//
//
//
//功能：点选此按钮可退出程序、格式化程序。
//
//
//*******************************************************//
void CBNS_APPDlg::OnBnClickedButtonOut()
{
	// TODO: 在此添加控件通知处理程序代码
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
				delete []ColorBuff_512;          //删除数组
			}
		   }
		ToOnClose();   //删除和硬件连接时生成的数组
		OnCancel();    //退出程序
		return;
		}
	case (IDCANCEL):       //格式化程序
		{
		 if(key==true)
		  { 
			delete []ColorBuff; //删除加载到内存中的相位屏数据
			if(m_Len<ImgHeight)
			{ 
				delete []ColorBuff_512;         //删除数组
			}
		  }
		 key=false;
		 m_Begin.EnableWindow(true);
		 m_Prepare_value.EnableWindow(true);
		 m_UP.EnableWindow(false);
		 m_DOWN.EnableWindow(false);
		 m_Add.EnableWindow(false);
		 m_StartStopButton.EnableWindow(false);//使“上电”、“START”、“UP”、“DOWN”、“保存”按钮处于不可用状态。
		 m_SlmPwrButton.EnableWindow(false);
		 m_Save.EnableWindow(false);
		 m_EDIT_BN=0; 
	     m_EDIT_EN=0;
         m_speed=0;                //将控制面板上的定时等参数归零。
	     m_frame=0.0;
	     m_Now=0;
		 m_L0=0;
		 m_i0=0;
		 m_r0=0;
		 m_Width_m=0;
		 m_Len_m=0;
		 m_T=0;
		 UpdateData(false);
		 return;        //格式化程序完成之后返回主程序。
		}
	default:
		{
			return; //返回主程序
		}
	}
}


void CBNS_APPDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
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
	m_SlmPwrButton.SetWindowText(_T("ON POWER"));          //初始化上电控件为："ON POWER",表示等待上电状态。
	m_StartStopButton.SetWindowText(_T("START"));         //初始化开始控件，设置为“START”,表示等待加载相位屏数据。
	if(LC_Type == 1)
		m_CompensatePhaseCheckbox.ShowWindow(false);      //如果液晶为向列型液晶，则不使用补偿。
	else
		m_CompensatePhaseCheckbox.ShowWindow(true);       //否则使用补偿。
	m_SlmPwrButton.EnableWindow(true);
	m_Load.EnableWindow(false);

}


void CBNS_APPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (Down_Up)
	{
	case 1:
		UpdateData(true);
	Page_0=m_Now;
	Page_0+=Pixel;
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-1）
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
	if(m_EDIT_BN==0&&m_EDIT_EN==0)   //如果未进行初值设定，则将初值设置为0，终值设置为（Page-Pixel）
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