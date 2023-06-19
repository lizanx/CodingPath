package main

import (
	"fmt"
	"net/http"
)

func setCookieHandler(w http.ResponseWriter, r *http.Request) {
	c1 := http.Cookie{
		Name:     "first_cookie",
		Value:    "Go Web Programming",
		HttpOnly: true,
	}
	c2 := http.Cookie{
		Name:     "second_cookie",
		Value:    "Manning Publication Co",
		HttpOnly: true,
	}
	http.SetCookie(w, &c1)
	http.SetCookie(w, &c2)
}

func getCookieHandler(w http.ResponseWriter, r *http.Request) {
	c1, err := r.Cookie("first_cookie")
	if err != nil {
		fmt.Fprintf(w, "Failed to get cookie 'first_cookie', err: %v\n", err)
	} else {
		fmt.Fprintf(w, "c1: %v\n", c1)
	}
	c2 := r.Cookies()
	fmt.Fprintf(w, "c2: %v\n", c2)
}

func main() {
	http.HandleFunc("/setcookie", setCookieHandler)
	http.HandleFunc("/getcookie", getCookieHandler)
	http.ListenAndServe("localhost:2999", nil)
}
