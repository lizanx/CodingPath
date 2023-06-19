package main

import "fmt"

func main() {
	var x = 5
	var y = 0
	y, z := squareCube(x)
	fmt.Printf("x:%d, y:%d, z:%d\n", x, y, z)
}

func squareCube(x int) (int, int) {
	return x * x, x * x * x
}
