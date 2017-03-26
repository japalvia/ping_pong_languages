package main

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"log"
	"os"
)

func receiveMessage() []byte {
	var msgLen uint32
	data := make([]byte, 4)
	os.Stdin.Read(data)

	buf := bytes.NewReader(data)
	binary.Read(buf, binary.LittleEndian, &msgLen)
	log.Printf("receiving %v bytes\n", msgLen)

	data = make([]byte, msgLen)
	os.Stdin.Read(data)
	return data
}

func sendMessage() {
	r := make([]string, 1)
	r[0] = "pong"
	b, err := json.Marshal(r)
	if err != nil {
		log.Panicf("Encoding json failed: %v\n", err)
	}

	buf := new(bytes.Buffer)
	msgLen := uint32(len(b))
	binary.Write(buf, binary.LittleEndian, msgLen)
	os.Stdout.Write(buf.Bytes())
	os.Stdout.Write(b)
}

func main() {
	var msg = receiveMessage()
	log.Printf("received: %v\n", string(msg))

	var f interface{}
	err := json.Unmarshal(msg, &f)
	if err != nil {
		log.Panicf("Failed to decode json: %v\n", err)
	}

	array := f.([]interface{})
	if array[0] == "ping" {
		sendMessage()
	}
}
