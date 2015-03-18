##Simple C-like Langauge Compiler

###Grammar

```
Statement :: = ; | Block
Block     :: = {Statement*}
/* declaration */
DefVar ::= var ID [Num]?
DefFunc ::= func ID ((ID,)*) Block

Exp ::= SubExp [+-] Subexp
Subexp ::= Num [*/] Num
```
