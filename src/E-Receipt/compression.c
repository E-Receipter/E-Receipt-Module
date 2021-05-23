/*
Compression and Decompression functions
*/
#include "jabcode.h"
#include "compression.h"
#include "utils.h"
#include "zlib.h"
#include<stdlib.h>

jab_data* RG_compress(jab_data* data){
    jab_data* compressed_data = JabData_create(data->data,data->length);
    uLong len = compressed_data->length+1;
    int err = compress(
        (Bytef*)compressed_data->data,&len,
        (Bytef*)data->data,data->length
        );
    compressed_data->length = len;
    return compressed_data;
}

jab_data* RG_decompress(jab_data* data){
    jab_data* decompressed_data = (jab_data*) malloc(sizeof(jab_data)+data->length*2);
    uLong len = data->length*2;
    int err = uncompress(
        (Bytef*)decompressed_data->data,&len,
        (Bytef*)data->data,data->length
        );
    decompressed_data->length = len;
    return decompressed_data;
}