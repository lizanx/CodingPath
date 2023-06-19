package main

import (
	"fmt"
	"net/http"
)

type helloHandler struct {
}

// ServeHTTP implements the http handler
func (h helloHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Hello! - test chain handlers")
}

func chaninLogHandler(h http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		printCallerName()
		h.ServeHTTP(w, r)
	})
}

func main() {
	h := helloHandler{}
	http.Handle("/hello", chaninLogHandler(h))
	http.ListenAndServe("localhost:2999", nil)
}
