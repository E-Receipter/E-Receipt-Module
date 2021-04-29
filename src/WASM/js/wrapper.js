class JABCodeDecoder{
    constructor(module,width,height){
        this.module = module
        this.initBitmap(width,height)
    }
    initBitmap(width,height){
        if(this.bitmapPtr){
            this.clean()
        }
        this.width = width
        this.height = height
        this.byteLength = this.width*this.height*4
        this.bitmapPtr = this.module._JabBitmap_create(this.width,this.height)
        this.pixelPtr = this.module._JabBitmap_getPixelArray(this.bitmapPtr)
        this.pixels = new Uint8Array(this.module.HEAPU8.buffer,this.pixelPtr,this.byteLength)
    }
    getImage(){
        return new ImageData(new Uint8ClampedArray(this.pixels),this.width);
    }
    setImage(value){
        if (value instanceof Uint8Array)
            this.pixels.set(value)
        else if(value instanceof ImageData)
            this.pixels.set(new Uint8Array(value.data.buffer))
        else 
            this.pixels.set(new Uint8Array(value.buffer))
    }
    decode(value){
        this.setImage(value)
        this.decodePtr = this.module._RG_decode(this.bitmapPtr)
        console.log(this.module._JabDecode_getStatus(this.decodePtr))
        this.dataPtr = this.module._JabDecode_getData(this.decodePtr)
        this.dataArrPtr = this.module._JabData_getData(this.dataPtr)
        this.dataLength = this.module._JabData_getDataLength(this.dataPtr)
        this.value = new Uint8Array(this.module.HEAPU8.buffer,this.dataArrPtr,this.dataLength)
        return this.value
    }
    clean(){
        this.module._free(this.bitmapPtr)
        if('dataPtr' in this)
        this.module._free(this.dataPtr);
    }
}