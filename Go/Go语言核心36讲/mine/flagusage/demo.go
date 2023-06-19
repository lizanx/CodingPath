package main

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var myCmdLine = flag.NewFlagSet("MyCmdLine", flag.ExitOnError)
var name string
var p person

func init() {
	// flag.CommandLine = flag.NewFlagSet("CustomizedCmdLine", flag.ExitOnError)
	// flag.CommandLine.Usage = func() {
	// 	fmt.Fprintf(os.Stdout, "Usage of flag, a demo(cmdline=%s):\n", flag.CommandLine.Name())
	// 	flag.PrintDefaults()
	// }

	myCmdLine.Usage = func() {
		fmt.Fprintf(os.Stdout, "Usage of flag, a demo(cmdline=%s):\n", myCmdLine.Name())
		myCmdLine.PrintDefaults()
	}

	// flag.StringVar(&name, "name", "Nobody", "`person name`")
	myCmdLine.StringVar(&name, "name", "Nobody", "`person name`")
	myCmdLine.Var(&p, "person", "info of a `person`")
}

func main() {
	// flag.Parse()

	myCmdLine.Parse(os.Args[1:])

	fmt.Printf("Hello, %s!\n", name)
	fmt.Print(p.String())
}

type person struct {
	name   string
	age    int
	career string
}

func (p *person) String() string {
	return fmt.Sprintf("Person[name=%s|age=%d|career=%s]", p.name, p.age, p.career)
}

func (p *person) Set(s string) error {
	parts := strings.Split(s, ",")
	if len(parts) != 3 {
		return fmt.Errorf("Invalid arguments: %s", s)
	}
	age, err := strconv.Atoi(parts[1])
	if err != nil {
		return fmt.Errorf("Invalid age: %s", parts[1])
	}
	p.name = parts[0]
	p.age = age
	p.career = parts[2]
	return nil
}
