/*
Compression and Decompression functions
*/
#include "jabcode.h"
#include "compression.h"
#include "utils.h"
#include<stdlib.h>

jab_data* RG_compress(jab_data* data){
    jab_data* compressed_data = JabData_create(data->data,data->length);
    return compressed_data;
}

jab_data* RG_decompress(jab_data* data){
    jab_data* decompressed_data = JabData_create(data->data,data->length);
    return decompressed_data;
}