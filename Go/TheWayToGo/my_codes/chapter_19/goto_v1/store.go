package main

import "sync"

//URLStore manipulates relationship between short and long urls
type URLStore struct {
	urls map[string]string
	mu   sync.RWMutex
}

//NewURLStore returns a new URLStore pointer
func NewURLStore() *URLStore {
	return &URLStore{urls: make(map[string]string)}
}

//Get returns long url mapped from short url
func (s *URLStore) Get(short string) string {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.urls[short]
}

//Set adds a new short-long url pair to the map
func (s *URLStore) Set(key, url string) bool {
	s.mu.Lock()
	defer s.mu.Unlock()
	if _, present := s.urls[key]; present {
		//Only unused short url as key is allowed.
		return false
	}
	s.urls[key] = url
	return true
}

//Count returns the the number of stored url pairs
func (s *URLStore) Count() int {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return len(s.urls)
}

//Put generates a key for the long url and put it into the map
func (s *URLStore) Put(url string) string {
	for {
		key := genKey(s.Count()) //repeatedly generate keys until it's unused
		if ok := s.Set(key, url); ok {
			return key
		}
	}
	//should never reach here
	return ""
}
