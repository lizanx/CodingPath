package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	ticker := time.NewTicker(time.Second * 2)
	defer ticker.Stop()
	ch := time.Tick(time.Second * 3)
	timeout := time.After(time.Second * 5)
	for {
		select {
		case t := <-ticker.C:
			fmt.Println("From ticker:", t)
		case t := <-ch:
			fmt.Println("From chan:", t)
		case <-timeout:
			fmt.Println("timeout, exit")
			os.Exit(1)
		}
	}
}
