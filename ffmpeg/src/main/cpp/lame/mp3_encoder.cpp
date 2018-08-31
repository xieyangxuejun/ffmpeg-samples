//
// Created by silen on 2018/8/27.
//

#include "mp3_encoder.h"

Mp3Encoder::Mp3Encoder() {

}

Mp3Encoder::~Mp3Encoder() {

}

int Mp3Encoder::Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels,
                     int bitRate) {
    int ret = -1;
    pcmFile = fopen(pcmFilePath, "rb");
    if (pcmFile) {
        mp3File = fopen(mp3FilePath, "wb");
    }

    if (mp3File) {
        lameClient = lame_init();
        lame_set_in_samplerate(lameClient, sampleRate);
        lame_set_out_samplerate(lameClient, sampleRate);
        lame_set_num_channels(lameClient, channels);
        lame_set_brate(lameClient, bitRate / 1000);
        lame_init_params(lameClient);
        ret = 0;
    }
    return ret;
}

void Mp3Encoder::Encoder() {
    int buffer_size = 1024 * 256;
    short* buffer = new short[buffer_size/2];
    short* left_buffer = new short[buffer_size/4];
    short* right_buffer = new short[buffer_size/4];
    unsigned char* mp3_buffer = new unsigned char[buffer_size];
    size_t read_buffer_size = 0;
    while ((read_buffer_size = fread(buffer, 2, buffer_size / 2, pcmFile)) > 0) {
        for(int i = 0; i < read_buffer_size; i++) {
            if (i % 2) {
                left_buffer[i/2] = buffer[i];
            } else {
                right_buffer[i/2] = buffer[i];
            }
        }

        size_t write_buffer_size = lame_encode_buffer(lameClient, left_buffer, right_buffer, read_buffer_size/2, mp3_buffer, buffer_size);
        fwrite(mp3_buffer, 1, write_buffer_size, mp3File);
    }

    delete [] buffer;
    delete [] left_buffer;
    delete [] right_buffer;
    delete [] mp3_buffer;
}

void Mp3Encoder::Destroy() {
    if (pcmFile) {
        fclose(pcmFile);
    }
    if (mp3File) {
        fclose(mp3File);
        lame_close(lameClient);
    }

}
