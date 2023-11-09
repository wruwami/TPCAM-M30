#include "ImageConverter.h"

extern "C" {
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
}
#include "thermal_printer.h"

ImageConverter::ImageConverter(QImage image)
{
    m_image = image;
}

void ImageConverter::Convert()
{
    QImage img = m_image;//your image in RGB32

    //allocate output buffer.  use av_malloc to align memory.  YUV420P
    //needs 1.5 times the number of pixels (Cb and Cr only use 0.25
    //bytes per pixel on average)
    unsigned char* out_buffer = (unsigned char*)av_malloc(1712 * 984 * 1.5/*img.height() * img.width() * 1.5)*/);

    //allocate ffmpeg frame structures
    AVFrame* inpic = av_frame_alloc();
    AVFrame* outpic = av_frame_alloc();

    //avpicture_fill sets all of the data pointers in the AVFrame structures
    //to the right places in the data buffers.  It does not copy the data so
    //the QImage and out_buffer still need to live after calling these.
    avpicture_fill((AVPicture*)inpic,
                   img.bits(),
                   AV_PIX_FMT_ARGB,
                   img.width(),
                   img.height());
    avpicture_fill((AVPicture*)outpic,
                   out_buffer,
                   AV_PIX_FMT_YUV420P,
                   1712,
                   984);

    //create the conversion context.  you only need to do this once if
    //you are going to do the same conversion multiple times.
    SwsContext* ctx = sws_getContext(img.width(),
                                     img.height(),
                                     AV_PIX_FMT_ARGB,
                                     1712,
                                     984,
                                     AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC,
                                     NULL, NULL, NULL);

    //perform the conversion
    sws_scale(ctx,
              inpic->data,
              inpic->linesize,
              0,
              img.height(),
              outpic->data,
              outpic->linesize);

    memcpy(g_print_img_body_buff_file_management, out_buffer, 1712 * 984/*img.height() * img.width() * 1.5*/);

    //free memory
    av_free(inpic);
    av_free(outpic);

    //...

    //free output buffer when done with it
    av_free(out_buffer);
}
