#include "jabcode.h"
#include "encryption.h"
#include "compression.h"
#include "jab_enc.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char SOURCE[] = "jab.png";
char DEST[] = "jab_decode.txt";

long get_length(FILE* file){
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    return fsize;
}

char* read_file(FILE* file,long fsize){
    char* data = malloc(fsize)+1;
    fread(data, 1, fsize, file);
    return data;
}
int main(){
    jab_bitmap* bitmap = readImage(SOURCE);
    jab_decode* decoded_data= RG_decode(bitmap);
    jab_data* data = decoded_data->data;
    FILE* dest_file = fopen(DEST,"wb");
    fwrite(data->data,1,data->length,dest_file);
    fclose(dest_file);
    free(bitmap);
    free(data);
    printf("JAB decrypted!\n");
    return 0;
}