#!/usr/bin/python2

import sys
import struct
import json


def getMessage():
    rawLength = sys.stdin.read(4)
    if len(rawLength) == 0:
        sys.exit(0)
    messageLength = struct.unpack('@I', rawLength)[0]
    print(" python recv len: {}".format(messageLength))
    message = sys.stdin.read(messageLength)
    return json.loads(message)

receivedMessage = getMessage()
print("receivedMessage:{}".format(receivedMessage))
