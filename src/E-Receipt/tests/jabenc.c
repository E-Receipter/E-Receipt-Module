#include "jabcode.h"
#include "encryption.h"
#include "compression.h"
#include "jab_enc.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char SOURCE[] = "encrypt.txt";
char DEST[] = "jab.png";

long get_length(FILE* file){
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    return fsize;
}

char* read_file(FILE* file,long fsize){
    char* data = malloc(fsize+1);
    fread(data, 1, fsize, file);
    return data;
}
int main(){
    FILE* file = fopen(SOURCE,"rb");
    long fsize = get_length(file);
    char* tmp_data = read_file(file,fsize);
    jab_data* data = JabData_create(tmp_data,fsize);
    jab_bitmap* bitmap =  RG_encode(data);
    if(!saveImage(bitmap, DEST))
	{
		printf("Saving png image failed\n");
        return 1;
	}
    free(data);
    printf("JAB encrypted!\n");
    return 0;
}