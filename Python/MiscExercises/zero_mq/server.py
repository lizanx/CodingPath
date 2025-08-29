#!/usr/bin/env python
import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    msg = socket.recv_pyobj()
    print(f"Received request: {msg}")
    time.sleep(1)
    socket.send_pyobj(f"Hello {msg}")
