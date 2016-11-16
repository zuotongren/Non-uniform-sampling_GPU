#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "math.h"
#include <math_constants.h>
#include <device_functions.h>
#define POINT 512         //液晶屏上列（行）向像素点个数为512个
#define Samp_point (512)//采样点数
using namespace std;
struct double_complex
{
	double real;
	double imag;
};//定义结构体类型：复数由两个double类型的数组成
extern "C" int cuda_PSD_sample(int Nf,double *PSD_sample,double *sequex);
extern "C" cudaError_t cuda_Phase(double_complex*Phase,double_complex * Rand_Spect_Lin,double*ka_dbside,int sm,int D);
