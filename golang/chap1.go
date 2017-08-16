package main

import (
	"fmt"
	"os"
    "strings"
)

func main() {
	var s, sep string
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
	fmt.Println(s)
    fmt.Println("Prac. 1:")
	fmt.Println(os.Args[0])
    fmt.Println("Prac. 2:")
    for index, value := range os.Args[1:] {
	    fmt.Println(index)
	    fmt.Println(value)
    }
    fmt.Println("Prac. 3:")
	fmt.Println(strings.Join(os.Args[1:], " "))
	fmt.Println(os.Args[1:])

}
