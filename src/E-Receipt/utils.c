/*
Utility functions to get/set JAB structures
*/
#include "jabcode.h"
#include "utils.h"
#include <stdlib.h>

jab_char* JabData_getData(jab_data *data){
    return data -> data;
}
jab_int32 JabData_getDataLength(jab_data *data){
    return data -> length;
}