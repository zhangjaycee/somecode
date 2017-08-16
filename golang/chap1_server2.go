package main

import (
    "fmt"
    "log"
    "net/http"
    "sync"
)

var mu_cnt sync.Mutex
var count int

func main() {
    http.HandleFunc("/zjc/", handler_zjc)
    http.HandleFunc("/", handler)
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
    mu_cnt.Lock()
    count++
    mu_cnt.Unlock()
    fmt.Fprintf(w, "this is the home page (%d times visited)\n", count)
    fmt.Fprintf(w, "METHOD: %s\nURL: %s\nPATH: %s\nPROTOTYPE: %s\n", r.Method, r.URL, r.URL.Path, r.Proto)
    for k, v := range r.Header {
        fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
    }
    fmt.Fprintf(w, "Host = %q\n", r.Host)
    fmt.Fprintf(w, "RemoteAddr = %q\n", r.RemoteAddr)
    if err := r.ParseForm(); err != nil {
        log.Print(err)
    }
    for k, v := range r.Form {
        fmt.Fprintf(w, "Form[%q] = %q\n", k, v)
    }
}

func handler_zjc(w http.ResponseWriter, r *http.Request) {
    //mu_cnt.Lock()
    //count++
    //mu_cnt.Unlock()
    fmt.Fprintf(w, "oh, now in \"zjc\" (%d times visited)\nURL.Path = %q\n", count, r.URL.Path)
}
