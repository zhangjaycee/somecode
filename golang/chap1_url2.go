package main

import (
    "fmt"
    "io"
    "io/ioutil"
    "net/http"
    "os"
    "time"
)

func main() {
    channel := make(chan string)
    for _, url := range os.Args[1:] {
        go fetch(url, channel)
    }
    for range os.Args[1:] {
        fmt.Println(<-channel)
    }
    fmt.Printf("main done\n")
}


func fetch(url string, channel chan<- string) {
    start := time.Now()
    resp, err := http.Get(url)
    if err != nil {
        channel <- fmt.Sprintf("fetch:%v\n", err)
    }
    nbytes, err := io.Copy(ioutil.Discard, resp.Body)
    resp.Body.Close()
    if err != nil {
        channel <- fmt.Sprintf("fetch copying %s:%v\n", url, err)
    }
    td := time.Since(start).Seconds()
    channel <- fmt.Sprintf("%.2f s\t%d bytes\t%s", td, nbytes, url)
}
