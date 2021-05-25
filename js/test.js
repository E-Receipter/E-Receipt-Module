const WASM_MODULE = 'build/jabcode.wasm';
const canvas = document.getElementById("canvas")
const ctx = canvas.getContext("2d");

function loadImage(url){
    return new Promise((resolve)=>{
        let image = new Image();
        image.onload = ()=> {resolve(image)};
        image.src = url;
    })
}

async function getImage(url) {
    const image = await loadImage(url);
    scaling = 0.5;
    canvas.width = image.naturalWidth * scaling;
    canvas.height = image.naturalHeight * scaling;
    ctx.drawImage(image, 0, 0, canvas.width, canvas.height);
    return ctx.getImageData(0, 0, canvas.width, canvas.height);
}

function protoload(url){
    return new Promise((resolve)=>{
        protobuf.load(url,(err,root)=>{
            resolve(root);
        })
    })
}

// --------------- TESTS -------------------------
// Test - 1 -> direct decode
async function decode() {
    imgData = await getImage("test/test.png");
    // bitmap_ptr = loadBitMap(imgData)
    //return Module._decode(bitmap_ptr)
    decoder = new JABCodeDecoder(window.module, canvas.width, canvas.height)
    value = decoder.decode(imgData)
    decoder.clean()
    return await new TextDecoder('utf-8').decode(value)
}

async function protobuf_test() {
    out = {}
    imgData = await getImage("test/enc.png");
    decoder = new JABCodeDecoder(window.module, canvas.width, canvas.height)
    value = decoder.decode(imgData)
    proto = await protoload('main.proto');
    ebillType = proto.lookupType("EncryptedBill");
    ebill = ebillType.toObject(ebillType.decode(value));
    out.shopId = ebill.shopId;
    billType = proto.lookupType("Bill");
    bill = billType.toObject(billType.decode(ebill.encryptedBill));
    out = {
        ...out,...bill
    }
    decoder.clean()
    return out;
}

async function test() {
    let a = 10;
    let b = 20;
    ans = window.module._test(a,b);
    return `${a}+${b}=${ans}`;
}

// ------------------END TESTS --------------------
const tests = [
    decode,
    test,
    protobuf_test,
]

function getMarkerId(name){
    return name;
}

function getResultId(name){
    return name+'-result';
}

function createTestList(){
    parent = document.getElementById('test-list');
    for(let func of tests){
        div = document.createElement('div');
        title = document.createElement('span');
        title.innerText = func.name;
        marker = document.createElement('span');
        marker.id = getMarkerId(func.name);
        result = document.createElement('span');
        result.id = getResultId(func.name);
        div.appendChild(title);
        div.appendChild(marker);
        div.appendChild(result);
        parent.appendChild(div);
    }
}

async function loadModule(){
    window.module = await self.Module(
        {
            wasm: fetch(WASM_MODULE),
        }
    )
}

async function testRunner(){
    await loadModule();
    for(let func of tests){
        let resultValue = '';
        marker = document.getElementById(getMarkerId(func.name));
        result = document.getElementById(getResultId(func.name));
        try {
            resultValue = await func();
        } catch (error) {
            marker.innerText = '❌';
            console.log(func.name);
            console.log(error);
            continue;
        }
        marker.innerText = '✅';
        result.innerText = JSON.stringify(resultValue);
    }
}
createTestList();
document.getElementById('start-test').onclick = testRunner;