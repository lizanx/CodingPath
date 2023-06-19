package main

import (
	"fmt"
	"time"
)

var chars = []byte{'A', 'B', 'C', 'D', 'E', 'F'}

func main() {
	for i := range chars {
		func() {
			fmt.Print(i, " ")
		}()
	}
	fmt.Println()
	time.Sleep(5 * time.Second)

	for i := range chars {
		go func() {
			fmt.Print(i, " ")
		}()
	}
	fmt.Println()
	time.Sleep(5 * time.Second)

	for i := range chars {
		go func(j int) {
			fmt.Print(j, " ")
		}(i)
	}
	fmt.Println()
	time.Sleep(5 * time.Second)

	for i := range chars {
		index := i
		go func() {
			fmt.Print(index, " ")
		}()
	}
	fmt.Println()
	time.Sleep(5 * time.Second)
}
