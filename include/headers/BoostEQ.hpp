#pragma once
#include "miniaudio.h"
#include <string>

class EQ{
public:
    static void setLow(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float cutoffFreq, float Q); 
    static void setMid(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float cutoffFreq, float Q); 
    static void setHigh(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float cutoffFreq, float Q);
};