package main

import (
	"fmt"
//	"os"
//  "strings"
)

func main() {
    var a = 10
    var p *int
    p = &a
    fmt.Printf("a = %d, p = 0x%x\n",a, p)
    fmt.Printf("*p++\n")
    *p++
    fmt.Printf("a = %d, p = 0x%x\n",a, p)
}
