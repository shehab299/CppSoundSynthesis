#pragma once
#include "Synthizer.h"


class SineOscillator : public Synthizer
{
    //Parameters
    float frequency;
    float sampleRate;
    float amplitude;

    //Internal Variables
    float angle;
    float offset;

    void updateOffset();

public:
    SineOscillator(float freq, float amp, int SampleRate);

    float getNextSample();

    void setFrequency(int frequency);
    const float getFrequency() const;

    void setAmplitude(int amplitude);
    const float  getAmplitude() const;

    void setSampleRate(int sampleRate);
    const float getSampleRate() const;
};
