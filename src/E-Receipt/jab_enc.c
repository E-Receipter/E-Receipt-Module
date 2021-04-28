/*
JABCode encoding and decoding functions
*/
#include <stdlib.h>
#include "jabcode.h"
#include "jab_enc.h"

/**
 * @brief JABCode Bitmap decoding function
 * @param bitmap the bitmap of the image to be processed
 * @return the decoded data and status
**/
jab_decode* RG_decode(jab_bitmap *bitmap){
    jab_int32 decode_status;
	jab_decoded_symbol symbols[MAX_SYMBOL_NUMBER];
    jab_data* data = decodeJABCodeEx(bitmap, NORMAL_DECODE, &decode_status, symbols, MAX_SYMBOL_NUMBER);
    jab_decode* decoded = (jab_decode*) malloc(sizeof(jab_decode));
    decoded -> decode_status = decode_status;
    decoded -> data = data;
    return decoded;
}

// jab_bitmap* RG_encode(jab_data* data){

// }