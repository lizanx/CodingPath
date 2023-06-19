package main

import (
	"encoding/json"
	"net/http"
)

func writeHandler(w http.ResponseWriter, r *http.Request) {
	res := `<!DOCTYPE html>
	<html>
		<header>
			<title>Go Web Programming</title>
		</header>
	
		<body>
		   To Learn About Go Web Programming 
		</body>
	</html>`
	w.Write([]byte(res))
}

func writeHeaderHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusNotImplemented)
	w.Write([]byte("No such service, try another door\n"))
}

func headerHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Location", "http://www.google.com")
	w.WriteHeader(http.StatusFound)
}

type UserInfo struct {
	Name   string `json:"name"`
	Age    int    `json:"age"`
	Nation string `json:"nation"`
}

func jsonHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	data, err := json.Marshal(&UserInfo{"Diana", 24, "Amazon"})
	if err == nil {
		w.Write(data)
	}
}

func main() {
	server := http.Server{
		Addr: "localhost:2999",
	}
	http.HandleFunc("/write", writeHandler)
	http.HandleFunc("/writeheader", writeHeaderHandler)
	http.HandleFunc("/header", headerHandler)
	http.HandleFunc("/json", jsonHandler)
	server.ListenAndServe()
}
