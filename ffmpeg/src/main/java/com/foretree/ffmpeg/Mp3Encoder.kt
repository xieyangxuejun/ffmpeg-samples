package com.foretree.ffmpeg

/**
 * Created by silen on 2018/8/31 22:21
 * Copyright (c) 2018 in FORETREE
 */
class Mp3Encoder {
    companion object {
        init {
            System.loadLibrary("mp3core")
        }
    }

    external fun init(pcmFile: String, channels: Int, bitRate: Int, sampleRate: Int, mp3File: String)
    external fun encode()
    external fun destroy()
}