//
//  myFFT.cpp
//  tesi
//
//  Created by Eugenio  on 26/09/16.
//
//

#include "myFFT.h"

myFFT::myFFT() {}
myFFT::~myFFT() {}

kiss_fft_cpx* myFFT::copycpx(float *mat, int nframe)
{
     int i;
     kiss_fft_cpx *mat2;
     mat2=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*nframe);
     kiss_fft_scalar zero;
     memset(&zero,0,sizeof(zero));
     for(i=0; i<nframe ; i++)
     {
         mat2[i].r = mat[i];
         mat2[i].i = zero;
     }
     return mat2;
}

float* myFFT::doFFT(float *input, int puntiFFT)
{
     float *resFFT=new float [puntiFFT];
     kiss_fft_cpx out_cpx[puntiFFT], *cpx_buf;
     kiss_fftr_cfg fft = kiss_fftr_alloc(puntiFFT*2,0,0,0);
     cpx_buf = copycpx(input,puntiFFT);
     
     for(int i=0;i<1024;i++)
          resFFT[i]=out_cpx[i].r=0;
     
     kiss_fftr(fft,(kiss_fft_scalar*)cpx_buf, out_cpx);
     
     for(int i = 0; i< 1024; i++)
          resFFT[i]=sqrtf((out_cpx[i].r)*(out_cpx[i].r))+((out_cpx[i].i)*(out_cpx[i].i));
     for(int i = 0; i< 1024; i++)
          resFFT[i]=(resFFT[i]*resFFT[i])/1024;
     
     kiss_fft_cleanup();
     free(fft);
     
     return resFFT;
}