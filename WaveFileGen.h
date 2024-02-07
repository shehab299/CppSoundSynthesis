#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include "Synthizers/Synthizer.h" 

class WaveFileGenerator {
public:
    WaveFileGenerator(const char* fileName, int sampleRate, int bitDepth);

    void generateFile(int duration, int amp, Synthizer* gen);

private:
    const char* fileName;
    int sampleRate;
    int bitDepth;

    void writeToFile(std::ofstream &file, int value, int size);
    void writeHeaders(std::ofstream &file, int duration);
    void writeAudioData(std::ofstream &file, Synthizer* gen, int duration, int amp);
    void updateHeaderInfo(std::ofstream &file, int preAudioPosition, int postAudioPosition);
};
