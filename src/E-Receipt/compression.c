/*
Compression and Decompression functions
*/
#include "jabcode.h"
#include "compression.h"
#include "utils.h"

jab_data* RG_compress(jab_data* data){
    return JabData_create(data->data,data->length);
}

jab_data* RG_decompress(jab_data* data){
    return JabData_create(data->data,data->length);
}