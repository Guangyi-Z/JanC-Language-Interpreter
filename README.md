##JanC Language Interpreter

This interpreter is purely written in C++11.
And, MEMORY LEAK is not ensured!
You say what? GC is not supported in C++? WTF!&^%$#@!%..

###Compilation and Usage

Under the root directory of the project.

Compilation requires ``cmake`` tool:

```bash
mkdir build && cd build
cmake ..
make
```

Run the interpreter after compilation:

```bash
./run
```

Uasge promopt will guide you all the way.

```
➜  build git:(master) ✗ ./run 
Welcome to JanC Interpreter!

Usage:
1. load FILENAME.janc
2. quit

>> 
```

###JanC Langauge

This page focuses on the Language features and code demo.
For the architecture design details, please follow [this link](https://github.com/JanFan/JanC-Language-Interpreter/blob/master/doc/arch.md)

Why is it called “JanC”?
Because it’s syntax style is heavily copied from the C language, 
and...“Jan” is my English name :)

I’m gonna show you the brief introduction to the language features, 
and then many small easy code snippets follow to give you concrete impressions.

####Grammar

```
Program     :: = Statement*
Statement   :: = ST_Block | ST_Var; | ST_Expression; | ST_Func | ST_If | ST_While | ST_Return; | ST_Continue; | ST_Break;
ST_Block    :: = "{" Statement* "}"
ST_Var      :: = var ID ("["Int”]”)? (= Constant)? ;
ST_Func     :: = func ID “(“ (ID,)* “)” ST_Block
ST_If       :: = if “(“ST_Expression”)” Statement (elseif (ST_Expression) Statement)* (else Statement)?
ST_While    :: = while “(“ST_Expression”)” Statement
ST_Return   :: = return ST_Expression
ST_Continue :: = continue
ST_Break    :: = break
ID          :: = String
Constant    :: = Basic | Array
Array       :: = "{" (Basic,)? "}"
Basic       :: = String | Int | Double | Bool
```


####Features

1. Basic Types: Bool, Int, Double, String, Array
2. Operators
    1. Arithmetics
        * Binary op
            * +, -, \*, /
        * Unary op
            * +, -, ++, --
    2. Relation
        * >, >=, <, <=, ==, !=
    3. Logic
        * &&, ||, !
    4. Assignment
        * =
3. Expression
4. Variables: ``var`` with Type Inference
5. Function: ``func``
6. ``if``-``elseif``-``else``
7. ``while``

Features To Do:

1. Comment
2. return ref from functions (abstract the id of Reference into Reference itself)

####Data Types and Operators

**Bool**

```js
var b = true;
if (b)
    b = false;
print(b);
print(!b);
```

```
false
true
```

**Int**

```js
var num = 4;
print(++num);
print(num++);
print(num);
num = num / 2;
print(+num);
print(-num);
```

```
5
5
6
3
-3
```

**Double**

```js
num = 2.5;
print(num);
```

```
3.5
```

**String**

```js
var str = "hello";
print(str, "world");
str = str + " world";
print(str);
var secp = "\"\"\"";
print (secp);
```

```
"hello" "world"
"hello world"
"""""
```

**Array**

Array elements are not restricted to one specific type.
You can mix up elements of several types in one Array.

```js
var arr[] = {true, 1, 2.5, "string"};
print("len:", len(arr));
print(arr);
arr[0] = false;
print(arr[0]);
```

```
"len:" 4
[true, 1, 2.5, "string", ]
false
```

You can run the code sample above, ``type.janc``, which can be found in ``doc`` directory.

```bash
>> load ../doc/type.janc
false
true
5
5
6
3
-3
3.5
"hello" "world"
"hello world"
"""""
"len:" 4
[true, 1, 2.5, "string", ]
false
```

####If-elseif-else

The code block within the conditional structure can be surrounded be curly brace ``{...}``, or simply use a single statement ending with ``;``

```js
func test_if(i) {
    if (i == 1) {
        print(1);
    }
    elseif (i == 2) {
        print (2);
    }
    else {
        print ("neither 1 nor 2");
    }
}

test_if(1);
test_if(2);
test_if(3);
```

```
>> load ../doc/ifs.janc
1
2
"neither 1 nor 2"
```

####while

Surely, you can use ``break`` and ``continue`` as you are used to do.

```js
var cnt = 0;
while(true) {
    cnt++;
    if (cnt <= 3) {
        print(cnt);
        continue;
    }
    break;
}
```

```
load ../doc/while.janc
1
2
3
```

####func

As you can see above, functions are defined with keyword ``func``.
It’s able to accept literals, variables, arrays as it’s parameters, as well as it’s return value;

Also, currently there are only two **Built-in Functions** supported- ``len(ARRAY)`` and ``print(...)``, 
whose meanings are quite self-explanatory.

```js
func add (x, y) {
    return x+y;
}

print(add(1, 1));
print(add(1, 2.5));
print(add("hello", " world"));
```

```
>> load ../doc/func.janc
2
3.5
"hello world"
```

###Extra Notes

* Variables and Functions must be declared and defined before used.
* Array size can be declared explicitly, and they will be set as ``0`` if not initialized.

```js
var arr[5] = {1,2,3};
print("len:", len(arr), arr);
arr[4] = 4;
print(arr[4]);
```

```
>> load ../doc/array.janc
"len:" 5 [1, 2, 3, 0, 0, ]
4
```

* For String, ``"`` is available by escaping ``\"``
* For Expression, ``()`` can be added to enforce precedence, 
otherwise the expressions are evaluated by the default precedence of operations, same as C.

###The End

We’d end with a complete program written in JanC- Bubble Sort :-P

```js
func bubble_sort(arr) {
    var l = len(arr);
    var beg = 0;
    while(beg < l) {
        var cur = l-1;
        while(cur > beg) {
            if (arr[cur] < arr[cur-1]) {
                var tmp = arr[cur];
                arr[cur] = arr[cur-1];
                arr[cur-1] = tmp;
            }
            cur--;
        }
        beg++;
    }
}

var ls[] = {5,2,5,3,7,1,10};
bubble_sort(ls);
print(ls);
```

```
>> load ../doc/bubble.janc
[1, 2, 3, 5, 5, 7, 10, ]
```
