package main

import (
	"container/list"
	"fmt"
	"strings"
)

func main() {
	var l = list.New()
	for i := 0; i < 10; i++ {
		l.PushBack(i)
	}
	var sb strings.Builder
	for node := l.Back(); node != nil; node = node.Prev() {
		sb.WriteString(fmt.Sprint(node.Value.(int)))
	}
	fmt.Println(sb.String())
}
