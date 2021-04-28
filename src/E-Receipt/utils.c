/*
Utility functions to get/set JAB structures
*/
#include "jabcode.h"
#include "utils.h"
#include <stdlib.h>

jab_bitmap *createJabBitmap(
    int width,int height
    ){
        int bits_per_pixel = BITMAP_BITS_PER_PIXEL;
        int bits_per_channel = BITMAP_BITS_PER_CHANNEL;
        int channel_count = BITMAP_CHANNEL_COUNT;
        int pixel_length = width * height * BITMAP_CHANNEL_COUNT;

        jab_bitmap* bitmap = (jab_bitmap*)malloc(sizeof(jab_bitmap) + pixel_length);
        bitmap -> width = width;
        bitmap -> height = height;
        bitmap -> bits_per_pixel = bits_per_pixel;
        bitmap -> bits_per_channel = bits_per_channel;
        bitmap -> channel_count = channel_count;
        return bitmap;
    }

jab_byte* getPixelArray(jab_bitmap* bitmap){
    return bitmap -> pixel;
}

jab_int64 getPixelWidth(jab_bitmap* bitmap) {
    return bitmap->width;
}

jab_int64 getPixelLength(jab_bitmap* bitmap) {
    return bitmap->width * bitmap->height;
}

/*
@brief select only one channel and set all but alpha to 0
*/
jab_byte* getTrimmed(jab_bitmap *bitmap,jab_int32 channel){
    jab_int64 length = bitmap->height*bitmap->width*BITMAP_CHANNEL_COUNT;
    jab_byte* pixels = (jab_byte*) malloc(length*sizeof(jab_byte));
    for(jab_int64 i=0;i<length;i++){
        if((i + channel)%4 == 0)
            pixels[i] = bitmap->pixel[i];
        else
            pixels[i] = 0;
        if((i+1)%4 == 0){
            pixels[i] = 255;
        }
    }
    return pixels;
}

jab_char* getData(jab_data *data){
    return data -> data;
}
jab_int32 getDataLength(jab_data *data){
    return data -> length;
}