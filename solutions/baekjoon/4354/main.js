// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/55ac88fe3758467fab0f0b00e5c38978
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
const input = new InputModule(trim=true);
const output = new OutputModule();

while(true) {
    const str = input.readLine();
    if(str === '.') break;
    const N = str.length;
    const F = new Array(str.length + 1).fill(0);
    for(let i = 1, j = 0; i < N; ++i) {
        while(j > 0 && str[i] != str[j]) j = F[j - 1];
        if(str[i] == str[j]) F[i] = ++j;
    }

    const x = F[N - 1];
    if(N % (N - x) !== 0) output.write("1\n");
    else {
        output.write(N / (N - x) | 0);
        output.write("\n");
    }
}
output.flush();

/* Solution Description
*/