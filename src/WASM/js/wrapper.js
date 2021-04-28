class JABCodeDecoder{
    constructor(module,width,height){
        this.module = module
        this.setBitmap(width,height)
    }
    setBitmap(width,height){
        if(this.bitmapPtr){
            this.clean()
        }
        this.width = width
        this.height = height
        this.byteLength = this.width*this.height*4
        this.bitmapPtr = this.module._createJabBitmap(this.width,this.height)
        this.pixelPtr = this.module._getPixelArray(this.bitmapPtr)
        this.pixels = new Uint8Array(this.module.HEAPU8.buffer,this.pixelPtr,this.byteLength)
    }
    get image(){
        return new ImageData(new Uint8ClampedArray(this.pixels),this.width);
    }
    set image(value){
        if (value instanceof Uint8Array)
            this.pixels.set(value)
        else if(value instanceof ImageData)
            this.pixels.set(new Uint8Array(value.data.buffer))
        else 
            this.pixels.set(new Uint8Array(value.buffer))
    }
    decode(){
        this.dataPtr = Module._decode(this.bitmapPtr)
        this.dataArrPtr = this.module._getData(this.dataPtr)
        this.dataLength = this.module._getDataLength(this.dataPtr)
        this.value = new Uint8Array(this.module.HEAPU8.buffer,this.dataArrPtr,this.dataLength)
        return this.value
    }
    clean(){
        this.module._free(this.bitmapPtr)
        if('dataPtr' in this)
        this.module._free(this.dataPtr);
    }
}