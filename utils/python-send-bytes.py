#!/usr/bin/python2

import sys
import struct
import json


def encodeMessage(messageContent):
    encodedContent = json.dumps(messageContent)
    encodedLength = struct.pack('@I', len(encodedContent))
    return {'length': encodedLength, 'content': encodedContent}


# Send an encoded message to stdout
def sendMessage(encodedMessage):
    sys.stdout.write(encodedMessage['length'])
    sys.stdout.write(encodedMessage['content'])
    sys.stdout.flush()

# sendMessage(encodeMessage( {'foo' : 'pong' } ))
sendMessage(encodeMessage( [ "ping" ] ))

