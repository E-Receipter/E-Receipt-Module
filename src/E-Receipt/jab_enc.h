/*
@brief JABCode decoded output
*/
typedef struct {
    jab_int32 decode_status;
    jab_data* data;
} jab_decode;

extern jab_decode* RG_decode(jab_bitmap *bitmap);
// extern jab_bitmap* encode(jab_data* data);