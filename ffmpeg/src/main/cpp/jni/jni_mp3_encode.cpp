//
// Created by silen on 2018/8/31.
//
#include <jni.h>
#include "../lame/mp3_encoder.h"

Mp3Encoder *encoder;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_foretree_ffmpeg_Mp3Encoder_init(
        JNIEnv *env, jobject obj,
        jstring pcm_path, jint channels, jint bit_rate,
        jint sample_rate, jstring mp3_path) {
    const char *pcm_file_path = env->GetStringUTFChars(pcm_path, NULL);
    const char *mp3_file_path = env->GetStringUTFChars(mp3_path, NULL);
    encoder = new Mp3Encoder();
    encoder->Init(pcm_file_path, mp3_file_path, sample_rate, channels, bit_rate);
    env->ReleaseStringUTFChars(pcm_path, pcm_file_path);
    env->ReleaseStringUTFChars(mp3_path, mp3_file_path);
}

JNIEXPORT void JNICALL
Java_com_foretree_ffmpeg_Mp3Encoder_encode(
        JNIEnv *env, jobject obj) {
    if (encoder) {
        encoder->Encoder();
    }
} ;

JNIEXPORT void JNICALL
Java_com_foretree_ffmpeg_Mp3Encoder_destroy(
        JNIEnv *env, jobject obj) {
    if (encoder) {
        encoder->Destroy();
    }
} ;

#ifdef __cplusplus
}
#endif
