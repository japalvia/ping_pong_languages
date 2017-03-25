package main

import (
    "bytes"
    "encoding/binary"
    "log"
    "os"
)

func receiveMessage() ([]byte) {
    var msgLen uint32
    data := make([]byte, 4)
    os.Stdin.Read(data)

    buf := bytes.NewReader(data)
    binary.Read(buf, binary.LittleEndian, &msgLen)
    log.Printf("msgLen %v", msgLen)
    return data
}

func main() {
    var msg = receiveMessage()
    log.Printf("test: %v", msg)

}
