#include "BoostEQ.hpp"
#include "miniaudio.h"
#include <iostream>
#include <cmath>

void EQ::setLow(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float freq, float Q){

    float omega = 2.0 * M_PI * freq / sampleRate;
    float alpha = sinf(omega) / (2.0f * Q);
    float cosw = cosf (omega);
 
    float b0 = (1.0 - cosw) * 0.5f;
    float b1 = 1.0 - cosw;
    float b2 = (1.0 - cosw) * 0.5f;
    float a0 = 1.0 - alpha;
    float a1 = -2.0f * cosw;
    float a2 = 1.0 - alpha;

    b0 /= a0; b1 /= a0; b2 /= a0;
    a1 /= a0; a2 /= a0;
    a0 = 1.0;
    ma_biquad_config cfg = ma_biquad_config_init(fmt, channels, sampleRate, b0, b1, b2, a1, a2);

    if (ma_biquad_init(&cfg, NULL, biq) != MA_SUCCESS) { 
        std::cout << "Erro ao inicializar biquad\n"; 
    }
}

void EQ::setHigh(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float freq, float Q){

    float omega = 2.0 * M_PI * freq / sampleRate;
    float alpha = sinf(omega) / (2.0f * Q);
    float cosw = cosf (omega);
 
    float b0 = (1.0 - cosw) * 2.0f;
    float b1 = -(1.0 - cosw);
    float b2 = (1.0 - cosw) * 2.0f;
    float a0 = 1.0 - alpha;
    float a1 = -2.0f * cosw;
    float a2 = 1.0 - alpha;

    b0 /= a0; b1 /= a0; b2 /= a0;
    a1 /= a0; a2 /= a0;
    a0 = 1.0;
    ma_biquad_config cfg = ma_biquad_config_init(fmt, channels, sampleRate, b0, b1, b2, a1, a2);

    if (ma_biquad_init(&cfg, NULL, biq) != MA_SUCCESS) { 
        std::cout << "Erro ao inicializar biquad\n"; 
    }
}

void EQ::setMid(ma_biquad* biq, ma_format fmt, ma_uint32 channels, ma_uint32 sampleRate, float freq, float Q){
    ma_biquad biquad;

    float omega = 2.0 * M_PI * freq / sampleRate;
    float alpha = sinf(omega) / (2.0f * Q);
    float cosw = cosf (omega);
 
    float b0 = alpha;
    float b1 = 0.0f;
    float b2 = -alpha;
    float a0 = 1.0 + alpha;
    float a1 = -2.0f * cosw;
    float a2 = 1.0 - alpha;

    b0 /= a0; b1 /= a0; b2 /= a0;
    a1 /= a0; a2 /= a0;
    a0 = 1.0;
    ma_biquad_config cfg = ma_biquad_config_init(fmt, channels, sampleRate, b0, b1, b2, a1, a2);

    if (ma_biquad_init(&cfg, NULL, biq) != MA_SUCCESS) { 
        std::cout << "Erro ao inicializar biquad\n"; 
    }
}