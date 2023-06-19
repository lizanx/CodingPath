package main

import (
	"fmt"
	"net/http"

	"github.com/julienschmidt/httprouter"
)

func rootHandler(w http.ResponseWriter, r *http.Request, _ httprouter.Params) {
	fmt.Fprint(w, "root handler")
}

func greetHandler(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	fmt.Fprintf(w, "Hello, %s!", ps.ByName("name"))
}

func main() {
	router := httprouter.New()
	router.GET("/", rootHandler)
	router.GET("/:name", greetHandler)

	server := http.Server{
		Addr:    "localhost:2999",
		Handler: router,
	}
	server.ListenAndServe()
}
