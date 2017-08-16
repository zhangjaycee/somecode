package main

import (
    "fmt"
)

func main() {
    ascii := 'a'
    unicode := '汉'
    newline := '\n'
    fmt.Printf("%d %[1]c %[1]q\n", ascii)   // "97 a 'a'"
    fmt.Printf("%d %[1]c %[1]q\n", unicode) // "22269 国 '国'"
    fmt.Printf("%d %[1]q\n", newline)       // "10 '\n'"

    var z float64
    fmt.Println(z, -z, 1/z, -1/z, z/z) // "0 -0 +Inf -Inf NaN"

    var s = "hello, world"
    fmt.Println(s)
    fmt.Println(s[:5]) // "hello"
    fmt.Println(s[7:]) // "world"
    fmt.Println(len(s))     // "12"
    fmt.Println(s[0], s[7]) // "104 119" ('h' and 'w')
    fmt.Println(s[:])  // "hello, world"

    for i, r := range "Hello, 世界" {
        fmt.Printf("%d\t%q\t%d\n", i, r, r)
    }
}
