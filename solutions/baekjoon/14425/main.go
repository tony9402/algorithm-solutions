// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/92e0fc6698e6402aaa544f8de5eaf874
package main

import (
	"bufio"
	"os"
	"strings"
)

type FastInputDto struct {
	bufferMaxSize int
	bufferPointer int
	buffer []byte
	eof bool
	reader *bufio.Reader
}

func FastInput() *FastInputDto {
	return &FastInputDto{
		bufferMaxSize: 1 << 22,
		bufferPointer: 1 << 22,
		buffer: make([]byte, 1 << 22),
		eof: false,
		reader: bufio.NewReaderSize(os.Stdin, 1 << 22),
	}
}

func (fi *FastInputDto) _read() byte {
	if fi.eof {
		return 0
	}
	if fi.bufferPointer == fi.bufferMaxSize {
		fi.reader.Read(fi.buffer)
		fi.bufferPointer = 0
	}
	ret := fi.buffer[fi.bufferPointer]
	fi.bufferPointer ++
	if ret == 0 {
		fi.eof = true
	}
	return ret
}

func (fi *FastInputDto) readInt() int {
	ret := 0
	minus := false
	cur := fi._read()

	for cur == 10 || cur == 32 {
		cur = fi._read()
	}
	if cur == 45 {
		minus = true 
		cur = fi._read()
	}
	for 48 <= cur && cur <= 57 {
		ret = ret * 10 + int(cur) - 48
		cur = fi._read()
	}
	if minus {
		ret *= -1
	}
	return ret
}

func (fi *FastInputDto) _readStringOrLine(line bool) string {
	var ret strings.Builder
	cur := fi._read()

	for cur == 10 || cur == 32 {
		if line && cur == 32 {
			break
		}
		cur = fi._read()
	}
	for {
		if !line && cur == 32 { break }
		if cur == 10 || cur == 0 { break }
		ret.WriteByte(cur)
		cur = fi._read()
	}
	return ret.String()
}

func (fi *FastInputDto) readString() string {
	return fi._readStringOrLine(false)
}

func (fi *FastInputDto) readLine() string {
	return fi._readStringOrLine(true)
}

type FastOutputDto struct {
	bufferMaxSize int
	bufferPointer int
	buffer []byte
	writer *bufio.Writer
}

func FastOutput() *FastOutputDto {
	return &FastOutputDto {
		bufferMaxSize: 1 << 22,
		bufferPointer: 1 << 22,
		buffer: make([]byte, 1 << 22),
		writer: bufio.NewWriter(os.Stdout),
	}
}

func (fo *FastOutputDto) flush() { fo.writer.Flush() }
func (fo *FastOutputDto) _writeInt(x int) {
	ret := []byte{}
	var minus = false

	if x < 0 {
		x *= -1
		minus = true
	}
	for x > 0 {
		ret = append(ret, byte(x % 10 + 48))
		x /= 10
	}
	if minus {
		ret = append(ret, '-')
	}

	left := 0
    right := len(ret) - 1
    for left < right {
        ret[left], ret[right] = ret[right], ret[left]
        left++
        right--
    }

	if len(ret) == 0 {
		ret = append(ret, '0')
	}

	fo.writer.Write(ret)
}
func (fo *FastOutputDto) _writeByte(x byte) {
	fo.writer.WriteByte(x)
}
func (fo *FastOutputDto) _writeString(x string) {
	fo.writer.WriteString(x)
}
func (fo *FastOutputDto) write(x interface{}, nxt string) {
	switch v := x.(type) {
	case int:
		fo._writeInt(v) 
	case byte:
		fo._writeByte(v)
	case string:
		fo._writeString(v)
	}
	if nxt != "" {
		fo._writeString(nxt)
	}
}

func main() {
	input := FastInput()
	output := FastOutput()
	defer output.flush()
	N := input.readInt()
	M := input.readInt()

	mp := make(map[string]bool)
	for i := 1; i <= N; i++ {
		x := input.readString()
		mp[x] = true
	}
	answer := 0
	for i := 1; i <= M; i++ {
		x := input.readString()
		if mp[x] { answer ++ }
	}
	output.write(answer, "")
}

/* Solution Description
map이나 set(S는 중복 원소가 없기 때문에 가능) 자료구조를 이용해서 문자열이 존재하는 개수를 세면 된다.  
시간복잡도: O(MlogN)
*/