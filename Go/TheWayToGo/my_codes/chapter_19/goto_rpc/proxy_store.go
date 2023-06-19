package main

import (
	"log"
	"net/rpc"
)

// ProxyStore runs on proxy server, which has key-url pairs cache.
type ProxyStore struct {
	client *rpc.Client
	urls *URLStore
}

// NewProxyStore returns a new ProxyStore.
func NewProxyStore(addr string) *ProxyStore {
	client, err := rpc.Dial("tcp", addr)
	if err != nil {
		log.Println("Error creating new proxystore:", err)
	}
	return &ProxyStore{client: client, urls: NewURLStore("")}
}

// Get returns the url according to the key, search proxy server cache first, then main server.
func (p *ProxyStore) Get(key, url *string) error {
	if err := p.urls.Get(key, url); err == nil {
		return nil
	}
	if err := p.client.Call("Store.Get", key, url); err != nil {
		return err
	}
	p.urls.Set(key, url)
	return nil
}

// Put executes call to main server to store new url, and update the local cache.
func (p *ProxyStore) Put(url, key *string) error {
	if err := p.client.Call("Sotre.Put", url, key); err != nil {
		return err
	}
	p.urls.Set(key, url)
	return nil
}