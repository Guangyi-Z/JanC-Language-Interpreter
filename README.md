##Simple C-like Langauge Compiler

###Features

7. Basic Types: Int, Double, String, Array
1. Arithmetics
    * +, -, \*, /
    * >, >=, <, <=, ==, !=
2. Relational Logic
    * &&, ||, !
3. Expression & Assignment
3. Type Inference
4. Function: func
5. if-elseif-else
6. while
8. Comment: ``\\``

For functions, you are allowed to pass constants or references to variables, arrays, and functions.
While only references to arrays and functions are not supported in terms of the return type of functions so far.
``return`` statement can only be used in the main block of the function.

Built-in Operation on String

Array usage.
Besides, Array elements are not restricted to one specific type.
You can mix up elements of several types in one Array.

```
var arr[5] = {1,2,3};   // default as 0
arr.len();  // 5
arr[4] = 4;
```

String
``”`` is available by escape character.

``var``
Variables that have not been initialized is not allowed to used.

Expression.
``()`` can be added to enforce precedence, otherwise the expressions are evaluated by the default precedence of operations.


###Features To Do

1. Comment
2. arbitrary return in functions
3. ref pass in functions
4. mixed type elements in Array
5. unary operations

####Difficult Points

1. Expression Parsing- unary oeprations
2. Expression Interpreting- factor types
    * Prefix & Suffix OP
    * Direct Ref to functions or arrays
3. Symbol Table Design
4. decouple IntrStatment and IntrExpression
5. split SymbolTable with Interpreter?

###Grammar

```
var arr[5] = {1,2,3,4,5};
var a = 1;
// var arr[5] = {1,1+1,3,4,5};
// a = 1+1;
```

``var`` can only be initialized with literals value, not expression.

```
Statement :: = ; | Block
Block     :: = {Statement*}
/* declaration */
DefVar ::= var ID [Num]?
DefFunc ::= func ID ((ID,)*) Block

Exp ::= SubExp [+-] Subexp
Subexp ::= Num [*/] Num
```

```
                ┌───────────┐                           
                │    Int    │                           
                └───────────┘                           
                ┌───────────┐                           
                │  Double   │                           
                └───────────┘                           
                ┌───────────┐                           
  ┌───────────┐ │   Char    │                           
  │ Constant  │ └───────────┘                           
  └───────────┘ ┌───────────┐                           
                │  String   │                           
                └───────────┘                           
                ┌───────────┐                           
                │ Array_Int │                           
                └───────────┘                           
                ┌────────────┐                          
                │Array_Double│                          
                └────────────┘                          
                                                        
                                                        
                                                        
                ┌───────────┐ ┌───────────┐             
                │   Index   │ │ Constant  │             
  ┌───────────┐ └───────────┘ └───────────┘             
  │  Operand  │ ┌───────────┐ ┌───────────┐             
  └───────────┘ │Parameters │ │   Func    │             
                └───────────┘ └───────────┘             
                                                        
                                                        
                ┌───────────┐ ┌───────────┐             
  ┌───────────┐ │Symbol_Var │ │ Constant  │             
  │  Symbol   │ └───────────┘ └───────────┘             
  └───────────┘ ┌───────────┐ ┌───────────┐             
                │Symbol_Func│ │   Func    │             
                └───────────┘ └───────────┘             
                                                        
                                                        
                ┌───────────┐                           
                │    Var    │                           
                └───────────┘                           
  ┌───────────┐ ┌───────────┐ ┌───────────┐             
  │ Statement │ │   Func    │ │   Block   │             
  └───────────┘ └───────────┘ └───────────┘             
                ┌───────────┐ ┌───────────┐┌───────────┐
                │Expression │ │  Operand  ││Expression │
                └───────────┘ └───────────┘└───────────┘
                ┌───────────┐                           
                │   Block   │                           
                └───────────┘                           
```


```
                                    ┌─────────────┐                                          
                                    │  Constant   │                                          
                   ┌─────────────┐  └─────────────┘                                          
                 ┌─│   ST_Var    │  ┌─────────────┐                                          
                 │ └─────────────┘  │     ID      │                                          
                 │                  └─────────────┘                                          
                 │                                                                           
                 │                  ┌─────────────┐                                          
                 │ ┌─────────────┐  │  ST_Block   │                                          
                 ├─│   ST_Func   │  └─────────────┘                                          
                 │ └─────────────┘  ┌─────────────┐                                          
                 │                  │     ID      │                                          
  ┌─────────────┐│                  └─────────────┘                                          
  │  Statement  ├┤                                                                           
  └─────────────┘│                  ┌─────────────┐ │ ┌─────────────┐                        
                 │                  │ST_Expression│ │ │  Constant   │                        
                 │                  └─────────────┘ │ └─────────────┘  is_leaf               
                 │ ┌─────────────┐  ┌─────────────┐ │ ┌─────────────┐                        
                 ├─│ST_Expression│  │     OP      │ │ │     ID      │  ID->Symbol Table      
                 │ └─────────────┘  └─────────────┘ │ └─────────────┘                        
                 │                  ┌─────────────┐ │ ┌─────────────┐ ┌──────────────┐       
                 │                  │ST_Expression│ │ │ Parameters  │ │ST_Expression*│       
                 │                  └─────────────┘ │ └─────────────┘ └──────────────┘       
                 │                                                                           
                 │ ┌─────────────┐  ┌─────────────┐                                          
                 └─│  ST_Block   │  │ Statement*  │                                          
                   └─────────────┘  └─────────────┘                                          
```
