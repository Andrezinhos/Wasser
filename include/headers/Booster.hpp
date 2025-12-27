#pragma once
#include "miniaudio.h"
#include <string>

struct Eq{
    ma_data_source_base ds;
    ma_decoder decoder;
    ma_biquad biq;
};

class Booster{
private:
    ma_engine engine;
    bool initiated;
    std::string currentSong;
    ma_sound sound;
    bool soundLoaded;

public:
    
    Booster();
    ~Booster();

    bool init();
    void play(const std::string& filepath);
    void replay();
    void stop();
    void setVol(float vol);
};