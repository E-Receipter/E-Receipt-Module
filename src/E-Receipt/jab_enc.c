/*
JABCode encoding and decoding functions
*/
#include <stdlib.h>
#include "jabcode.h"
#include "jab_enc.h"

jab_int32 JabDecode_getStatus(jab_decode* decoded_data){
    return decoded_data -> decode_status;
}

jab_data* JabDecode_getData(jab_decode* decoded_data) {
    return decoded_data -> data;
}

jab_bitmap* JabBitmap_create(int width,int height){
    int pixel_length = width * height * BITMAP_CHANNEL_COUNT;

    jab_bitmap* bitmap = (jab_bitmap*)malloc(sizeof(jab_bitmap) + pixel_length);
    bitmap -> width = width;
    bitmap -> height = height;
    bitmap -> bits_per_pixel = BITMAP_BITS_PER_PIXEL;
    bitmap -> bits_per_channel = BITMAP_BITS_PER_CHANNEL;
    bitmap -> channel_count = BITMAP_CHANNEL_COUNT;
    return bitmap;
}

jab_byte* JabBitmap_getPixelArray(jab_bitmap* bitmap){
    return bitmap -> pixel;
}

jab_int64 JabBitmap_getPixelWidth(jab_bitmap* bitmap) {
    return bitmap->width;
}

jab_int64 JabBitmap_getPixelLength(jab_bitmap* bitmap) {
    return bitmap->width * bitmap->height;
}

/**
 * @brief JABCode Bitmap decoding function
 * @param bitmap the bitmap of the image to be processed
 * @return the decoded data and status
**/
jab_decode* RG_decode(jab_bitmap *bitmap){
    jab_int32 decode_status;
	jab_decoded_symbol symbols[MAX_SYMBOL_NUMBER];
    jab_data* data;
    for(int i=0;i<6;i++){
        data = decodeJABCodeEx(bitmap, NORMAL_DECODE, &decode_status, symbols, MAX_SYMBOL_NUMBER);
        if(data->length>0)
            break;
    }
    jab_decode* decoded = (jab_decode*) malloc(sizeof(jab_decode));
    decoded -> decode_status = decode_status;
    decoded -> data = data;
    return decoded;
}

jab_bitmap* RG_encode(jab_data* data){
    jab_int32 color_number = DEFAULT_COLOR_NUMBER;
    jab_int32 symbol_number = DEFAULT_SYMBOL_NUMBER;
    jab_int32 module_size = DEFAULT_MODULE_SIZE;
    jab_int32 master_symbol_width = 0;
    jab_int32 master_symbol_height = 0;
    jab_int32* symbol_ecc_levels = 0;
    jab_vector2d* symbol_versions = 0;
    jab_int32* symbol_positions = 0;
    jab_encode* enc = createEncode(color_number,symbol_number);
    if(enc == NULL)
    {
        return NULL;
    }
    if(module_size > 0)
    {
		enc->module_size = module_size;
    }
    if(master_symbol_width > 0)
    {
		enc->master_symbol_width = master_symbol_width;
    }
    if(master_symbol_height > 0)
    {
		enc->master_symbol_height = master_symbol_height;
    }
	for(jab_int32 loop=0; loop<symbol_number; loop++)
	{
		if(symbol_ecc_levels)
			enc->symbol_ecc_levels[loop] = symbol_ecc_levels[loop];
		if(symbol_versions)
			enc->symbol_versions[loop] = symbol_versions[loop];
		if(symbol_positions)
			enc->symbol_positions[loop] = symbol_positions[loop];
	}
    if(generateJABCode(enc, data) != 0)
	{
		return NULL;
	}
    return enc->bitmap;
}