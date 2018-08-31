package com.foretree.samples.ffmpeg

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import com.foretree.ffmpeg.FFmpegCmd
import com.foretree.ffmpeg.Mp3Encoder
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        tv.text = FFmpegCmd.getFFmpegConfig()

        Mp3Encoder().run {
            init("", 2, 128, 4100, "")
        }
    }

    /**
     * 从视频中提取视频.不要音频
     */
    fun getVideoFrom(inPath: String, outPath: String) : String{
        //ffmpeg -i test.mp4 -an -y -vcodec copy out.mp4
        return String.format("ffmpeg -i %s -an -y -vcodec copy %s", inPath, outPath).let {
            FFmpegCmd.run(it)
            outPath
        }
    }

    /**
     * 合并视频和音频
     * 若音频比视频长，画面停留在最后一帧，继续播放声音。
     */
    fun mergeVideo(paths: Array<String>, outPath: String) : String{
        return StringBuffer().apply {
            for (path in paths) {
                this.append("-i")
                this.append(path)
            }
            this.append("-c:a")
            this.append("copy")
            this.append("-c:v")
            this.append("copy")

        }.toString().let {
            FFmpegCmd.run(it)
            outPath
        }
    }
}