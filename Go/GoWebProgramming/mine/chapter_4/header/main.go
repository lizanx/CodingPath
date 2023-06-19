package main

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/showHeader", showHeader)
	http.HandleFunc("/getAccept", getAccept)
	http.HandleFunc("/valuesAccept", valuesAccept)
	http.ListenAndServe("localhost:2999", nil)
}

func showHeader(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, r.Header)
}

func getAccept(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, r.Header.Get("Accept"))
}

func valuesAccept(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, r.Header.Values("Accept"))
}
