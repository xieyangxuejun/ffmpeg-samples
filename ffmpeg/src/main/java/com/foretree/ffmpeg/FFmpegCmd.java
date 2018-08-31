package com.foretree.ffmpeg;

/**
 * Created by silen on 2018/7/31 17:18
 * Copyright (c) 2018 in FORETREE
 */
public class FFmpegCmd {

    static {
        System.loadLibrary("avutil");
        System.loadLibrary("fdk-aac");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("avfilter");
        System.loadLibrary("ffmpegcore");
    }

    /**
     * 命令运行
     * @param cmd
     * @return
     */
    public static int run(String cmd){
        String regulation="[ \\t]+";
        final String[] split = cmd.split(regulation);

        return ffmpegRun(split);
    }

    public static native int ffmpegRun(String[] cmd);

    public static native String getFFmpegConfig();
}
