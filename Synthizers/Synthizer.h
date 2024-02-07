#pragma once

class Synthizer
{
private:

public:
    Synthizer(){}

    virtual float getNextSample() = 0;
};

