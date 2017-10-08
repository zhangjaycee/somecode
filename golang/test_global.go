package main

import (
	"fmt"
)

var global *int

func f() {
    var x int
    x = 10
    global = &x
}

func main() {
	f()
	fmt.Printf("*global = %d\n", *global)
}
