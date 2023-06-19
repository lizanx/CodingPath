package main

import "fmt"

var fc chan uint64

func fibonacci() chan uint64 {
	yield := make(chan uint64)
	var x, y uint64 = 1, 1
	go func() {
		for {
			x, y = y, x+y
			yield <- y
		}
	}()
	return yield
}

func fibonacciGenerator() uint64 {
	return <-fc
}

func main() {
	fc = fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(i, "->", fibonacciGenerator())
	}
}
