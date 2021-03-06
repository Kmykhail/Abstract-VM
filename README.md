# Abstract-VM
Goal of this project is create a simple virtual machine that can interpret programs written in a basic assembly language.</br>
It's very simple vitrtual machine, which will run some basic arithemetic programs coded in a very basic assembly language.</br>
##### Abstract is composed of a series of instructions:
  `push int[8|16|32] | float | double(value)`: Push the value at the top of the stack.</br>
  `pop`: Unstack the value from the top of the stack. If the stack is empty, the program execution must stop with an error.</br>
  `dump`: Displays each value of the stack, from the most recent one to the oldest value.</br>
  `assert int[8|16|32] | float | double(value)`: Asserts that the value at the top of the stack is equal to the one passed as    parameter for this instruction.</br>
  `add`: Unstacks the first two values on the stack, adds them together and stacks the result.</br>
  `sub`: Unstacks the first two values on the stack, subtracts them, then stacks the result.</br>
  `mul`: Unstacks the first two values on the stack, multiplies them, then stacks the result.</br>
  `div`: Unstacks the first two values on the stack, divides them, then stacks the result.</br>
  `mod`: Unstacks the first two values on the stack, calculates the modulus, then stacks the result.</br>
  `print`: Asserts that the value at the top of the stack is an 8-bit integer.</br>
  `exit`: Terminate the execution of the current program.</br>
 ##### Exceptions:
  1. Problems reading files</br>
  2. When use arithmetic instructions, stack must contain at least 2 values, otherwise I catch an exception and continue reading to the end of the file</br>
  3. Type overflow</br>
  4. Division by zero

### Compiling:
  `$> make`
### Usage:
  [`./avm` without parameters: reading from standard input]</br>
  [`./avm [some file]`]
### Example:
```
; -------------
; exemple.avm -
; -------------
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
```
