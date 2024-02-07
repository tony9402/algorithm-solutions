// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/9dfba03fe3104798a6b85336ace8335d
class InputModule {
    constructor(trim = false) { 
        this.buffer = require("fs").readFileSync("/dev/stdin").toString();
        if(trim) this.buffer = this.buffer.trim();
        this.buffer = this.buffer.split("\n").map(x => x.split(" ")); 
        this.x = 0;
        this.y = 0;
        this.pointer = 0;
    }
    _nextPointer() {
        if(this.y === this.buffer.length) return;
        if(this.x === this.buffer[this.y].length) {
            this.x = 0;
            if(++ this.y == this.buffer.length) return;
        }
        while(this.y < this.buffer.length && this.x === this.buffer[this.y].length) {
            this.x = 0;
            this.y ++;
        }
    }
    _read() {
        if(this.y === this.buffer.length) return null;
        const ret = this.buffer[this.y][this.x][this.pointer ++];
        if(this.pointer === this.buffer[this.y][this.x].length) {
            this.x ++;
            this.pointer = 0;
        }
        this._nextPointer();
        return ret;
    }
    ignore() {
        this.x ++;
        this.pointer = 0;
        this._nextPointer();
    }
    readChar() {
        return this._read();
    }
    readString() {
        if(this.y === this.buffer.length) return null;
        const ret = this.buffer[this.y][this.x];
        this.pointer = 0; 
        this.x ++;
        this._nextPointer();
        return ret;
    }
    readLine() {
        if(this.y === this.buffer.length) return null;
        const ret = this.buffer[this.y].join(' ');
        this.y ++;
        this.x = 0;
        this.pointer = 0;
        this._nextPointer();
        return ret;
    }
    readInt() {
        return Number.parseInt(this.readString());
    }
    readBigInt() {
        return BigInt(this.readString());
    }
    readFloat() {
        return Number.parseFloat(this.readString());
    }
}

class OutputModule {
    constructor() { 
        this.bufferMaxSize = 100000;
        this.buffer = new Array(this.bufferMaxSize);
        this.pointer = 0;
    }
    write(x) {
        if(this.pointer === this.bufferMaxSize) {
            this.flush();
        }
        this.buffer[this.pointer ++] = x;
    }
    flush() {
        if(this.pointer > 0) {
            process.stdout.write(this.buffer.slice(0, this.pointer).join(""));
            this.pointer = 0;
        }
    }
}
const input = new InputModule();
const output = new OutputModule();

const GCD = (a, b) => {
    if(b === 0) return a;
    return GCD(b, a % b);
};

const N = input.readInt();
const map = new Map();
let answer = 0;
for(let i = 0; i < N; ++i) {
    let x = input.readInt();
    let y = input.readInt();
    let g = GCD(Math.abs(x), Math.abs(y));
    x = x / g | 0;
    y = y / g | 0;
    
    let key = `${x}&${y}`;
    let cnt = (map.get(key) || 0) + 1;
    map.set(key, cnt);
    answer = Math.max(answer, cnt);
}
output.write(answer);
output.flush();

/* Solution Description
*/