package main

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"log"
	"os"
)

func receiveMessage() ([]byte) {
	var msgLen uint32
	data := make([]byte, 4)
	os.Stdin.Read(data)

	buf := bytes.NewReader(data)
	binary.Read(buf, binary.LittleEndian, &msgLen)
	log.Printf("msgLen: %v", msgLen)

	data = make([]byte, msgLen)
	os.Stdin.Read(data)
	return data
}

func sendMessage() {
    r := make([]string, 1)
    r[0] = "pong"

    b, err := json.Marshal(r)
    log.Printf("json encode err: %v, b: %v", err, string(b))

    //buf := make([]byte, 4)
    buf := new(bytes.Buffer)
    msgLen := len(b)
    binary.Write(buf, binary.LittleEndian, msgLen)
    log.Printf("sendMessage len: %v", msgLen)
    os.Stdout.Write(buf.Bytes())
    os.Stdout.Write(b)
}

func main() {
	var msg = receiveMessage()
	log.Printf("test: %v", string(msg[:]))

	var f interface{}
	err := json.Unmarshal(msg, &f)
	if err != nil {
		log.Println("Failed to decode json")
	}
	array := f.([]interface{})
	log.Printf("array[0]: %v", array[0])
	if array[0] == "ping" {
		sendMessage()
	}
}
