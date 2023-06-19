package main

import (
	"fmt"
	"net/http"
	"strconv"
	"strings"
	"text/template"
)

const web = `
<html>
    <body>
        <h1>Statistics</h1>
        <br>
        <div>Compute basic statistics for a given list of numbers</div>
        <br>
        <div>
            Numbers(comma or space separated):
            <br>
            <form action="#" method="POST" name="in">
                <input type="text" name="numbers" />
                <input type="submit" name="Calculate" />
            </form>
        </div>
        <div>
			<h2>Results</h2>
			Numbbers:
			<br>
			Count:
			<br>
			Mean:
        </div>
    </body>
</html>
`
const webTemplate = `
<html>
    <body>
        <h1>Statistics</h1>
        <br>
        <div>Compute basic statistics for a given list of numbers</div>
        <br>
        <div>
            Numbers(comma or space separated):
            <br>
            <form action="#" method="POST" name="in">
                <input type="text" name="numbers" />
                <input type="submit" name="Calculate" />
            </form>
        </div>
        <div>
			<h2>Results</h2>
			Numbbers:{{.Nums | html}}
			<br>
			Count:{{.Cnt | html}}
			<br>
			Mean:{{.Mean | html}}
        </div>
    </body>
</html>
`

//Statistics is ...
type Statistics struct {
	Nums []int
	Cnt  int
	Mean int
}

func main() {
	http.HandleFunc("/", handleCalculation)
	if err := http.ListenAndServe("localhost:2999", nil); err != nil {
		panic("Failed to listen and serve")
	}
}

func handleCalculation(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-type", "text/html")
	var ss Statistics
	switch req.Method {
	case "GET":
		fmt.Fprint(w, web)
	case "POST":
		data := req.FormValue("numbers")
		if data == "" {
			fmt.Println("Empty data received!")
			fmt.Fprint(w, web)
			break
		}

		var nums []int
		if strings.Contains(data, ",") {
			for _, n := range strings.Split(data, ",") {
				i, err := strconv.Atoi(n)
				if err != nil {
					fmt.Println("Parsing int error!")
					continue
				}
				nums = append(nums, i)
			}
		} else {
			for _, n := range strings.Fields(data) {
				i, err := strconv.Atoi(n)
				if err != nil {
					fmt.Println("Parsing int error!")
					continue
				}
				nums = append(nums, i)
			}
		}
		ss.Nums = nums
		var total int
		for _, n := range nums {
			total += n
			ss.Cnt++
		}
		ss.Mean = total / len(nums)
		tmpl := template.Must(template.New("statistics").Parse(webTemplate))
		tmpl.Execute(w, ss)
	}

}
