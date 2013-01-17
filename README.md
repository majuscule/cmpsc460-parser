## Homework 1

A REPL interpreter for arithmetic expressions and IF statements.

### Syntax:
- an expression has the following form: (number number operator)
  - will return the value of calculated by applying the operator to the operands
- an arithmetic IF statement has the following form: IF exp1 exp2 exp3 exp4
  - will return the value of exp2, exp3 or exp4, respectively, if exp1 is negative, equal to zero, or positive

### Examples:

    $ c++ hw.cpp && ./a.out
    > (5 2 +)
    7
    > (5 2 x)
    10
    > IF (2 -2 +) (5 2 +) (5 -2 x) (5 2 x)
    -10
    > ^C

