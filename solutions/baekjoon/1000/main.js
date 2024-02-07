// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/60894600e5de4926b0620c8cfca2a77f
class InputModule {
    constructor() { 
        this.buffer = require("fs").readFileSync("/dev/stdin").toString(); 
        this.pointer = 0;
    }
    _read() {
        if(this.pointer < this.buffer.length) {
            return this.buffer[this.pointer ++];
        }
        return null;
    }
    ignore() {
        while(this.pointer < this.buffer.length && this.buffer[this.pointer] === '\n') {
            this.pointer ++;
        }
    }
    readChar() {
        var cur = this._read();
        while(cur === ' ' || cur === '\n') cur = this._read();
        return cur;
    }
    readString() {
        var ret = "";
        var cur = this._read();
        while(cur === ' ' || cur === '\n') cur = this._read();
        if(cur === null) return null;
        while(true) {
            ret += cur;
            cur = this._read();
            if(cur === ' ' || cur === '\n' || cur === null) break;
        }
        return ret; 
    }
    readLine() {
        var ret = "";
        var cur = this._read();
        if(cur === null) return null;
        while(cur !== '\n') {
            ret += cur;
            cur = this._read();
            if(cur === null) break;
        }
        return ret;
    }
    readInt() {
        var ret = 0;
        var minus = false;
        var cur = this._read();
        while(cur === ' ' || cur === '\n') cur = this._read();
        if(cur === null) return null;
        if(cur === '-') {
            minus = true;
            cur = this._read();
        }
        while('0' <= cur && cur <= '9') {
            ret = ret * 10 + +cur;
            cur = this._read();
            if(cur === null) break;
        }
        if(minus) ret *= -1;
        return ret;
    }
    readBigInt() {
        var ret = "";
        var minus = false;
        var cur = this._read();
        while(cur === ' ' || cur === '\n') cur = this._read();
        if(cur === null) return null;
        if(cur === '-') {
            minus = true;
            cur = this._read();
        }
        while('0' <= cur && cur <= '9') {
            ret += cur;
            cur = this._read();
            if(cur === null) break;
        }
        return minus ? BigInt(`-${ret}`) : BigInt(ret);
    }
    readFloat() {
        var ret = "";
        var minus = false;
        var cur = this._read();
        while(cur === ' ' || cur === '\n') cur = this._read();
        if(cur === null) return null;
        if(cur === '-') {
            minus = true;
            cur = this._read();
        }
        while('0' <= cur && cur <= '9') {
            ret += cur;
            cur = this._read();
            if(cur === null) {
                ret = parseFloat(ret);
                return minus ? -ret : ret;
            }
        }
        if(cur === '.') {
            ret += cur;
            cur = this._read();
        }
        while('0' <= cur && cur <= '9') {
            ret += cur;
            cur = this._read();
            if(cur === null) break;
        }
        ret = parseFloat(ret);
        return minus ? -ret : ret;
    }
}

class OutputModule {
    constructor() { 
        this.bufferMaxSize = 100000;
        this.buffer = new Array(this.bufferMaxSize);
        this.pointer = 0;
    }
    write(x) {
        if(this.pointer == this.bufferMaxSize) {
            this.flush();
        }
        this.buffer[this.pointer ++] = x;
    }
    flush() {
        if(this.pointer !== 0) {
            process.stdout.write(this.buffer.join(""));
            this.pointer = 0;
        }
    }
    finally() {
        this.flush();
    }
}
const input = new InputModule();
const output = new OutputModule();

output.write(input.readBigInt() + input.readBigInt());
output.write('\n');
output.flush();

/* Solution Description
두 정수 A와 B를 입력받고 두 정수의 합의 결과를 출력하면 되는 문제

node.js에서 input 모듈과 output 모듈 적용 테스트  
버그 또는 틀린 부분, 더 좋은 모듈있으면 알려주세요.
*/