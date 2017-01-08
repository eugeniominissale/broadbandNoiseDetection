//
//  myFFT.h
//  tesi
//
//  Created by Eugenio  on 26/09/16.
//
//

#ifndef myFFT_h
#define myFFT_h

#include <stdio.h>
#include ".././Source/kiss_fft130/kiss_fft.h"
#include ".././Source/kiss_fft130/kiss_fftr.h"

class myFFT {
public:
    myFFT();
    ~myFFT();
    kiss_fft_cpx* copycpx(float *mat, int nframe);
    float* doFFT(float *input, int puntiFFT);
};

#endif /* myFFT_h */
