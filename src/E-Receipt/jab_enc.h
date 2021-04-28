/**
 * @brief JABCode decoded output
**/
typedef struct {
    jab_int32 decode_status;
    jab_data* data;
} jab_decode;

extern jab_int32 JabDecode_getStatus(jab_decode*);

extern jab_data* JabDecode_getData(jab_decode*);

extern jab_bitmap* JabBitmap_create(int,int);

extern jab_byte* JabBitmap_getPixelArray(jab_bitmap*);

extern jab_int64 JabBitmap_getPixelWidth(jab_bitmap*);

extern jab_int64 JabBitmap_getPixelLength(jab_bitmap*);

extern jab_decode* RG_decode(jab_bitmap*);

extern jab_bitmap* RG_encode(jab_data*);