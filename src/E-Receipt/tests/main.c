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
    jab_bitmap* bitmap =  RG_encode(a);
    if(!saveImage(bitmap, "test.png"))
	{
		printf("Saving png image failed\n");
        return 1;
	}

    jab_decode* decoded = RG_decode(bitmap);
    if(!decoded){
        printf("decode failed\n");
        return 1;
    }
    printf("status: %i\n",decoded->decode_status);
    printf("data:%s\n",decoded->data->data);
    free(a);
    return 0;
}