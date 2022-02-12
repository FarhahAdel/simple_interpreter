# simple Interpreter

Program accepts a text file with input expressions, Then the program evalutes these expressions and display values of each variable.
Expressopn evaluation is done by converting it from infix to postfix  notations using stacks.

**Sample input**
```
x=12.5
y=x*4/5
z=x*y/5
M=Z*-2
k=10.5+(z-2.5)/(x+y)
```

**Output**

*Sorted by variable name*
```
k=11.5
M=-50
x=12.5
y=10
z=25
```
*Sorted by value*
```
m=-50
y=10
k=11.5
x=12.5
z=25
```

