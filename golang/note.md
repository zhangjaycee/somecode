# 0. 基础

## 0.1 运行 
go run PATH

## 0.2 编译 
go build PATH

golang都是静态编译

## 0.3 代码格式化
go fmt PATH

## 0.4 程序执行顺序
init函数 --> main函数， 例如：

```go
package main

import (
    "fmt"
)

func init() {
    fmt.Println("this is init...")
}

func main() {
    fmt.Println("this is main...")
}
```

输出：
```
this is init...
this is main...
```


# 1. 声明&定义
类型名在最前，变量名在前，数据类型在后。

其中，声明最开始的类型包括var, const, type, func。分别对应变量、常亮、类型和函数。

## 1.1 变量

* 变量声明

`var 变量名 数据类型 = 表达式`

`数据类型`和`表达式`可以省略其中的一个。如果省略`类型`，那么将根据初始化表达式来推导。如果`表达式`被省略，那么将用零值初始化该变量(0, false或nil)。

还有一种简短的形式：

`变量名 := 表达式`  （等价于：  `var 变量名 = 表达式`）

```go
//例子
var s, sep string
var i, j, k int
var b, f, s = true, 2.3, "four"
i, j := 0, 1
var f, err = os.Open(name)
```

* 变量指针

`&`和`*`符号的语法和C语言基本一样。

但注意，golang中`*ptr++`和C中`*ptr++`的顺序是相反的，C中的时间顺序是`*(ptr++)`，而golang中指针不变，实际可以看成`(*ptr)++`，即使加括号，golang也不支持像C一样改变指针地址，如下：

```cpp
//C中：
int a = 10;
int *p;
p = &a;
printf("a = %d, p = 0x%x\n", a, p); //output: a = 10, p = 0x5f43fa6c
(*p)++;
printf("a = %d, p = 0x%x\n", a, p); //output: a = 11, p = 0x5f43fa6c
*p++;
printf("a = %d, p = 0x%x\n", a, p); //output: a = 11, p = 0x5f43fa70

```

```go
//golang中：
var a = 10
var p *int
p = &a
fmt.Printf("a = %d, p = 0x%x\n",a, p) //output: a = 10, p = 0xc42006c178
*p++
fmt.Printf("a = %d, p = 0x%x\n",a, p) //output: a = 11, p = 0xc42006c178
```

* 用new创建变量

`new(Type)`返回一个Type类型的指针。

```go
p := new(int) //此时p是个int型指针
*p = 2
fmt.Println(*p)
```

注意：new只是一个预定义的函数，它并不是一个关键字，如果定义了一个变量覆盖了这个名字，作用于内就用不了它了。

## 1.2 类型的定义
应该是相当于类型的别名吧。。。
```go
type 类型名字 底层类型
```
## 1.3 包的声明
* 在一个源文件的最前面，用"package xxx"声明一个包，比如主程序一般用"package main"。package的**某一个**声明前应该包含一个包注释，如果包注释很大，通常会放到一个独立的doc.go文件中。

```go
// Package tempconv performs Celsius and Fahrenheit conversions. （这是包注释，一个包只需要一个就行）
package tempconv //这是包的声明，说明此文件属于tempconv包

```

* 源文件的package后面，import其他的包，一个文件夹下的所有源文件一般是一个包，文件夹名一般要和包名相同。


* 如果一个名字是大写字母开头的，那么该名字是导出的。（类似public的变量/函数？）

* 同一个包中所有文件可以共享各种变量。(类似private？)



# 2. 数据类型

## 2.1 变量和常量

```go
int  int8  int16  int32  int64 		(整形)
uint uint8 uint16 uint32 uint64		(无符号整形)
rune            					(等价于int32，表示一个Unicode字符)
byte								(等价于uint8，强调数值是原始的数据)
float32    float64             		(浮点数)
complex64  complex128				(复数)
bool								(布尔型)
string								(字符串)
const								(常量类型)
```

## 2.2 字符串和数字的转换

* 数字 --> 字符串
两种方法和C语言的思路类似：

```go
x := 123
y := fmt.Sprintf("%d", x)	//方法一
z := strconv.Itoa(x) 		//方法二
fmt.Println(y, z) 			// "123 123"
```

* 字符串 --> 数字

```go
x, err := strconv.Atoi("123")             // x is an int
y, err := strconv.ParseInt("123", 10, 64) // base 10, up to 64 bits
```

## 2.3 复合类型--数组

数组长度固定，不可不变。

* 定义和初始化

```go
//a) 一般定义和初始化
var a [3]int					//定义长度为3的整形数组
var q [3]int = [3]int{1, 2, 3}	//定义并赋值
q := [...]int{1, 2, 3}			//定义并赋值

//b) golang中索引可以使用一个非顺序的索引（类似C的枚举？），如：
const (
    USD Currency = iota // 美元
    EUR                 // 欧元
    RMB                 // 人民币
)
symbol := [...]string{USD: "$", EUR: "€", RMB: "￥"}
fmt.Println(RMB, symbol[RMB]) 	// "3 ￥"

//c) 定义一个第100个元素为-1的数组，其它元素初始化为0，长度为100
r := [...]int{99: -1}
```

* 数组长度

```go
len(a)
```

* 数组指针

```go
//例子： 用于给[32]byte类型的数组清零的两个函数
func zero(ptr *[32]byte) {
    for i := range ptr {
        ptr[i] = 0
    }
}
func zero2(ptr *[32]byte) {
    *ptr = [32]byte{}
}
```


* 数组切片Slice

```go
//类似于Python的切片
slice_a = a[:]
slice_b = a[3:5]

// append(slice_name, element)
var runes []rune
for _, r := range "Hello, 世界" {
    runes = append(runes, r)
}
fmt.Printf("%q\n", runes) // "['H' 'e' 'l' 'l' 'o' ',' ' ' '世' '界']"
```



## 2.4 复合类型--Map（/Map/结构体/JSON/文本和HTML模板)

key/value类型: `map[Key_TYPE]Value_TYPE`

* 创建：

```go
//用make函数
ages := make(map[string]int) // mapping from strings to ints

//用字面值赋值创建
ages := map[string]int{
    "alice":   31,
    "charlie": 34,
}

```

* 操作和方法

delete 方法用于删除某对值：
```go
delete(ages, "alice")
```

查找某对值失败不会错误，而会返回0。

Map的元素不能被取地址(原因是map可能随着元素数量的增长而重新分配更大的内存空间，从而可能导致之前的地址无效)。

## 2.5 复合类型--结构体类型

结构体类型的定义和结构体变量的定义：
```go
type Point struct {
	X, Y int
}

var foo Point
foo = new(Point)
foo := Point{1, 2}
```

和C/C+\+相同的是可以通过点来使用一个对象的某个成员，同时golang的点C对指向对象的指针同样起作用，可以和C/C++的"->"起到一样的作用。

* 匿名成员

golang可以在一个结构体中包含另一个结构体的类型名，这样就相当于直接包含了这种类型的所有变量。(但是这种匿名成员无法用剪短的字面值列表来初始化)如：

```go
type Circle struct {
    Point
    Radius int
}

type Wheel struct {
    Circle
    Spokes int
}

var w Wheel
w.X = 8            // equivalent to w.Circle.Point.X = 8
w.Y = 8            // equivalent to w.Circle.Point.Y = 8
w.Radius = 5       // equivalent to w.Circle.Radius = 5
w.Spokes = 20
```

## 2.6 复合类型--JSON等

> http://docs.ruanjiadeng.com/gopl-zh/ch4/ch4-05.html
> 标准库中的encoding/json、encoding/xml、encoding/asn1等包支持对应的信息发送和接收协议。
> 
> JSON是对JavaScript中各种类型的值——字符串、数字、布尔值和对象——Unicode本文编码。它可以用有效可读的方式表示第三章的基础数据类型和本章的数组、slice、结构体和map等聚合数据类型。
>
> 基本的JSON类型有数字（十进制或科学记数法）、布尔值（true或false）、字符串，其中字符串是以双引号包含的Unicode字符序列，支持和Go语言类似的反斜杠转义特性，不过JSON使用的是\Uhhhh转义数字来表示一个UTF-16编码（译注：UTF-16和UTF-8一样是一种变长的编码，有些Unicode码点较大的字符需要用4个字节表示；而且UTF-16还有大端和小端的问题），而不是Go语言的rune类型。
>
> 这些基础类型可以通过JSON的数组和对象类型进行递归组合。一个JSON数组是一个有序的值序列，写在一个方括号中并以逗号分隔；一个JSON数组可以用于编码Go语言的数组和slice。一个JSON对象是一个字符串到值的映射，写成以系列的name:value对形式，用花括号包含并以逗号分隔；JSON的对象类型可以用于编码Go语言的map类型（key类型是字符串）和结构体。例如：
>
> ```go
> boolean         true
number          -273.15
string          "She said \"Hello, BF\""
array           ["gold", "silver", "bronze"]
object          {"year": 1980,
                 "event": "archery",
                 "medals": ["gold", "silver", "bronze"]}`
```
>
> 将一个Go语言中类似movies的结构体slice转为JSON的过程叫编组（marshaling）。编组通过调用json.Marshal函数完成；json.MarshalIndent函数将产生整齐缩进的输出。
>
> 在早些的例子中，我们使用了json.Unmarshal函数来将JSON格式的字符串解码为字节slice。但是这个例子中，我们使用了基于流式的解码器json.Decoder，它可以从一个输入流解码JSON数据，尽管这不是必须的。如您所料，还有一个针对输出流的json.Encoder编码对象。

## 2.7 复合类型--文本和HTML模板

> http://docs.ruanjiadeng.com/gopl-zh/ch4/ch4-06.html



# 3. 函数

## 3.1 函数定义格式：

```go
func 函数名(形参列表) (返回参数列表) {
    函数体
}
```
> 你可能会偶尔遇到没有函数体的函数声明，这表示该函数不是以Go实现的。这样的声明定义了函数标识符。

> ```go
> package math

> func Sin(x float64) float //implemented in assembly language
> ```

## 3.2 支持匿名函数(闭包)

> http://docs.ruanjiadeng.com/gopl-zh/ch5/ch5-06.html

## 3.3 支持可变参数

要声明可变的函数参数，要在参数类型之前加`...`，此时，如果是多个参数，形参会被视为切片数组。如果多个参数已经是切片，可以在要传入函数的实参名后加`...`。例如：

```go
func sum(vals...int) int {
    total := 0
    for _, val := range vals {
        total += val
    }
    return total
}
fmt.Println(sum(1, 2, 3, 4)) // "10" (实参的多个参数 --> 形参的切片)
values := []int{1, 2, 3, 4}
fmt.Println(sum(values...)) // "10" (实参切片加... --> 形参还是切片)
```

> 函数名的后缀f是一种通用的命名规范，代表该可变参数函数可以接收Printf风格的格式化字符串。

## 3.4 函数中的defer语句

前面带有`defer`的语句，在return或panic结束函数后才执行。对于多个return出口前要完成关闭文件等操作的情况很好用；在打开/关闭文件或加锁/开锁这种成对的操作也很好用：

```go
//open和close紧挨着，close使用defer
package ioutil
func ReadFile(filename string) ([]byte, error) {
    f, err := os.Open(filename)
    if err != nil {
        return nil, err
    }
    defer f.Close()
    return ReadAll(f)
}

//加锁和开锁紧挨着，开锁使用了defer
var mu sync.Mutex
var m = make(map[string]int)
func lookup(key string) int {
    mu.Lock()
    defer mu.Unlock()
    return m[key]
}
```

## 3.5 Panic异常及异常捕获

数组访问越界、空指针引用等。这些运行时错误会引起painc异常。

...

> http://docs.ruanjiadeng.com/gopl-zh/ch5/ch5-10.html


# 4. 方法

在一个函数声明前加上一个变量，就是一个方法。如：

```go
type Point struct{ X, Y float64 }
// 传统的函数
func Distance(p, q Point) float64 {
    return math.Hypot(q.X-p.X, q.Y-p.Y)
}
// 等价于上一函数功能的方法
func (p Point) Distance(q Point) float64 {
    return math.Hypot(q.X-p.X, q.Y-p.Y)
}
```

这里的Distance方法属于Point类，而p是一个receiver(类似于其他语言的this或self)，receiver应尽量简短，所以这里选取了类名的第一个字母p。

用这种方式，golang的各种类型都可添加方法，如数值、字符串、map等都可以，**只有指针和interface除外** 。

#


# 杂项

> 1. golang.org/x/... 目录下存储了一些由Go团队设计、维护，对网络编程、国际化文件处理、移动平台、图像处理、加密解密、开发者工具提供支持的扩展包。未将这些扩展包加入到标准库原因有二，一是部分包仍在开发中，二是对大多数Go语言的开发者而言，扩展包提供的功能很少被使用。



