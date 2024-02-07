// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/78ab0b8ade084911a645f02953da83f9

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

// KMP
const getFailure = (str) => {
    const failure = Array(str.length).fill(0);
    for(let i = 1, j = 0; i < str.length; ++i) {
        while(j > 0 && str[i] !== str[j]) j = failure[j - 1];
        if(str[i] === str[j]) failure[i] = ++j;
    }
    return failure;
};

const solution = (X, Y) => {
    const ret = Array();
    const F = getFailure(Y);
    for(let i = 0, j = 0; i < X.length; ++i) {
        while(j > 0 && X[i] !== Y[j]) j = F[j - 1];
        if(X[i] === Y[j]) {
            if(j === Y.length - 1) {
                ret.push(i - Y.length + 2);
                j = F[j];
            }
            else {
                j ++;
            }
        }
    }
    return ret;
};

const S = input.readLine(), T = input.readLine();
const answer = solution(S, T);
output.write(answer.length);
output.write("\n");
for(let i = 0; i < answer.length; ++i) {
    output.write(answer[i]);
    if(i + 1 !== answer.length) output.write(" ");
}
output.flush();

/* Solution Description
*/