package main

import (
	"fmt"
	"runtime"
)

func printCallerName() {
	pc, file, line, ok := runtime.Caller(1)
	if !ok {
		fmt.Println("Failed to recover information.")
		return
	}
	callerName := runtime.FuncForPC(pc).Name()
	fmt.Printf("Name: %s, in file %s at line %d\n", callerName, file, line)
}

func printCallChain() {
	pc := make([]uintptr, 10)
	n := runtime.Callers(0, pc)
	fmt.Println(n, "PCs got.")

	frames := runtime.CallersFrames(pc[:n])
	for frame, more := frames.Next(); more; frame, more = frames.Next() {
		fmt.Printf("Func name: %s, in file %s at line %d\n", frame.Function, frame.File, frame.Line)
	}
}

func foo() {
	fmt.Println("Test printing func name in foo.")
	printCallerName()
}

func bar() {
	fmt.Println("Test printing funcion calling chain in bar.")
	printCallChain()
}

func main() {
	foo()
	fmt.Println()
	bar()
}
