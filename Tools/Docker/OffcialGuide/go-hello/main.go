package main

import (
	"fmt"
	"os"
)

func main() {
	fmt.Println("Checking environment variables...")
	home := os.Getenv("HOME")
	fmt.Println("HOME:", home)
	path := os.Getenv("PATH")
	fmt.Println("PATH:", path)
	env := os.Getenv("FOO")
	fmt.Println("FOO:", env)
}
