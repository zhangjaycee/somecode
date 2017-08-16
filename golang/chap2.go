package main

import(
    "fmt"
    "flag"
)

var optPrintLog = flag.Bool("p", false, "print debug log to screen")
var optHello = flag.String("s", "hello~", "welcome words")

const foo = 1024 //一级声明，常量，同一个包的所有文件可见
var foo2 = 1024 //一级声明，变量，同一个包的所有文件可见
var globalVar *int



func main() {
    //进行命令行参数解析
    flag.Parse()
    //参数变量是指针类型，注意用*进行解引用操作 
    fmt.Printf("%s\n", *optHello)
    if *optPrintLog == true {
        fmt.Printf("---===:::hello, I am a debug message:::===---\n")
    }
    //第一种定义和初始化变量的方法 var [variable] [type](optional) = [expression]
    var bar float64 = 10.11 //局部变量，只在当前函数可用
    //第二种定义和初始化变量的方法 var [variable] [type]; [variable] = [expression]
    var bar2 float64
    bar2 = 20.22
    //第三种定义和初始化变量的方法 [variable] := [expression]
    bar3 := 30.33
    fmt.Printf("%f + %f +%f = %f\n", bar, bar2, bar3, add(bar3, add(bar, bar2)))
    //其他初始化方式
    var i, j, k int                 // int, int, int
    var b, f, s = true, 2.3, "four" // bool, float64, string
    fmt.Printf("%d %d %d %t %f %s\n", i, j, k, b, f, s)

    var foo = 100
    var ptr = &foo
    fmt.Printf("foo: %d &ptr: %d\n", foo, &ptr)
    pointer(ptr)
    fmt.Printf("[func: *ptr++]\t\t\tfoo: %d\t*ptr: %d\tptr: %d\n", foo, *ptr, ptr)
    pointer(ptr)
    fmt.Printf("[func: *ptr++]\t\t\tfoo: %d\t*ptr: %d\tptr: %d\n", foo, *ptr, ptr)
    var ptr2 = pointer2(ptr)
    fmt.Printf("[func: *ptr++; ptr2=ptr]\tfoo: %d\t*ptr2: %d\tptr: %d\tptr2: %d\n", foo, *ptr2, ptr, ptr2)
    *ptr2 += 1
    fmt.Printf("[*ptr2 += 1]\t\t\tfoo: %d\t*ptr: %d\t*ptr2: %d\n", foo, *ptr, *ptr2)
    *ptr += 1
    fmt.Printf("[*ptr += 1]\t\t\tfoo: %d\t*ptr: %d\t*ptr2: %d\n", foo, *ptr, *ptr2)

}

//函数定义，以func开头。参数列表后的返回列表是可选的，这里是float64类型的返回值
func add(a float64, b float64) float64 {
    return a + b
}

func pointer(a *int) {
   *a++ 
}

func pointer2(a *int) *int {
   var b *int
   c := 1111024
   b = &c
   fmt.Printf("%d\n", *b)
   *a += 1
   var ptr2 = a 
   return ptr2
}


func funcVar() {
    //退出本函数时，x从函数中逃逸了，所以编译器应该把x分配到堆上
    var x int =100
    globalVar = &x
    //退出本函数时，y没有从函数中逃逸，所以编译器可以分配到栈上
}
