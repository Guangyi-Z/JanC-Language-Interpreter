##Simple C-like Langauge Compiler

###Features

1. Arithmetics
2. Relational Logic
3. Expression & Assignment
3. Type Inference
7. Basic Types: Int, Double, String, Array
4. Function: func
5. if-elseif-else
6. while

For functions, you are allowed to pass or return the reference to variables, array, and functions.

Built-in Operation on String

####Difficult Points

1. Expression Parsing- unary oeprations
2. Expression Interpreting- factor types
    * Prefix & Suffix OP
    * Direct Ref to functions or arrays
3. Symbol Table Design

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

###Features To Do

1. Comment
2. Relational Logic
