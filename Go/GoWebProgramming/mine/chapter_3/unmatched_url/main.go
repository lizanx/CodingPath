package main

import (
	"fmt"
	"net/http"
)

func rootHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "root handler")
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "hello handler")
}

func helloWorldHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "hello world handler")
}

func nameHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "name handler")
}

func usernameHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "username handler")
}

func main() {
	http.HandleFunc("/", rootHandler)
	// end with no "/", only exact match is allowed, otherwise mismatched url(like "/hello/go") is handled by rootHandler
	http.HandleFunc("/hello", helloHandler)
	http.HandleFunc("/hello/world", helloWorldHandler)
	// end with "/", can handle mismatched url(eg: "/name/adminname" is handled by nameHandler, rather than rootHandler)
	http.HandleFunc("/name/", nameHandler)
	http.HandleFunc("/name/username/", usernameHandler)

	http.ListenAndServe("localhost:2999", nil)
}
