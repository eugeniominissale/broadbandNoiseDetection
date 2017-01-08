//
//  myJuceFFT.h
//  tesi
//
//  Created by Eugenio  on 04/10/16.
//
//

#ifndef myJuceFFT_h
#define myJuceFFT_h

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>

class myJuceFFT {
public:
    myJuceFFT();
    ~myJuceFFT();
    float* doFFT(float *input, int puntiFFT);
};

#endif /* myJuceFFT_h */
