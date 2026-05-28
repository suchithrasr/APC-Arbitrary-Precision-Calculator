Arbitrary Precision Calculator (APC)
A command-line calculator written in C that performs arithmetic operations — addition, subtraction, multiplication, and division — on integers of any size, far beyond the 64-bit limit of standard C data types.
Each number is stored digit-by-digit in a Doubly Linked List, enabling precise computation through manual digit-level arithmetic.

Features

Addition of arbitrarily large integers
Subtraction with correct sign and borrow handling
Multiplication using long-multiplication with partial products
Division using repeated subtraction (returns integer quotient)
Full support for negative numbers (- sign prefix)
Division-by-zero detection with error message
Leading zero removal from results
Complete memory cleanup after every operation


Data Structure
Doubly Linked List (Dlist)

head → [d1] ↔ [d2] ↔ [d3] ↔ ... ↔ [dn] ← tail
        MSB                            LSB

Each node stores ONE digit.
Arithmetic traversal goes tail → head (LSB to MSB).
Result digits are inserted at front to maintain correct order.

Project Structure
apc/
├── apc.h             # Dlist struct definition + all function prototypes
├── main.c            # CLI argument parsing, sign detection, operator dispatch
├── apc.c             # Core list utilities: insert, delete, compare, print
├── addition.c        # Tail-to-head addition with carry
├── subtraction.c     # Tail-to-head subtraction with borrow
├── multiplication.c  # Long multiplication with partial product accumulation
├── division.c        # Repeated subtraction-based integer division
└── Makefile

Build & Run
Compile
bashmake
Usage
bash./apc <operand1> <operator> <operand2>
Operators supported
SymbolOperation+Addition-Subtraction*MultiplicationxMultiplication (alternate)/Division

Note: Wrap * in quotes to prevent shell expansion: ./apc 99 '*' 99


Sample Test Cases
Addition
bash./apc 10 + 20           # → 30
./apc 999 + 1           # → 1000
./apc -10 + -20         # → -30
./apc -10 + 5           # → -5
./apc 0 + 0             # → 0
Subtraction
bash./apc 50 - 20           # → 30
./apc 1000 - 1          # → 999
./apc 20 - 50           # → -30
./apc 123 - 123         # → 0
./apc -50 - 20          # → -70
Multiplication
bash./apc 5 '*' 4           # → 20
./apc 99 '*' 99         # → 9801
./apc 0 '*' 123         # → 0
./apc -10 '*' 5         # → -50
./apc -10 '*' -5        # → 50
Division
bash./apc 100 / 5           # → 20
./apc 7 / 2             # → 3
./apc 5 / 10            # → 0
./apc -20 / 5           # → -4
./apc 10 / 0            # → Division failed (division by zero)

How Each Operation Works
Addition

Traverse both lists from tail → head (LSB first)
At each step: sum = d1 + d2 + carry, store sum % 10, update carry = sum / 10
Insert each result digit at the front of the result list
Loop continues while either list has digits OR carry is non-zero (handles 999 + 1 → 1000)

Subtraction

Assumes head1 >= head2 (caller ensures this via compare_list())
Traverse from tail → head with borrow tracking
If d1 < d2: borrow from next digit (d1 += 10, borrow = 1)

Multiplication

For each digit of operand2 (tail → head), multiply against all digits of operand1
Each partial product gets positional zero-padding (place value)
Partial products are accumulated using the addition function

Division

Checks for zero divisor before starting
If dividend < divisor: quotient is 0
Repeatedly subtracts divisor from dividend, counting iterations
Count is converted to a digit list as the quotient

Sign Handling

Signs are detected from the leading - character before list conversion
For A - B: internally converts to A + (-B) by flipping sign2
Result sign is negative only if signs differ (for * and /) or as computed (for + and -)
-0 is printed as 0


Memory Management
Every code path (including error paths like division by zero) calls delete_list() on all three lists (head1/tail1, head2/tail2, headR/tailR) before returning. No memory leaks.

Clean Build
bashmake clean

Author
Suchithra S
B.E. ECE — Gopalan College of Engineering & Management, VTU (2025)
Advanced Embedded Systems Training — Emertxe Information Technologies, Bengaluru