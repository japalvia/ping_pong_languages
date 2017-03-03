#!/bin/bash

./python-send-bytes.py |
    RUST_BACKTRACE=1 cargo run |
    ./python-recv-bytes.py
