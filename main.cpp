#include "../JuceLibraryCode/JuceHeader.h"
#include "myFFT.h"
#include "myJuceFFT.h"
#include "wavLib.h"

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

float varianza (float *input, int k)
{
    float var = 0, sum=0;
    for (int i=0;i<k;i++)
        sum+=input[i];
    float mean = static_cast<float>(sum)/k;
    for(int i = 0;i<k;++i)
        var += (input[i]-mean)*(input[i]-mean)/(k-1);
    return var;
}

inline float amplitudeTodB(float amplitude)
{
    return 20.0f * log10(amplitude);
}

//==============================================================================

int main (int argc, char* argv[])
{
    wavLib rw;
    myFFT fft;
    myJuceFFT fftJ;
    float *samples;
    int lenghtInSamples=0, sampleRate=0;
    char percorsoAssolutoFile[]={"/Users/eugenio/tesi/Source/heyjudeAcap.wav"};
    
    // Leggo i campioni del file wav in ingresso
    samples=rw.readWav(percorsoAssolutoFile, &lenghtInSamples, &sampleRate);

    int lBuffer=1024, fineFile=0, in1, in2, c, i, k=0;
    float vTemp[1024], k2=1;
    float *fftTemp=NULL;
    float SNR;
    int colSpectrogram=((ceil(lenghtInSamples/1024))*2)-1;
    float minFFT[colSpectrogram], maxFFT[colSpectrogram];
    
    // Bufferizzazione - FFT
    while(fineFile==0)
    {
        in1=(k2*lBuffer)-(lBuffer);
        in2=(k2*lBuffer);
        if(in2<=lenghtInSamples)
        {
            fftTemp=new float;
            c=0;
            for(i=in1; i<in2; i++)
            {
                vTemp[c]=samples[i];
                c++;
            }
            fftTemp=fftJ.doFFT(vTemp, 1024);
            
            // Calcolo Massimi/minimi
            float max=0.0;
            for (i=0; i<1024; i++)
            {
                if (max<fftTemp[i])
                    max=fftTemp[i];
            }
            
            // 15000 - 21050 Hz
            float min=fftTemp[0];
            for (i=697; i<1024; i++)
            {
                if (min>fftTemp[i])
                    min=fftTemp[i];
            }
            
            minFFT[k]=min;
            maxFFT[k]=max;
            
            k2+=0.5;
            k++;
        }
        else
        {
            fineFile=1;

        }
    }
 
    float varMin,varMax;
    varMax=varianza(maxFFT,k);
    varMin=varianza(minFFT,k);
    SNR=amplitudeTodB(varMax/varMin);
    
    printf("\nSNR: %.0f\n",SNR);
    
    return 0;
}

