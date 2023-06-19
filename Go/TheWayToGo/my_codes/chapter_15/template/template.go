package main

import (
	"os"
	"text/template"
)

//Student is...
type Student struct {
	Name   string
	Skills []string
}

func main() {
	tmpl1 := template.Must(template.New("tmpl1").Parse("{{.Name}} has knowledge of {{range .Skills}}{{.}} {{end}}\n"))
	s1 := Student{Name: "gavin", Skills: []string{"C", "C++", "Go", "Kotlin"}}
	err := tmpl1.Execute(os.Stdout, s1)
	if err != nil {
		panic("failed to execute tmp1" + err.Error())
	}
}
