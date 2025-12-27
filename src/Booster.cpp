#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "Booster.hpp"
#include "BoostEQ.hpp"
#include "vector"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Booster::Booster() : initiated(false), soundLoaded(false) {
    if (ma_engine_init(NULL, &engine) == MA_SUCCESS){
        initiated = true;
        std::cout << "Booster Initiated\n";
    } else {
        std::cout << "Booster could Init\n";
    }
}

Booster::~Booster(){
    if (soundLoaded){
        ma_sound_uninit(&sound);
    }
    if (initiated){
        ma_engine_uninit(&engine);
    }
}

EQ beq;
Eq eq;

ma_result EQ_onRead(ma_data_source* pDataSource, void* pFramesOut, ma_uint64 frameCount, ma_uint64* pFramesRead) {
    Eq* equ = (Eq*)pDataSource; 
    std::vector<uint8_t> temp(frameCount * equ->decoder.outputChannels * ma_get_bytes_per_sample(equ->decoder.outputFormat));
    ma_uint64 framesRead;

    ma_decoder_read_pcm_frames(&equ->decoder, temp.data(), frameCount, &framesRead); // aplica o filtro
    // ma_biquad_process_pcm_frames(&equ->biq, pFramesOut, temp.data(), framesRead); 
    memcpy(pFramesOut, temp.data(), framesRead * equ->decoder.outputChannels * ma_get_bytes_per_sample(equ->decoder.outputFormat));
    *pFramesRead = framesRead; 
    return MA_SUCCESS;
}

ma_result EQ_onSeek(ma_data_source* pDataSource, ma_uint64 frameIndex){
    Eq* equ = (Eq*)pDataSource;
    return ma_decoder_seek_to_pcm_frame(&equ->decoder, frameIndex);
}

ma_result EQ_onGetDataFormat(ma_data_source* pDataSource, ma_format* pFormat, ma_uint32* pChannels, ma_uint32* pSampleRate, ma_channel* pChannelMap, size_t channelMapCap){
    Eq* equ = (Eq*)pDataSource;
    *pFormat = equ->decoder.outputFormat; 
    *pChannels = equ->decoder.outputChannels; 
    *pSampleRate = equ->decoder.outputSampleRate; 
    return MA_SUCCESS;
}

static ma_data_source_vtable g_eq_vtable = {
    EQ_onRead,
    EQ_onSeek,
    EQ_onGetDataFormat,
    0,
    0,
    0,
    0
};

ma_result Eq_init(Eq* eq) {
    ma_data_source_config config;
    config.vtable = &g_eq_vtable;

    return ma_data_source_init(&config, &eq->ds);
}

void Booster::play(const std::string& songName){
    if (!initiated) return;

    fs::path fullpath = "C:/WasserEngine/songs/" + songName;

    if (!fs::exists(fullpath)){ 
        std::cout << "Cannot find: " << fullpath << "\n";
    }

    if (soundLoaded){
        ma_sound_uninit(&sound);
        soundLoaded = false;
    }

    if (ma_decoder_init_file(fullpath.string().c_str(), NULL, &eq.decoder) != MA_SUCCESS){
        std::cout << "couldn't decode" << "\n";
        return;
    }

    if (Eq_init(&eq) != MA_SUCCESS){
        std::cout << "couldn't init Eq data source\n";
        return;
    }
    
    if (ma_sound_init_from_data_source(&engine, (ma_data_source*)&eq, 0, NULL, &sound) == MA_SUCCESS){
        ma_sound_set_volume(&sound, 1.0f);
        soundLoaded = true;
        ma_sound_start(&sound);
        currentSong = songName;
        std::cout << "Playing with BoostEQ\n";
    } 
    
    // if (ma_sound_init_from_file(&engine, fullpath.string().c_str(), 0, NULL, NULL, &sound) == MA_SUCCESS){
    //     ma_sound_set_volume(&sound, 1.0f);
    //     soundLoaded = true;
    //     ma_sound_start(&sound);
    //     currentSong = songName;
    //     std::cout << "Playing with BoostEQ\n";
    // } 
    else {
        std::cout << "Couldn't play: " << fullpath << "\n";
    }
}

void Booster::replay(){
    if (soundLoaded) {
        ma_sound_seek_to_pcm_frame(&sound, 0);
        ma_sound_start(&sound);
        std::cout << "Replaying\n";
    } else {
        std::cout << "No added song\n" << "\n";
        return;
    }
}

void Booster::stop() {
    if (soundLoaded){
        ma_sound_stop(&sound);
        std::cout << "Stoped\n";
    }
}

void Booster::setVol(float vol) {
    if (soundLoaded){
        ma_sound_set_volume(&sound, vol);
        std::cout << "Set Volume to: " << vol;
    }
}