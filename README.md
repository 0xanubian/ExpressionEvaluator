## ExpressionEvaluator

This program takes the whole expression from user as input and prints the result.

It uses Recursive Desccent Parsing to parse and evaluate the expression.

### Grammar
```
Expression   ::= Term (('+' | '-') Term)*
Term         ::= Factor (('*' | '/') Factor)*
Factor       ::= Number | '(' Expression ')'
Number       ::= [0-9]+ ('.' [0-9]*)?
```

## Features
- It can evaluate addition, subtraction, multiplication and division with integers and decimals.
- It follows the BODMAS rule.

## Issues
- It can't warn/point the user if they give a invalid input.

```
>>> 5.8_ - 90
5.800000
```
