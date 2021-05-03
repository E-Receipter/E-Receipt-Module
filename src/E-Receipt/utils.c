/*
Utility functions to get/set JAB structures
*/
#include "jabcode.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

jab_data* JabData_create(char* data,long length){
    jab_data* jdata = malloc(sizeof(jab_data)+length+1);
    jdata->length = length;
    strcpy(jdata->data,data);
    return jdata;
}

jab_char* JabData_getData(jab_data *data){
    return data -> data;
}
jab_int32 JabData_getDataLength(jab_data *data){
    return data -> length;
}