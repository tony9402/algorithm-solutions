// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/d7babb083f7b4498aa792e4530ef71f5
class InputModule {
    constructor() { 
        this.buffer = require("fs").readFileSync("/dev/stdin").toString().trim().split("\n").map(x => x.split(" ")); 
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
        if(this.pointer === this.buffer[this.y][this.x].length) {
            this.x ++;
            this.pointer = 0;
        }
        while(this.y < this.buffer.length && this.x === this.buffer[this.y].length) {
            this.x = 0;
            this.y ++;
        }
    }
    _read() {
        if(this.y === this.buffer.length) return null;
        const ret = this.buffer[this.y][this.x][this.pointer ++];
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
        const ret = this.buffer[this.y][this.x].slice(this.pointer);
        this.pointer = 0; 
        this.x ++;
        this._nextPointer();
        return ret;
    }
    readLine() {
        const ret = this.buffer[this.y].slice(this.x).join(' ');
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