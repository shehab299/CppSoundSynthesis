#include "WaveFileGen.h"


WaveFileGenerator::WaveFileGenerator(const char* fileName, int sampleRate, int bitDepth)
    : fileName(fileName), sampleRate(sampleRate), bitDepth(bitDepth) {}

void WaveFileGenerator::generateFile(int duration, int amp, Synthizer* gen) {
    
    std::ofstream file(fileName, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    writeHeaders(file, duration);

    int preAudioPosition = file.tellp();
    writeAudioData(file, gen, duration, amp);
    int postAudioPosition = file.tellp();

    updateHeaderInfo(file, preAudioPosition, postAudioPosition);

    file.close();
}

void WaveFileGenerator::writeToFile(std::ofstream &file, int value, int size) {
    file.write(reinterpret_cast<const char*>(&value), size);
}

void WaveFileGenerator::writeHeaders(std::ofstream &file, int duration) {
    file << "RIFF";
    file << "----";
    file << "WAVE";

    // Format chunk
    file << "fmt ";
    writeToFile(file, 16, 4); // Size
    writeToFile(file, 1, 2);  // Compression code
    writeToFile(file, 1, 2);  // Number of channels
    writeToFile(file, sampleRate, 4);             // Sample rate
    writeToFile(file, sampleRate * bitDepth / 8, 4); // Byte rate
    writeToFile(file, bitDepth / 8, 2);             // Block align
    writeToFile(file, bitDepth, 2);                 // Bit depth

    // Data chunk
    file << "data";
    file << "----";
}

void WaveFileGenerator::writeAudioData(std::ofstream &file, Synthizer* gen, int duration, int amp) {
    float maxAmplitude = pow(2, bitDepth - 1) - 1;
    float factor = maxAmplitude / amp;

    for (int i = 0; i < sampleRate * duration; i++) {
        float sample = gen->getNextSample();
        int intSample = static_cast<int>(sample * factor);
        writeToFile(file, intSample, 2);
    }
}

void WaveFileGenerator::updateHeaderInfo(std::ofstream &file, int preAudioPosition, int postAudioPosition) {
    file.seekp(preAudioPosition - 4);
    writeToFile(file, postAudioPosition - preAudioPosition, 4);

    file.seekp(4, std::ios::beg);
    writeToFile(file, postAudioPosition - 8, 4);
}
