package main

import (
	"fmt"
	"io"
	"net/http"
)

func main() {
	// server := http.Server{
	// 	Addr: "127.0.0.1:2999",
	// }
	http.HandleFunc("/process", processHandler)
	http.ListenAndServe("localhost:2999", nil)
	// server.ListenAndServe()
}

func processHandler(w http.ResponseWriter, r *http.Request) {
	r.ParseMultipartForm(1024)
	// fmt.Printf("MultipartForm:%t,\n", r.MultipartForm != nil)
	// if r.MultipartForm != nil {
	// 	fmt.Printf("MultipartForm:%t, File:%t, Value:%t\n", r.MultipartForm != nil,
	// 		r.MultipartForm.File != nil, r.MultipartForm.Value != nil)
	// }
	if _, ok := r.MultipartForm.File["uploaded"]; !ok {
		fmt.Println("No file from form['uploaded']!")
		return
	}
	fileHeader := r.MultipartForm.File["uploaded"][0]
	file, err := fileHeader.Open()
	if err == nil {
		data, err := io.ReadAll(file)
		if err != nil {
			fmt.Println("Failed to read data from the first file, err:", err)
		} else {
			fmt.Fprint(w, string(data))
		}
	}
}
