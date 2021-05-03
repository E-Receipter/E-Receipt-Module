#include "jabcode.h"
#include "compression.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char SOURCE[] = "data.txt";
char DEST[] = "compressed.txt";

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
    FILE* source_file = fopen(SOURCE,"rb");
    long fsize = get_length(source_file);
    char* tmp_data = read_file(source_file,fsize);
    fclose(source_file);

    jab_data* data = JabData_create(tmp_data,fsize);

    jab_data* compressed_data = RG_compress(data);
    FILE* dest_file = fopen(DEST,"wb");
    fwrite(compressed_data->data,1,data->length,dest_file);
    fclose(dest_file);

    free(data);
    free(compressed_data);
    printf("compressed!\n");
    return 0;
}