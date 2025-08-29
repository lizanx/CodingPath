#!/usr/bin/env python
import zmq


def main(who: str):
    context = zmq.Context()
    print("Connecting to server..")
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")

    for request in range(5):
        print(f"[{who}] Sending request {request} ..")
        socket.send_pyobj(who)

        msg = socket.recv_pyobj()
        print(f"[{who}] Received reply: {msg}")


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("usage: client.py <user name>")
        raise SystemExit

    main(sys.argv[-1])
