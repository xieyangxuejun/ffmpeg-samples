cmake_minimum_required(VERSION 3.4.1)
project(ffmpeg)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_ANDROID_STL_TYPE ${CMAKE_ANDROID_STL_TYPE} stlport_static)

set(PATH_LIB_SO ${CMAKE_SOURCE_DIR}/src/main/jniLibs)
set(JNI_DIR src/main/cpp)

set(SRC_LIST)
aux_source_directory(${JNI_DIR} JNI_SRC_LIST)
aux_source_directory(${JNI_DIR}/lame LAME_SRC_LIST)
aux_source_directory(${JNI_DIR}/jni JNI_SRC_LIST)

list(APPEND SRC_LIST
        ${JNI_SRC_LIST}
        ${LAME_SRC_LIST}
        ${JNI_SRC_LIST}
)

add_library(ffmpegcore SHARED ${SRC_LIST})
# mp3lame single lib
add_library(mp3core SHARED
        ${JNI_DIR}/jni/jni_mp3_encode.cpp
        ${JNI_DIR}/lame/mp3_encoder.cpp)

add_library(avcodec SHARED IMPORTED)
add_library(avfilter SHARED IMPORTED)
add_library(avformat SHARED IMPORTED)
add_library(avutil SHARED IMPORTED)
add_library(swresample SHARED IMPORTED)
add_library(swscale SHARED IMPORTED)
add_library(fdk-aac SHARED IMPORTED)

add_library(mp3lame SHARED IMPORTED)
set_target_properties(
        mp3lame
        PROPERTIES IMPORTED_LOCATION
        ${PATH_LIB_SO}/${ANDROID_ABI}/libmp3lame.so
)

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

set(LIBS)
list(APPEND LIBS
        fdk-aac
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        mp3lame
        jnigraphics
        log)

set(MP3_LIBS)
list(APPEND MP3_LIBS
        mp3lame
        jnigraphics
        log)

target_link_libraries(ffmpegcore ${LIBS})
target_link_libraries(mp3core ${MP3_LIBS})