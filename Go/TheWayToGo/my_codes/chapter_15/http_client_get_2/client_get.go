package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"sync"
)

var wg sync.WaitGroup

func main() {
	if len(os.Args) < 2 {
		log.Fatal("Plese enter the urls you want to get!")
	}
	for _, url := range os.Args[1:] {
		go getURLData(url)
		wg.Add(1)
	}
	wg.Wait()
	fmt.Println("All done!")
}

func getURLData(url string) {
	defer wg.Done()
	resp, err := http.Get(url)
	if err != nil {
		log.Println("Failed when get:", err)
		return
	}
	data, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Println("Failed when get body data:", err)
		return
	}
	defer resp.Body.Close()
	fmt.Printf("data got from [%s]: %s\n\n\n\n", url, string(data))
}
