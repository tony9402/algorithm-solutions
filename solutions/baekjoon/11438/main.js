// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/829b139a1ce94e7ab92456a2a6dd0607
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

const N = input.readInt();
const Graph = new Array(N + 1);
for(let i = 0; i <= N; ++i) Graph[i] = new Array();
for(let i = 1; i < N; ++i) {
    let u = input.readInt();
    let v = input.readInt();
    Graph[u].push(v);
    Graph[v].push(u);
}

const dep = new Array(N + 1).fill(0);
const par = new Array(17);
for(let i = 0; i < 17; ++i) {
    par[i] = new Array(N + 1).fill(0);
}

const dfs = (cur = 1, prev = 0) => {
    dep[cur] = dep[prev] + 1;
    par[0][cur] = prev;
    for(let nxt of Graph[cur]) {
        if(nxt === prev) continue;
        dfs(nxt, cur);
    }
};
dfs();

for(let i = 1; i < 17; ++i){
    for(let j = 1; j <= N; ++j) {
        par[i][j] = par[i - 1][par[i - 1][j]];
    }
}

const getLCA = (u, v) => {
    if(dep[u] > dep[v]) [u, v] = [v, u];
    for(let i = 16; i >= 0; --i) {
        if(dep[u] <= dep[par[i][v]]) v = par[i][v];
    }
    if(u == v) return u;
    let ret = u;
    for(let i = 16; i >= 0; --i) {
        if(par[i][u] !== par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
        ret = par[i][u];
    }
    return ret;
};

const Q = input.readInt();
for(let i = 0; i < Q; ++i) {
    let u = input.readInt();
    let v = input.readInt();
    output.write(getLCA(u, v));
    output.write("\n");
}
output.flush();

/* Solution Description
*/