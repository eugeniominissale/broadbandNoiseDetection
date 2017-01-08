//
//  myJuceFFT.cpp
//  tesi
//
//  Created by Eugenio  on 04/10/16.
//
//

#include <stdio.h>
#include <math.h>      
#include "../JuceLibraryCode/JuceHeader.h"
#include "myJuceFFT.h"

myJuceFFT::myJuceFFT() {}
myJuceFFT:: ~myJuceFFT() {}

float* myJuceFFT::doFFT(float *input, int puntiFFT)
{
    float *resFFT=new float [puntiFFT];
    int numSamples=puntiFFT;
    
    FFT lForwardFFT(10, false);
    FFT::Complex lTData[numSamples];
    FFT::Complex lSpectrumData[numSamples];

    for(int i = 0; i< numSamples; i++)
    {
        lTData[i].r = input[i];
        lTData[i].i = 0.f;
    }
    
    lForwardFFT.perform(lTData, lSpectrumData);
    
    for(int i = 0; i< 1024; i++)
        resFFT[i]=sqrtf((lSpectrumData[i].r)*(lSpectrumData[i].r))+((lSpectrumData[i].i)*(lSpectrumData[i].i));
    for(int i = 0; i< 1024; i++)
        resFFT[i]=(resFFT[i]*resFFT[i])/1024;
    
    return resFFT;
}