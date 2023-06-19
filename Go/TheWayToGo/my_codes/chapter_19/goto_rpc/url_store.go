package main

import (
	"encoding/json"
	"errors"
	"log"
	"os"
	"sync"
)

const saveQueueLength = 1000

type record struct {
	Key, URL string
}

//URLStore manipulates relationship between short and long urls
type URLStore struct {
	urls     map[string]string
	mu       sync.RWMutex
	saveChan chan record
}

//NewURLStore returns a new URLStore pointer
func NewURLStore(dataFile string) *URLStore {
	store := &URLStore{urls: make(map[string]string)}
	if dataFile != "" {
		store.saveChan = make(chan record, saveQueueLength)
		if err := store.load(dataFile); err != nil {
			log.Println("Failed to load url store:", err)
		}
		go store.saveService(dataFile)	
	}
	return store
}

//Load loads the existing data in passed data file and store them in the map
func (s *URLStore) load(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		log.Println("Failed to open data file:", filename)
		return err
	}
	defer f.Close()
	dec := json.NewDecoder(f)
	var r record
	for dec.More() {
		dec.Decode(&r)
		if err = s.Set(&r.Key, &r.URL); err != nil {
			log.Printf("Failed to load key-url pair {%s, %s}\n", r.Key, r.URL)
			break
		}
	}
	log.Println("Load", filename, "done.")
	return err
}

func (s *URLStore) saveService(dataFile string) {
	f, err := os.OpenFile(dataFile, os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0644)
	if err != nil {
		log.Fatal("Failed to open", dataFile, "for save service.")
	}
	defer f.Close()
	enc := json.NewEncoder(f)
	for {
		r := <-s.saveChan
		if err := enc.Encode(r); err != nil {
			log.Printf("Failed to encode key-url pair {%s, %s}\n", r.Key, r.URL)
		}
	}
}

//Get returns long url mapped from short url
func (s *URLStore) Get(key, url *string) error {
	s.mu.RLock()
	defer s.mu.RUnlock()
	if result, ok := s.urls[*key]; ok {
		*url = result
		return nil
	}
	return errors.New("key not found")
}

//Set adds a new short-long url pair to the map
func (s *URLStore) Set(key, url *string) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if _, present := s.urls[*key]; present {
		//Only unused short url as key is allowed.
		return errors.New("key already exists")
	}
	s.urls[*key] = *url
	return nil
}

//Count returns the the number of stored url pairs
func (s *URLStore) Count() int {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return len(s.urls)
}

//Put generates a key for the long url and put it into the map
func (s *URLStore) Put(url, shortURL *string) error {
	for {
		key := genKey(s.Count()) //repeatedly generate keys until it's unused
		if err := s.Set(&key, url); err != nil {
			return err
		} else {
			*shortURL = key
			break
		}
	}
	if s.saveChan != nil {
		s.saveChan <- record{*shortURL, *url}
	}
	return nil
}
