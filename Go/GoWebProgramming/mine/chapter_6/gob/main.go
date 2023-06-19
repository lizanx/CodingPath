package main

import (
	"bytes"
	"encoding/gob"
	"fmt"
	"io"
	"log"
	"os"
)

type Post struct {
	ID      int
	Author  string
	Content string
}

func main() {
	posts := []Post{
		{ID: 1, Author: "Diana", Content: "I'm the Wonder Woman"},
		{ID: 2, Author: "Rob Pike", Content: "Welcome to Go programming"},
		{ID: 3, Author: "Bill Gates", Content: "Let's work together to achieve a zero-carbo life"},
		{ID: 4, Author: "Diana", Content: "Joined the Justice League"},
	}

	buf := new(bytes.Buffer)
	enc := gob.NewEncoder(buf)
	for _, post := range posts {
		if err := enc.Encode(&post); err != nil {
			log.Fatal(err)
		}
	}
	file, err := os.OpenFile("posts.gob", os.O_WRONLY|os.O_CREATE, 0600)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	file.Write(buf.Bytes())
	file.Sync()

	content, err := os.ReadFile("posts.gob")
	if err != nil {
		log.Fatal(err)
	}
	buf = bytes.NewBuffer(content)
	dec := gob.NewDecoder(buf)
	var post Post
	for {
		if err := dec.Decode(&post); err != nil {
			if err == io.EOF {
				break
			} else {
				log.Fatal(err)
			}
		} else {
			fmt.Printf("%v\n", post)
		}
	}
}
