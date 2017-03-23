#!/bin/bash

# Build and run:
go build main.go &&
    ~/ws/ping_pong_c/python-send-bytes.py | ./main
