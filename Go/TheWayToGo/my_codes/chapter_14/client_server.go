package main

import (
	"fmt"
	"time"
)

type request struct {
	a, b int
	ch   chan int
}

type binOps func(a, b int) int

func run(op binOps, req *request) {
	req.ch <- op(req.a, req.b)
}

func server(op binOps, service chan *request, quit chan bool) {
	for {
		select {
		case req := <-service:
			go run(op, req)
		case <-quit:
			fmt.Println("exit signal received")
			return
		}
	}
}

func startServer(op binOps) (chan *request, chan bool) {
	reqChan, quitChan := make(chan *request), make(chan bool)
	go server(op, reqChan, quitChan)
	return reqChan, quitChan
}

func main() {
	reqChan, quitChan := startServer(func(a, b int) int { return a * b })
	var reqs [100]request
	for i := 0; i < 100; i++ {
		reqs[i].a, reqs[i].b, reqs[i].ch = i, i+1, make(chan int)
		reqChan <- &reqs[i]
	}
	for i := 0; i < 100; i++ {
		res := <-reqs[i].ch
		if res != reqs[i].a*reqs[i].b {
			fmt.Printf("Failed! reqs[%d] res=%d\n", i, res)
		} else {
			fmt.Printf("request %d is successfully served! res=%d\n", i, res)
		}
	}
	quitChan <- true
	time.Sleep(1 * time.Second)
	fmt.Println("done!")
}
