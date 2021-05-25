const WASM_MODULE = 'build/jabcode.wasm';
const imgSrc = "test/test.png";
const canvas = document.getElementById("canvas")
const ctx = canvas.getContext("2d");
const image = new Image();
image.onload = loadImage;
image.src = imgSrc;

function loadImage() {
    scaling = 0.5;
    canvas.width = this.naturalWidth * scaling;
    canvas.height = this.naturalHeight * scaling;
    ctx.drawImage(this, 0, 0, canvas.width, canvas.height);
}

function getImage() {
    return ctx.getImageData(0, 0, canvas.width, canvas.height);
}

// --------------- TESTS -------------------------
// Test - 1 -> direct decode
async function decode() {
    imgData = getImage()
    // bitmap_ptr = loadBitMap(imgData)
    //return Module._decode(bitmap_ptr)
    decoder = new JABCodeDecoder(window.module, canvas.width, canvas.height)
    value = decoder.decode(imgData)
    decoder.clean()
    return await new TextDecoder('utf-8').decode(value)
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