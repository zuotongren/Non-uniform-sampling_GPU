// BNS_APPDlg.h : ͷ�ļ�
//
#include "FFTW/fftw3.h"
#include"cuda.h"
#pragma once


#include "BNSPCIeBoard\BNSPCIeHardware.h" //���Ӯ������ͷ�ļ�
#include "BNSPCIeBoard\BNSPCIeBoard.h"

#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include <string>
#include "afxwin.h"

#include "afxcmn.h" 

using namespace std;


#define PI 3.1415926f      //�еĶ���
#define e  2.7182818f      //��Ȼ��e�Ķ���
#define LC 0.00768        //Һ�����Ŀ��Ϊ7.68mm
#define Mosaic 64         //ƴ�Ӳ���Ϊ500��pixel
#define T_1_1 0.0044       //����һ����λ������ʱ��
#define Up false
#define Down true
#define m_Rr (POINT/m_Width_m) //�궨��m_Rr

//***** ���µĶ���Ϊ������Һ��Ӳ��������Ҫ�õ��ı���  ****//
typedef struct
{
	//pointer to the board
	CBNSPCIeBoard* theBoard;
	unsigned char*	PhaseCompensationData;
	unsigned char*  SystemPhaseCompensationData;
	unsigned char*	LUT;

	CString			LUTFileName;
	CString			PhaseCompensationFileName;
	CString			SystemPhaseCompensationFileName;
} Board_Entry;

typedef CTypedPtrList<CPtrList, Board_Entry*> CBoard_List;
//struct double_complex
//{
//	double real;
//	double imag;
//};//����ṹ�����ͣ�����������double���͵������
struct  double_xy
{
	double x;
	double y;
};//����ṹ�����ͣ���������double��������
struct int_xy
{
	int x;
	int y;
};//����ṹ�����ͣ���������int��������
struct My_st
{
	double m_L0;
	double m_i0;
	double m_r0;
	int m_speed;    //��ʱ����ʱʱ��
	float m_frame;   //֡��
	int m_Width_m;
	int m_Len_m;
	int m_T;
};
// CBNS_APPDlg �Ի���
class CBNS_APPDlg : public CDialog
{
// ����
public:


/****************************************************/

    LARGE_INTEGER M_Begin;  //��������ʼ��
	LARGE_INTEGER M_End;    //��������ֹ��
    LARGE_INTEGER TimeToL;  //
	LARGE_INTEGER Frequence;//ȡ�߾������м�������Ƶ��
   
	HICON m_hicn1;
	HICON m_hicn2;
	CFile file;      // CFile���� 
	CFile File;
	double *ColorBuff; //���ڴ����λ����Ϣ�Ķ�̬����
	unsigned __int8 *ColorBuff_512;//��Һ�����ص������ͬ��һ�����飬��������ʱ�����λ������
	double **A_P;

	CBNS_APPDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void			LoadSequence(double *ColorBuff);    //��Ӳ��������λ������
	bool			ReadAndScaleBitmap(unsigned char* buffer, CString ImagePath);//��ȡ���仯λͼ��С
	unsigned char*	ScaleBitmap(unsigned char* InvertedImage, int BitmapSize, int FinalBitmapSize);//����λͼ��С
	bool			ReadLUTFile(unsigned char* LUTBuf, CString LUTPath);//��ȡLUT�ļ�

    //Global variables
	int			NumBoards;    //����ʹ�õ�Ӳ������
	bool		LC_Type;      //bool �ͱ��� ��������Һ������  1��������  0��������
	int			FrameRate;    //֡��
	unsigned short TrueFrames; //ʵ��֡��
	int			ImgHeight;     //Һ�����߶ȣ���ʾ�������ص�
	int			ImgWidth;      //Һ������ȣ���ʾ�������ص�
	CBoard_List BoardList;     
  // �Ի�������
	enum { IDD = IDD_BNS_APP_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();   //��ʼ������
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    virtual void	OnOK();  
    afx_msg void	ToOnClose();  //������Ӳ�����ɵ������ͷŵ�
	DECLARE_MESSAGE_MAP()
public:

	BITMAPFILEHEADER fileheader;  //����BMP��ʽͼƬʱ��ͷ��Ϣ
	BITMAPINFOHEADER infoheader;  //����BMP��ʽͼƬʱ�����Ϣͷ
	//BITMAPINFO INFO;
	BITMAPINFO *INFO;
	RGBQUAD *RGB;                 //���ڴ�ŵ�ɫ��Ķ�̬����

	int m_EDIT_BN;   //�ؼ�����ʼ��ʾ�š��ı���
	int m_EDIT_EN;   //��������ʾ�š��ı���
	int Page;        //���ļ�ʱ������ļ��ָ�����ı���
	int Page_0;      //������ʾ����ӡ��ǰ��λ��
	int biWidth;     //��λ����ȣ����ص�����
	int	biHeight;    //��λ���߶ȣ����ص�����
	int Page_end;    //���ڼ�¼ѭ����ʾ������
	long Pixel;
	int Mosaic_Pixel;
	int m_Now;       //���ڰ�����ʾ��ǰ��λ����
	bool key;        //�����Ƿ�Ϊ�����λ�����ݵ���������ڴ�ı�־
	bool Down_Up;

	//void ReadFileToBuff(unsigned char *ColorBuff);    //��ȡ��λ�����ݵ�ָ������
	void Display_Picture(double *ColorBuff);  //����ȡ������λ����Ϣ��ӡ����Ļ��
	void ChangeTo512(unsigned __int8 *ColorBuff1,unsigned __int8 *ColorBuff_512); //��С��POINT����λ��ת��ΪPOINT*POINT��С
	void LoadHardBoard();                             //����λ����Ϣ���ص�Ӳ����
	void My_Delay(LARGE_INTEGER Interval);            //��ʱ����
	void Save_Pic_BMP(double *PictureBuff,int page,int Height,int Width); //������λ����Ϣ��BMP��ʽ��
    
	CButton m_Begin;         //��塰��ʼ���ؼ��ı���
    CStatic m_Picture;       //��塰ͼƬ���ؼ��ı���
	CString CS_Page;         //��塰�ļ���λ�����ؼ��ı���
	CButton m_CompensatePhaseCheckbox; //����������Һ���д˿ؼ�����ʾ��
	CButton m_StartStopButton;         //��塰STATE���ؼ��ı���
	CButton m_SlmPwrButton;            //��塰ON POWER���ؼ��ı���
	BOOL m_CompensatePhase;            //����������Һ���д˿ؼ�����ʾ��
	CButton m_UP;       //��塰UP���ؼ��ı���
	CButton m_DOWN;     //��塰DOWN���ؼ��ı���
	CButton m_Open;     //��塰�򿪡��ؼ��ı���
	CButton m_out;      //��塰�˳����ؼ��ı���
	CButton m_Save;     //��塰���桱�ؼ��ı���
	CString strFilePath;//��塰�ļ�·�����ؼ��ı���

	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedStartStopButton();
	afx_msg void OnBnClickedSlmPwrButton();
	afx_msg void OnBnClickedButtonGo();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedCompensatePhaseCheckbox();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnEnChangeEditBeginNum();
//	afx_msg void OnEnChangeEditEndNum();

	double m_L0;
	double m_i0;
	double m_r0;
	double m_fm;
	double m_errorboundd;
	double m_errorboundu;
	int m_Width;
	int m_Width_m;
	int m_Len;
	int m_Len_m;
	int m_speed;    
	float m_frame;   //֡��
	int T_Len;
	int m_T;
	int m_now_frame;
	My_st file_head;
	CString FileToSavePath;
	CString FileToSavePath_1;
	CString FileToSavePath_2;
	/*CProgressCtrl m_progress;
	CProgressCtrl m_progress_file;*/
	CButton m_Prepare_value;
	CString GetPathToSave();

	double integral(double(CBNS_APPDlg:: *fun)(double), double a, double b);
	double psdevalfunKolspf(double x);
	double randn();
	CString rands();
	long double psdevalfun(double f0, double f1, double f2, int samppoints);
    void Sequencer(double* f_sequence,double ** f_area,double ka_L,double ka_H,int Nf);

	void Norseque2(double *sequencex, int com_x, double *sequencey, int com_y, double **f_area);
	double Min(double *ka_dbside, int point);
	double Max(double *ka_dbside, int point);
	double Mod_double(double dividend, double divisor);
	float Mod_float(float dividend, double divisor);
	void fftshift(double_complex **matrix_old, double_complex **matrix_new, int row, int column);
	void Whitenoise(int com_x, int com_y,double_complex **whitenoise);
	void Summation(double **Spectrum1,double *ka_dbside, int Nf);
	void save_data(double **A_P);
	void save_data_1(double **A_P);
	void save_data_2(double **A_P);
	void save_headata();
	void Create_File();

	void Create_File_1();
	void Create_File_2();

	afx_msg void OnBnClickedButtonYushezhi();
	afx_msg void OnBnClickedButtonKaishi();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonOut();
	
	afx_msg void OnBnClickedAdd();
	CButton m_Load;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonAdd();
	CButton m_Add;
	CProgressCtrl m_Progress;
};

