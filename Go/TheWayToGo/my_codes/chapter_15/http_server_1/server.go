package main

import (
	"fmt"
	"log"
	"net/http"
	"strings"
)

const name = "gavin"

func main() {
	http.HandleFunc("/hello/Name", handleHello)
	http.HandleFunc("/shoutHello/Name", handleShoutHello)
	err := http.ListenAndServe("localhost:2999", nil)
	if err != nil {
		log.Fatal("Failed to listenAndServe:", err)
	}
}

func handleHello(w http.ResponseWriter, req *http.Request) {
	fmt.Println("insdie hello handler!")
	fmt.Fprint(w, strings.ToUpper(name[0:1])+name[1:])
}

func handleShoutHello(w http.ResponseWriter, req *http.Request) {
	fmt.Println("insdie ShoutHello handler!")
	fmt.Fprint(w, strings.ToUpper(name))
}
