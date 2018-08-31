//
// Created by silen on 2018/8/27.
//

#ifndef FFMPEG_SAMPLES_MP3_ENCODER_H
#define FFMPEG_SAMPLES_MP3_ENCODER_H


#include <stdio.h>
#include <lame/lame.h>

class Mp3Encoder {
private:
    FILE* pcmFile;
    FILE* mp3File;
    lame_t lameClient;

public:
    Mp3Encoder();
    ~Mp3Encoder();
    int Init(const char* pcmFile, const char* mp3File, int sampleRate,
            int channels, int bitRate);
    void Encoder();
    void Destroy();


};


#endif //FFMPEG_SAMPLES_MP3_ENCODER_H
