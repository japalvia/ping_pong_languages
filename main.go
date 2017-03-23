package main

import (
    "bytes"
    "encoding/binary"
    "fmt"
    "os"
)

func debug(msg string) {
    fmt.Println(msg)
}

func receiveMessage() ([]byte) {
    var msgLen uint32
    data := make([]byte, 4)
    os.Stdin.Read(data)

    buf := bytes.NewReader(data)
    binary.Read(buf, binary.LittleEndian, &msgLen)
    fmt.Println("msgLen:", msgLen)
    return data
}

func main() {
    var msg = receiveMessage()
    debug(string(msg[:]))

}
