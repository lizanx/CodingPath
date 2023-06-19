package main

import "fmt"

type myString string    // different types, with the same type under the hood
type myString2 = string // the same type

func main() {
	var s = "hello, go"
	var mys myString
	var mys2 myString2
	// mys = s // not allowed
	mys2 = s
	mys = myString(s)
	fmt.Println(mys)
	fmt.Println(mys2)

	var ss = []string{"hello", "go"}
	// var myss []myString
	var myss2 []myString2
	// var myss = ss //not allowed
	myss2 = ss
	// myss = []myString(ss) // not allowed
	fmt.Println(myss2)

}
