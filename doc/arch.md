##Architecture

###Grammar

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

###System Architecture

####Modules Dependency

```
                     ┌────────────┐                     
                     │     op     │                     
                     └────────────┘                     
                            ▲                           
       ┌────────────────────┼────────────────────┐      
       │                    │                    │      
       │                    │                    │      
┌────────────┐       ┌────────────┐       ┌────────────┐
│    type    │       │    ast     │       │   lexer    │
└────────────┘       └────────────┘       └────────────┘
       ▲                    ▲                    ▲      
       ├────────────────────┼────────────────────┘      
       │                    │                           
┌────────────┐       ┌────────────┐                     
│   symbol   │       │   parser   │                     
└────────────┘       └────────────┘                     
       ▲                    ▲                           
       └────────────────────┤                           
                            │                           
                     ┌────────────┐                     
                     │interpreter │                     
                     └────────────┘                     
```

####type Module

```
┌────────────┐    
│  Constant  │    
└────────────┘    
    ┌────────────┐
    │    Int     │
    └────────────┘
    ┌────────────┐
    │   Double   │
    └────────────┘
    ┌────────────┐
    │   String   │
    └────────────┘
    ┌────────────┐
    │   Array    │
    └────────────┘
    ┌────────────┐
    │    Bool    │
    └────────────┘
    ┌────────────┐
    │    Ref     │
    └────────────┘
```

####Abstract Syntax Tree


```
┌───────────────┐    
│ AST_Statement │    
└───────────────┘    
    ┌───────────────┐
    │   AST_Block   │
    └───────────────┘
    ┌───────────────┐
    │    AST_Var    │
    └───────────────┘
    ┌───────────────┐
    │   AST_Array   │
    └───────────────┘
    ┌───────────────┐
    │   AST_Func    │
    └───────────────┘
    ┌───────────────┐
    │AST_Expression │
    └───────────────┘
    ┌───────────────┐
    │  AST_Return   │
    └───────────────┘
    ┌───────────────┐
    │    AST_If     │
    └───────────────┘
    ┌───────────────┐
    │   AST_While   │
    └───────────────┘
```


####Expression

```
┌──────────────┐        
│AST_Expression│        
└──────────────┘        
    ┌──────────────────┐
    │e1: AST_Expression│
    └──────────────────┘
    ┌──────────────────┐
    │e2: AST_Expression│
    └──────────────────┘
    ┌─────────────┐     
    │   op: OP    │     
    └─────────────┘     
    ┌─────────────┐     
    │is_leaf: bool│     
    └─────────────┘     
    ┌─────────────┐     
    │ o: Operand  │     
    └─────────────┘     
```

```
┌─────────────┐                                 
│   Operand   │                                 
└─────────────┘                                 
   ┌─────────────┐ ┌─────────────┐              
   │   Literal   │ │  Constant   │              
   └─────────────┘ └─────────────┘              
   ┌─────────────┐ ┌─────────────┐              
   │  Reference  │ │ id: String  │              
   └─────────────┘ └─────────────┘              
       ┌─────────────┐ ┌─────────────────────┐  
       │   FuncVar   │ │ parameters: vector  │  
       └─────────────┘ │  <AST_Expression*>  │  
                       └─────────────────────┘  
       ┌─────────────┐ ┌───────────────────────┐
       │  RefArray   │ │index: AST_Expression* │
       └─────────────┘ └───────────────────────┘
```

####Interpreter

```
┌─────────────┐                    
│ Controller  │                    
└─────────────┘                    
     ┌───────────────────┐         
     │InterpreterInstance│         
     └───────────────────┘         
          ┌─────────────┐          
          │ SymbolTable │          
          └─────────────┘          
          ┌─────────────┐          
          │  FuncTable  │          
          └─────────────┘          
          ┌───────────────────────┐
          │Interpreter<Util Class>│
          └───────────────────────┘
```

```
┌───────────────────────┐
│Interpreter<Util Class>│
└───────────────────────┘
      ┌─────────────┐                                
      │IntrStatement│                                
      └─────────────┘                                
           ┌─────────────┐                           
           │   IntrVar   │                           
           └─────────────┘                           
           ┌──────────────┐                          
           │   IntrFunc   │                          
           └──────────────┘                          
           ┌──────────────┐                          
           │  IntrBlock   │                          
           └──────────────┘                          
           ┌──────────────┐                          
           │    IntrIf    │                          
           └──────────────┘                          
           ┌──────────────┐                          
           │  IntrWhile   │                          
           └──────────────┘                          
           ┌──────────────┐                          
           │IntrExpression│                          
           └──────────────┘                          
                ┌──────────────┐                     
                │ IntrOperand  │                     
                └──────────────┘                     
                     ┌─────────────────┐             
                     │ OperandHandler  │             
                     └─────────────────┘             
                          ┌─────────────────────────┐
                          │IntrOperand() : Constant │
                          └─────────────────────────┘
```

```
┌───────────────────────┐  
│ OperandHandlerFactory │  
└───────────────────────┘  
     ┌─────────────────┐   
     │ OperandHandler  │   
     └─────────────────┘   
          ┌──────────────┐ 
          │LiteralHandler│ 
          └──────────────┘ 
          ┌─────────────┐  
          │ReferenceHand│  
          └─────────────┘  
          ┌──────────────┐ 
          │RefFuncHandler│ 
          └──────────────┘ 
          ┌───────────────┐
          │RefArrayHandler│
          └───────────────┘
```

###Difficult Points

1. State Machine in Tokenizer
2. Rescent-Recursive Parser
3. Expression Interpretation
    * Unary oeprations
    * Direct Ref to functions or arrays
    * Operand Design
3. Symbol Table Design
4. Function’s return & While’s break and continue


