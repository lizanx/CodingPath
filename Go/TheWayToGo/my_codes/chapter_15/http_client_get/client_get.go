package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	resp, err := http.Get("https://www.google.com")
	if err != nil {
		log.Fatal("Failed when get:", err)
	}
	data, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("Failed when get body data:", err)
	}
	defer resp.Body.Close()
	fmt.Println("data got:", string(data))
}
