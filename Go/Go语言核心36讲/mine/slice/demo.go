package main

import "fmt"

func main() {
	s1 := []int{1, 2, 3, 4, 5}
	s2 := s1[0:3]
	s3 := s1[2:5]
	fmt.Printf("s1:%v\ns2:%v\ns3:%v\n", s1, s2, s3)
	s1[2] = 999 // this changes the underlying array, which affects both s2 and s3
	fmt.Printf("\ns1:%v\ns2:%v\ns3:%v\n", s1, s2, s3)
}
