package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"os"
	"strconv"
)

type Post struct {
	ID      int
	Author  string
	Content string
}

func main() {
	csvFile, err := os.OpenFile("posts.csv", os.O_RDWR|os.O_CREATE, 0644)
	if err != nil {
		log.Fatalln("Failed to open file posts.csv")
	}
	defer csvFile.Close()

	posts := []Post{
		{ID: 1, Author: "Diana", Content: "I'm the Wonder Woman"},
		{ID: 2, Author: "Rob Pike", Content: "Welcome to Go programming"},
		{ID: 3, Author: "Bill Gates", Content: "Let's work together to achieve a zero-carbo life"},
		{ID: 4, Author: "Diana", Content: "Joined the Justice League"},
	}

	w := csv.NewWriter(csvFile)
	for _, post := range posts {
		err := w.Write([]string{strconv.Itoa(post.ID), post.Author, post.Content})
		if err != nil {
			panic(err)
		}
	}
	w.Flush()
	if err = w.Error(); err != nil {
		panic(err)
	}

	file, err := os.Open("posts.csv")
	if err != nil {
		log.Fatalln("Failed to open posts.csv for reading", err)
	}
	r := csv.NewReader(file)
	records, err := r.ReadAll()
	if err != nil {
		log.Fatalln("Error occurs during reading:", err)
	}
	for _, record := range records {
		fmt.Printf("%v\n", record)
	}

}
