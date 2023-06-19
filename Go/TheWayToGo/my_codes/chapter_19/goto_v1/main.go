package main

import (
	"fmt"
	"net/http"
)

// AddForm is the form for input url info
const AddForm = `
<html>
	<form method="POST" action="/add">
	URL: <input type="text" name="url">
	<input type="submit" value="Add">
	</form>
</html>
`

var store = NewURLStore()

func main() {
	http.HandleFunc("/", Redirect)
	http.HandleFunc("/add", Add)
	http.ListenAndServe("localhost:2999", nil)
}

// Redirect redirects short urls to corresponding long urls
func Redirect(w http.ResponseWriter, r *http.Request) {
	key := r.URL.Path
	if key[0] == '/' {
		key = key[1:]
	}
	url := store.Get(key)
	if url == "" {
		http.NotFound(w, r)
		return
	}
	http.Redirect(w, r, url, http.StatusFound)
}

// Add adds a long url to the stored pair with a newly generated short url
func Add(w http.ResponseWriter, r *http.Request) {
	url := r.FormValue("url")
	if url == "" {
		fmt.Fprint(w, AddForm)
		return
	}
	if key := store.Put(url); key != "" {
		fmt.Fprintf(w, "Store new url pair successfully: http://localhost:2999/%s -> %s", key, url)
	}
}
