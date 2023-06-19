package main

import (
	"net/http"
	"text/template"
)

func main() {
	http.HandleFunc("/basic", basicTmpl)
	http.HandleFunc("/conditional", conditionalTmpl)
	http.HandleFunc("/range", rangeTmpl)
	http.HandleFunc("/with", withTmpl)
	http.HandleFunc("/include", includeTmpl)
	http.ListenAndServe("localhost:2999", nil)
}

func basicTmpl(w http.ResponseWriter, r *http.Request) {
	t := template.Must(template.ParseFiles("tmpl.html"))
	t.Execute(w, "Hello, Basic Use of Template!")
}
func conditionalTmpl(w http.ResponseWriter, r *http.Request) {
	t := template.Must(template.ParseFiles("conditional.html"))
	t.Execute(w, r.FormValue("data"))
}
func rangeTmpl(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	t := template.Must(template.ParseFiles("range.html"))
	t.Execute(w, r.Form["data"])
}

func withTmpl(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	t := template.Must(template.ParseFiles("with.html"))
	t.Execute(w, r.Form["data"])
}

func includeTmpl(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	t := template.Must(template.ParseFiles("include_1.html", "include_2.html"))
	t.Execute(w, r.Form["data"])
}
