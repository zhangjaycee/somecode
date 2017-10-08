package main

import (
    "fmt"
    "log"
    "net/http"
)


func main() {
    http.HandleFunc("/zjc/", handler)
    http.HandleFunc("/", handler2)
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "oh, now in \"zjc\" directory, URL.Path = %q\n", r.URL.Path)
}
func handler2(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "this is the home page, URL.Path = %q\n", r.URL.Path)
}
