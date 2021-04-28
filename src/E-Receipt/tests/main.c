#include "jabcode.h"
#include "encryption.h"
#include "compression.h"
#include "jab_enc.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    jab_data* a = (jab_data*) malloc(sizeof(jab_data) + 10);
    a->length = 10;
    strcpy(a->data,"qwertyuio");
    RG_compress(a);
    free(a);
    printf("hello world\n");
    return 0;
}