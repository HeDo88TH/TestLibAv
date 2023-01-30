
cmake_minimum_required(VERSION 3.18)

project(TestLibAv)

set(CMAKE_CXX_STANDARD 11)
set(DOWNLOADS_DIR "${CMAKE_BINARY_DIR}/downloads")


add_executable(TestLibAv main.cpp)

if (WIN32)
    function (download_dependency target_zip url)
        if (NOT EXISTS "${DOWNLOADS_DIR}/${target_zip}")
            message("Downloading ${target_zip}...")
            file(DOWNLOAD "${url}" "${DOWNLOADS_DIR}/${target_zip}" STATUS result)
            message("Download result: ${result}")
        endif()
    endfunction()

    function(extract_dependency target_zip path_check dest_dir )
        if (NOT EXISTS "${DOWNLOADS_DIR}/${path_check}")
            message("Extracting ${dest_dir}...")
            execute_process(COMMAND powershell Expand-Archive "\"${DOWNLOADS_DIR}/${target_zip}\"" "\"${DOWNLOADS_DIR}/${dest_dir}\" -Force")
        endif()
    endfunction()

    download_dependency("ffmpeg-libs.zip" "https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/ffmpeg-n5.1-latest-win64-gpl-shared-5.1.zip")
    extract_dependency("ffmpeg-libs.zip" "ffmpeg/include" "ffmpeg")

    set(DL_DIR "ffmpeg-n5.1-latest-win64-gpl-shared-5.1")

    set(AVCODEC_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/avcodec.lib")
    set(AVUTIL_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/avutil.lib")
    set(AVDEVICE_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/avdevice.lib")
    set(AVFILTER_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/avfilter.lib")
    set(AVFORMAT_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/avformat.lib")
    set(POSTPROC_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/postproc.lib")
    set(SWRESAMPLE_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/swresample.lib")
    set(SWSCALE_LIBRARY "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/lib/swscale.lib")

    set(AV_INCLUDE_DIR "${DOWNLOADS_DIR}/ffmpeg/${DL_DIR}/include")
    include_directories(${AV_INCLUDE_DIR})

    message("AVCODEC_LIBRARY: ${AVCODEC_LIBRARY}")
    message("AVUTIL_LIBRARY: ${AVUTIL_LIBRARY}")
    message("AVDEVICE_LIBRARY: ${AVDEVICE_LIBRARY}")
    message("AVFILTER_LIBRARY: ${AVFILTER_LIBRARY}")
    message("AVFORMAT_LIBRARY: ${AVFORMAT_LIBRARY}")
    message("POSTPROC_LIBRARY: ${POSTPROC_LIBRARY}")
    message("SWRESAMPLE_LIBRARY: ${SWRESAMPLE_LIBRARY}")
    message("SWSCALE_LIBRARY: ${SWSCALE_LIBRARY}")

    add_library(avcodec STATIC IMPORTED)
    set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${AVCODEC_LIBRARY})

    add_library(avutil STATIC IMPORTED)
    set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${AVUTIL_LIBRARY})

    add_library(avdevice STATIC IMPORTED)
    set_target_properties(avdevice PROPERTIES IMPORTED_LOCATION ${AVDEVICE_LIBRARY})

    add_library(avfilter STATIC IMPORTED)
    set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${AVFILTER_LIBRARY})

    add_library(avformat STATIC IMPORTED)
    set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${AVFORMAT_LIBRARY})

    add_library(postproc STATIC IMPORTED)
    set_target_properties(postproc PROPERTIES IMPORTED_LOCATION ${POSTPROC_LIBRARY})

    add_library(swresample STATIC IMPORTED)
    set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${SWRESAMPLE_LIBRARY})

    add_library(swscale STATIC IMPORTED)
    set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${SWSCALE_LIBRARY})

    target_link_libraries(${PROJECT_NAME}
        avcodec
        avutil
        avdevice
        avfilter
        avformat
        postproc
        swresample
        swscale
    )

else()
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil
    )

    target_link_libraries(${PROJECT_NAME}
        PkgConfig::LIBAV
    )

endif()




