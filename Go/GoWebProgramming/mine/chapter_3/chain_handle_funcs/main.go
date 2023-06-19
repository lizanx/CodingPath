package main

import (
	"fmt"
	"net/http"
)

func helloHandleFunc(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello!")
}

func chainLog(h http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		printCallerName()
		h(w, r)
	}
}

func main() {
	http.HandleFunc("/hello", chainLog(helloHandleFunc))
	http.ListenAndServe("localhost:2999", nil)
}
