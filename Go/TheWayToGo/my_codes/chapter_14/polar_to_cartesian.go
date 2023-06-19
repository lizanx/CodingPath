package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func main() {
	polarChan := make(chan polar)
	cartesianChan := make(chan cartesian)
	go parseCartesian(polarChan, cartesianChan)
	go printCartesian(cartesianChan)

	inputReader := bufio.NewReader(os.Stdin)
	for {
		fmt.Println("Please enter polar coordination:(enter quit to stop)")
		line, err := inputReader.ReadString('\n')
		if err != nil {
			fmt.Println("Failed to get input, err:", err)
			continue
		}
		if strings.Contains(line, "quit") {
			fmt.Println("quit received, exit program")
			os.Exit(0)
		}
		line = line[:len(line)-1]
		paras := strings.Fields(line)
		if len(paras) != 2 {
			fmt.Println("Incorrect input:", paras, "\tPlease try again")
			continue
		}
		var p polar
		p.angle, err = strconv.ParseFloat(paras[0], 64)
		if err != nil {
			fmt.Println("Error when parsing angle:", err)
			continue
		}
		p.radius, err = strconv.ParseFloat(paras[1], 64)
		if err != nil {
			fmt.Println("Error when parsing radius:", err)
			continue
		}
		polarChan <- p
	}
}

type polar struct {
	angle  float64
	radius float64
}

type cartesian struct {
	x float64
	y float64
}

func parseCartesian(pc chan polar, cc chan cartesian) {
	p := <-pc
	var c cartesian
	c.x = p.radius * math.Cos(p.angle)
	c.y = p.radius * math.Sin(p.angle)
	cc <- c
}

func printCartesian(cc chan cartesian) {
	c := <-cc
	fmt.Printf("Cartesian coordination parses: [%f, %f]\n", c.x, c.y)
}
