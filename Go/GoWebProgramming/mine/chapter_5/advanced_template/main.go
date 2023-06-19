package main

import (
	"net/http"
	"strings"
	"text/template"
)

func main() {
	http.HandleFunc("/pipeline", pipelineHandler)
	http.HandleFunc("/func", funcHandler)
	http.HandleFunc("/layout", layoutHandler)
	http.ListenAndServe("localhost:2999", nil)
}

func pipelineHandler(w http.ResponseWriter, r *http.Request) {
	t := template.Must(template.ParseFiles("pipeline.html"))
	r.ParseForm()
	t.Execute(w, r.Form["data"])
}

func funcHandler(w http.ResponseWriter, r *http.Request) {
	t := template.Must(template.New("funcMap.html").Funcs(template.FuncMap{
		"lower": strings.ToLower,
		"upper": strings.ToUpper,
		"title": strings.Title}).ParseFiles("funcMap.html"))
	r.ParseForm()
	t.Execute(w, r.Form["data"])
}

func layoutHandler(w http.ResponseWriter, r *http.Request) {
	var t *template.Template
	color := r.FormValue("color")
	if color == "blue" {
		t = template.Must(template.ParseFiles("layout.html", "blue_hello.html"))
	} else if color == "red" {
		t = template.Must(template.ParseFiles("layout.html", "red_hello.html"))
	} else {
		t = template.Must(template.ParseFiles("layout.html"))
	}
	t.ExecuteTemplate(w, "layout", "")
}
