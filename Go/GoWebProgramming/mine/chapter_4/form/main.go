package main

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/process", showForm)
	http.ListenAndServe("localhost:2999", nil)
}

func showForm(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "(1)FormValue(hello): "+r.FormValue("hello")+"\n")
	// fmt.Fprint(w, "(2)FormValue(data): "+r.FormValue("data")+"\n")
	// fmt.Fprint(w, "(3)PostFormValue(hello): "+r.PostFormValue("hello")+"\n")
	// fmt.Fprint(w, "(4)PostFormValue(data): "+r.PostFormValue("data")+"\n")

	fmt.Fprint(w, "\nParsing form...\n")
	r.ParseForm()
	fmt.Fprint(w, "(5)Form: "+fmt.Sprint(r.Form)+"\n")
	fmt.Fprint(w, "(6)PostForm: "+fmt.Sprint(r.PostForm)+"\n")

	fmt.Fprint(w, "\nParsing ParseMultipartForm...\n")
	r.ParseMultipartForm(1024)
	fmt.Fprint(w, "(7)MultipartForm: "+fmt.Sprint(r.MultipartForm)+"\n")
}
