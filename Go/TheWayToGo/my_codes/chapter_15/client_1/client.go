package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:2233")
	if err != nil {
		fmt.Fprint(os.Stderr, "Failed to dial:", err.Error())
		return
	}

	inputReader := bufio.NewReader(os.Stdin)
	fmt.Println("Please enter your name:")
	clientName, _ := inputReader.ReadString('\n')
	trimmedClient := strings.Trim(clientName, "\r\n")
	for {
		fmt.Println("Enter the message you wanna send(type Q to quit):")
		msg, _ := inputReader.ReadString('\n')
		trimmedMsg := strings.Trim(msg, "\r\n")
		if trimmedMsg == "Q" {
			fmt.Println("Exit msg received!")
			return
		}
		_, err := conn.Write([]byte(trimmedClient + " says " + trimmedMsg))
		if err != nil {
			fmt.Fprint(os.Stderr, "Failed to write:", err.Error())
		}
	}
}
