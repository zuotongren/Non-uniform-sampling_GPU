#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "math.h"
#include <math_constants.h>
#include <device_functions.h>
#define POINT 512         //Һ�������У��У������ص����Ϊ512��
#define Samp_point (512)//��������
using namespace std;
struct double_complex
{
	double real;
	double imag;
};//����ṹ�����ͣ�����������double���͵������
extern "C" int cuda_PSD_sample(int Nf,double *PSD_sample,double *sequex);
extern "C" cudaError_t cuda_Phase(double_complex*Phase,double_complex * Rand_Spect_Lin,double*ka_dbside,int sm,int D);
