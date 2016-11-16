#include"cuda.h"
#include "device_functions.h"
__constant__ double dev_a[Samp_point];
__global__ void addKernel(double *PSD_sample,double * seque)
{
	
	const int i=threadIdx.x+blockIdx.x*blockDim.x;
	const double k=0.490*(pow(0.1, -(5.0 / 3.0)));
	PSD_sample[i] = k*pow((pow(seque[blockIdx.x],2.0)+pow(seque[threadIdx.x],2.0)),-(11.0/6.0));
}


__global__ void Kernel(double_complex*Phase , double_complex * Rand_Spect_Lin ,int sm,int D)
{
	__shared__ double_complex Phase_part[Samp_point];//声明一个共享内存，用于存放生成的结果
	const double DX=1.0*D/POINT;
	int s=0;
	const int block_Idx = gridDim.x * blockIdx.y + blockIdx.x;
	double sum1=0.0,sum2=0.0,sum3=0.0,sum4=0.0;
	double x=dev_a[blockIdx.x]*(( sm + 1)*DX)+dev_a[threadIdx.x]*((blockIdx.y +1)*DX);
	if(blockIdx.x==Samp_point-1 || threadIdx.x == Samp_point-1 )
	{
		Phase_part[threadIdx.x].real = 0.0;
		Phase_part[threadIdx.x].imag = 0.0;
	}
	else
	{
      sum1=Rand_Spect_Lin[( blockDim.x )*blockIdx.x+threadIdx.x].real*(cos(x));
	  sum2=Rand_Spect_Lin[( blockDim.x )*blockIdx.x+threadIdx.x].imag*(sin(x));
	  sum3=Rand_Spect_Lin[( blockDim.x )*blockIdx.x+threadIdx.x].real*(sin(x));
	  sum4=Rand_Spect_Lin[( blockDim.x )*blockIdx.x+threadIdx.x].imag*(cos(x));
	  Phase_part[threadIdx.x].real = sum1 - sum2;
	  Phase_part[threadIdx.x].imag = sum3 + sum4;
	}
	__syncthreads();
	int j=blockDim.x/2;
	while(j!=0)
	{
	   if(s<=threadIdx.x && threadIdx.x< j)
		{
			Phase_part[threadIdx.x ].real += Phase_part[threadIdx.x - s + j].real;
			Phase_part[threadIdx.x ].imag += Phase_part[threadIdx.x - s + j].imag;
		}
		__syncthreads();
	   if(j%2!=0 && j!=1)
		{
			j=j+1;
			s=1;
		}
	   else s=0;
		j /=2;
	}
	if(threadIdx.x == 0)
		Phase[block_Idx]=Phase_part[0];


}
//__constant__ double dev_a[257];
// Helper function for using CUDA to add vectors in parallel.
int cuda_PSD_sample(int Nf,double *PSD_sample,double *sequex)
{
	double *dev_a = 0;
    double *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
	// Allocate GPU buffers for three vectors (one input, one output).
    cudaStatus = cudaMalloc((void**)&dev_a, Nf * sizeof(double));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_c, Nf*Nf * sizeof(double));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
	cudaStatus = cudaMemcpy(dev_a,sequex, Nf * sizeof(double),cudaMemcpyHostToDevice);//, cudaMemcpyHostToDevice
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
     //Copy input vectors from host memory to GPU buffers.
	//cudaStatus = cudaMemcpyToSymbol(dev_a,sequex, Nf * sizeof(double));//, cudaMemcpyHostToDevice
 //   if (cudaStatus != cudaSuccess) {
 //       fprintf(stderr, "cudaMemcpy failed!");
 //       goto Error;
 //   }

    // Launch a kernel on the GPU with one thread for each element.
    addKernel<<<Nf,Nf>>>(dev_c,dev_a);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
	
		 cudaStatus = cudaMemcpy(PSD_sample, dev_c, Nf*Nf*sizeof(double), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
	}
   
Error:
	cudaFree(dev_a);
	cudaFree(dev_c);
    
    return cudaStatus;
}
/*************************************************************************/
//
//
//
//
//
//
//
//
//
//***************************************************************************/
cudaError_t cuda_Phase(double_complex*Phase,double_complex * Rand_Spect_Lin,double*ka_dbside,int sm,int D)
{
	int bbb=11;
	dim3 blocks(Samp_point,POINT);
	int threadsPerBlock=Samp_point;
    double_complex *dev_c = 0;               //在GPU上声明的 串行化数组 用于存放相位屏输出结果
	double_complex *dev_b = 0;      //在GPU上声明的 串行化数组 用于存放功率谱与随机数相乘之后的值
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
		bbb=1;
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }
	// Allocate GPU buffers for three vectors (one input, one output).
	 cudaStatus = cudaMalloc((void**)&dev_b, Samp_point*Samp_point* sizeof(double_complex));
    if (cudaStatus != cudaSuccess) {
		bbb=2;
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
    cudaStatus = cudaMalloc((void**)&dev_c, Samp_point*POINT* sizeof(double_complex));
    if (cudaStatus != cudaSuccess) {
		bbb=3;
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }
     //Copy input vectors from host memory to GPU buffers.
	cudaStatus = cudaMemcpyToSymbol(dev_a,ka_dbside, Samp_point * sizeof(double));//, cudaMemcpyHostToDevice
    if (cudaStatus != cudaSuccess) {
		bbb=5;
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }
	cudaStatus = cudaMemcpy(dev_b,Rand_Spect_Lin,Samp_point*Samp_point*sizeof(double_complex), cudaMemcpyHostToDevice);//, cudaMemcpyHostToDevice
    if (cudaStatus != cudaSuccess) {
		bbb=7;
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    Kernel<<<blocks,threadsPerBlock>>>(dev_c,dev_b,sm,D);

    //Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
		bbb=8;
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
		bbb=9;
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
	
		 cudaStatus = cudaMemcpy(Phase, dev_c,Samp_point*POINT*sizeof(double_complex), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
		bbb=10;
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
	}
   
Error:
	  //cudaFree(dev_a);
	  cudaFree(dev_b);
	  cudaFree(dev_c);
      return cudaStatus;
}
