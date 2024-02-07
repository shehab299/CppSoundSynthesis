#include <iostream>
#include <fstream>
#include <cmath>
#include "Synthizers/Synthizer.h"
#include "Synthizers/SineOscillator.h"
#include "WaveFileGen.h"


// Example usage:
int main() {
    const char* fileName = "output.wav";
    int sampleRate = 44100;
    int bitDepth = 16;
    int duration = 100;
    int amplitude = 1; // Max amplitude for 16-bit depth

    Synthizer* osc = new SineOscillator(440, amplitude, sampleRate);

    WaveFileGenerator waveGenerator(fileName, sampleRate, bitDepth);
    waveGenerator.generateFile(duration, amplitude, osc);

    return 0;
}


