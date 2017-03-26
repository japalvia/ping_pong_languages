#!/bin/bash

UTILS=../utils

# Build and run:
go build main.go &&
    "$UTILS/python-send-bytes.py" \
        | ./main \
        | "$UTILS/python-recv-bytes.py"
