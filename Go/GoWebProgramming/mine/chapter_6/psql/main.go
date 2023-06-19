package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/lib/pq"
)

type Post struct {
	ID      int
	Content string
	Author  string
}

func GetPost(id int) (post Post, err error) {
	post = Post{}
	err = Db.QueryRow("SELECT id, content, author FROM posts WHERE id=$1", id).Scan(&post.ID, &post.Content, &post.Author)
	return
}

func (post *Post) Create() (err error) {
	statement := "INSERT INTO posts (content, author) values ($1, $2) returning id"
	stmt, err := Db.Prepare(statement)
	if err != nil {
		return
	}
	defer stmt.Close()
	err = stmt.QueryRow(post.Content, post.Author).Scan(&post.ID)
	return
}

func (post *Post) Update() (err error) {
	_, err = Db.Exec("UPDATE posts SET content = $2, author = $3 WHERE id = $1", post.ID, post.Content, post.Author)
	return
}

func (post *Post) Delete() (err error) {
	_, err = Db.Exec("DELETE FROM posts WHERE id = $1", post.ID)
	return
}

var Db *sql.DB

func init() {
	var err error
	Db, err = sql.Open("postgres", "user=gwp dbname=gwp_db sslmode=disable")
	if err != nil {
		panic(err)
	}
}

func main() {
	post := Post{Content: "Hello, Go Web Programming", Author: "Gavin"}
	fmt.Println("0:", post)
	err := post.Create()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("1:", post)
	post, err = GetPost(post.ID)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("2:", post)
	post.Author = "Diana"
	post.Content = "I'm the Wonder Woman"
	err = post.Update()
	if err != nil {
		log.Fatal(err)
	}
	post, err = GetPost(post.ID)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("3:", post)
	err = post.Delete()
	if err != nil {
		log.Println("Failed to delete")
		log.Fatal(err)
	}
}
