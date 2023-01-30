
#include <iostream>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
}

int main(int argc, char *argv[]) {

    AVFormatContext *fmt_ctx = NULL;
    const AVDictionaryEntry *tag = NULL;
    int ret;

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <input_file>"  << std::endl <<
               "example program to demonstrate the use of the libavformat metadata API." << std::endl;
        return 1;
    }

    if ((ret = avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)))
        return ret;

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return ret;
    }

    /*while ((tag = av_dict_iterate(fmt_ctx->metadata, tag)))
        std::cout << tag->key << "=" << tag->value << std::endl;
*/
    avformat_close_input(&fmt_ctx);

    return 0;
}