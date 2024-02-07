#include "SineOscillator.h"
#include <cmath>

SineOscillator::SineOscillator(float freq, float amp, int SampleRate)
    : frequency(freq),
      amplitude(amp),
      sampleRate(SampleRate),
      angle(0.0f),
      offset(2 * M_PI * frequency / sampleRate) {}

const float SineOscillator::getFrequency() const
{
    return frequency;
}

const float SineOscillator::getAmplitude() const
{
    return amplitude;
}

const float SineOscillator::getSampleRate() const
{
    return sampleRate;
}

float SineOscillator::getNextSample()
{
    auto sample = amplitude * sin(angle);
    angle += offset;
    return sample;
}

void SineOscillator::setFrequency(int freq)
{
    // Negative Checking

    if (freq < 0)
        throw 1;

    // Aliasing Checking

    int criticalFrequency = 2 * sampleRate;

    if (freq >= criticalFrequency)
        throw 1;

    // Updating

    frequency = freq;
    updateOffset();
}

void SineOscillator::setAmplitude(int amp)
{
    // Negative Checking
    if (amp < 0)
        throw 1;

    // Updating
    amplitude = amp;
}

void SineOscillator::setSampleRate(int SampleRate)
{
    // Negative Checking
    if (SampleRate < 0)
        throw 1;

    // Aliasing Checking
    int criticalFrequency = 2 * SampleRate;

    if (frequency >= criticalFrequency)
        throw 1;

    // Updating
    sampleRate = SampleRate;
    updateOffset();
}

void SineOscillator::updateOffset()
{
    offset = (2 * M_PI * frequency) / sampleRate;
}
