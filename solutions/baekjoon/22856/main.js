// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/78d15044078b4fb489011831f5b31f75
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

const N = input.readInt();
const nextRight = new Array(N + 1);
for(let i = 1; i <= N; ++i) {
    const a = input.readInt();
    const b = input.readInt();
    const c = input.readInt();
    nextRight[a] = c;
}

var ans = 2 * (N - 1);
for(let cur = 1; nextRight[cur] !== -1; cur = nextRight[cur]) {
    ans --;
}
output.write(ans);
output.flush();

/* Solution Description
잘 생각해보면 가장 루트에서 시작하여 가장 오른쪽으로 가는 경로를 제외하고는 2번 이동한다.  
직접 유사 중위 순회를 구현해도 되지만, 잘 관찰을 하면 답은 2 * (N - 1) - (루트에서 시작해서 가장 오른쪽 노드까지 이동하는 횟수)가 되는 것을 알 수 있다.
*/