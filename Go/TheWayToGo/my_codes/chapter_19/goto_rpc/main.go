package main

import (
	"flag"
	"fmt"
	"net/http"
	"net/rpc"
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

// Store represents main server URLStore or sub-server ProxyStore
type Store interface {
	Get(key, url *string) error
	Put(url, key *string) error
}

var store Store
var (
	listenAddr = flag.String("http", ":2999", "http listen address")
	dataFile   = flag.String("file", "store.json", "data store file name")
	hostName   = flag.String("host", "localhost:2999", "host name and address")
	rpcEnabled = flag.Bool("rpc", false, "enable RPC server")
	masterAddr = flag.String("master", "", "RPC master address")
)

func main() {
	flag.Parse()
	if *masterAddr != "" {
		store = NewProxyStore(*masterAddr)
	} else {
		store = NewURLStore(*dataFile)
	}
	if *rpcEnabled {
		rpc.RegisterName("Store", store)
		rpc.HandleHTTP()
	}
	http.HandleFunc("/", Redirect)
	http.HandleFunc("/add", Add)
	http.ListenAndServe(*listenAddr, nil)
}

// Redirect redirects short urls to corresponding long urls
func Redirect(w http.ResponseWriter, r *http.Request) {
	key := r.URL.Path
	if key[0] == '/' {
		key = key[1:]
	}
	var url string
	if err := store.Get(&key, &url); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
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
	var key string
	if err := store.Put(&url, &key); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	fmt.Fprintf(w, "Store new url pair successfully: %s/%s -> %s", *hostName, key, url)
}
