package main

import (
	. "flag"
	"fmt"
)

// var Usage = "usage" // Not allowed, type mismatch

func main() {
	Parse()
	var Usage = "usage" // Allowed, it will mask Usage in flag.

	fmt.Print(Usage)
}
