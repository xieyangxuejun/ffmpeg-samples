cmake_minimum_required(VERSION 3.4.1)
project(ffmpeg)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_ANDROID_STL_TYPE ${CMAKE_ANDROID_STL_TYPE} stlport_static)

set(PATH_LIB_SO ${CMAKE_SOURCE_DIR}/src/main/jniLibs)
set(JNI_DIR src/main/cpp)

add_library( # Sets the name of the library.
        jxffmpegrun

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/cmdutils.c
        src/main/cpp/ffmpeg.c
        src/main/cpp/ffmpeg_filter.c
        src/main/cpp/ffmpeg_opt.c
        src/main/cpp/jx_ffmpeg_cmd_run.c
        )
add_library(avcodec SHARED IMPORTED)
add_library(avfilter SHARED IMPORTED)
add_library(avformat SHARED IMPORTED)
add_library(avutil SHARED IMPORTED)
add_library(swresample SHARED IMPORTED)
add_library(swscale SHARED IMPORTED)
add_library(fdk-aac SHARED IMPORTED)

set_target_properties(
        avcodec
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libavcodec.so
)

set_target_properties(
        avfilter
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libavfilter.so
)

set_target_properties(
        avformat
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libavformat.so
)

set_target_properties(
        avutil
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libavutil.so
)

set_target_properties(
        swresample
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libswresample.so
)

set_target_properties(
        swscale
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libswscale.so
)


set_target_properties(
        fdk-aac
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libfdk-aac.so
)

include_directories(
        ${JNI_DIR}/include/
        ffmpeg-3.2.5
)

find_library(log-lib log)

set(LIBS)
list(APPEND LIBS
        fdk-aac
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        log)

target_link_libraries(jxffmpegrun ${LIBS})