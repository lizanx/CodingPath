package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	ln, err := net.Listen("tcp", "localhost:2233")
	if err != nil {
		fmt.Fprint(os.Stderr, "Failed to listen:", err.Error())
		return
	}
	for {
		conn, err := ln.Accept()
		if err != nil {
			fmt.Fprint(os.Stderr, "Failed to accep:", err.Error())
			return
		}
		go handleReq(conn)
	}
}

func handleReq(conn net.Conn) {
	buf := make([]byte, 512)
	for {
		cnt, err := conn.Read(buf)
		if err != nil {
			fmt.Fprint(os.Stderr, "Failed to handle request:", err.Error())
			return
		}
		fmt.Println("msg received:", string(buf[:cnt]))
	}
}
