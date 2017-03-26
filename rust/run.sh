#!/bin/bash

# Resolve utils directory
UTILS="../utils"

"$UTILS/python-send-bytes.py" |
    RUST_BACKTRACE=1 cargo run |
    "$UTILS/python-recv-bytes.py"
