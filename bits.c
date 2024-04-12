/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
  return ~((~x) | (~y));
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n)
{
  int mask = 0xff;
  return (x >> (n << 3)) & mask;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n)
{
  int mask = (1 << 31) >> n << 1; // Create mask to clear sign bits after logical shift
  return (x >> n) & ~mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
  // Creating masks for counting bits in different positions
  int _mask1 = (0x55) | ((0x55) << 8);
  int _mask2 = (0x33) | ((0x33) << 8);
  int _mask3 = (0x0f) | ((0x0f) << 8);
  // Combining masks to cover 16-bit chunks
  int mask1 = (_mask1) | (_mask1 << 16);
  int mask2 = (_mask2) | (_mask2 << 16);
  // Masks for 8-bit chunks
  int mask3 = (_mask3) | (_mask3 << 16);
  int mask4 = (0xff) | (0xff << 16);
  int mask5 = (0xff) | (0xff << 8);
  // Counting bits in x using masks
  int ans = (x & mask1) + ((x >> 1) & mask1);
  ans = (ans & mask2) + ((ans >> 2) & mask2);
  ans = (ans & mask3) + ((ans >> 4) & mask3);
  ans = (ans & mask4) + ((ans >> 8) & mask4);
  ans = (ans & mask5) + ((ans >> 16) & mask5);
  return ans;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x)
{
  /*
   * We check if x is zero or non-zero without using the ! operator.
   * If x is non-zero, its most significant bit or its complement's will be 1.
   * We bitwise OR x with its complement and right shift by 31 to get -1 or 0.
   * Finally, we add 1 to get the desired output: 1 if x is zero, and 0 if x is non-zero.
   */
  return ((x | (~x + 1)) >> 31) + 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  /*
   * The minimum two's complement integer has a 1 in the most significant bit
   * and 0s in all other bits.
   * We can achieve this by left shifting 1 by 31 bits.
   */
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
  int sign = x >> 31;                // Sign of x (1 for negative, 0 for non-negative)
  int bias = sign & ((1 << n) + ~0); // Bias to adjust rounding for negative numbers
  int mask = ~(sign);                // Mask for non-negative numbers
  return ((x + bias) >> n) & mask;   // Perform arithmetic right shift and adjust for negative numbers
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n)
{
  int sign = x >> 31;                // Sign of x (1 for negative, 0 for non-negative)
  int bias = sign & ((1 << n) + ~0); // Bias to adjust rounding for negative numbers
  return (x + bias) >> n;            // Perform arithmetic right shift and adjust for negative numbers
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  // Handle special case when x is the minimum two's complement integer
  if (x == 0x80000000)
  {
    return x;
  }
  // For all other cases, take one's complement of x and add 1
  return (~x) + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
  /*
   * We use a double negation to check if x is not zero.
   * If x is not zero, the inner negation (!) will result in 0, and the outer negation (!) will result in 1.
   * We also check if the sign bit of x is not set (i.e., if x is positive) using right shift and bitwise AND.
   * If the sign bit is not set, the expression (x >> 31) & 0x1 will result in 0, otherwise, it will be non-zero.
   * We use logical AND (&) to combine the results of the two checks.
   * If both conditions are true (x is not zero and positive), the result will be 1, otherwise, it will be 0.
   */
  return !(!(x)) & !((x >> 31) & (0x1));
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  /*
   * Compute the sign difference between x and y by evaluating (x - y).
   * If x is less than or equal to y, (x - y) will be non-negative.
   * Use double negation (!!) to convert the result to 0 for non-negative and 1 for negative.
   * Combine the sign of x and y with the sign difference using bitwise AND.
   * If x is negative and y is non-negative, the result will be 1 regardless of the sign difference.
   * If both x and y have the same sign, the result will depend on the sign difference.
   */
  int val = !!((x + ~y) >> 31);
  x = x >> 31;
  y = y >> 31;
  return (!!x | !y) & ((!!x & !y) | (val));
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x)
{
  /*
   * Binary search to find the position of the highest set bit in x.
   */
  int ans = 0;
  ans = (!!(x >> (16))) << 4;
  ans = ans + ((!!(x >> (8 + ans))) << 3);
  ans = ans + ((!!(x >> (4 + ans))) << 2);
  ans = ans + ((!!(x >> (2 + ans))) << 1);
  ans = ans + ((!!(x >> (1 + ans))) << 0);
  return ans;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf)
{
  /*
   * Check if the argument is NaN, return argument if true.
   * Otherwise, toggle the sign bit to get the bit-level equivalent of -f.
   */
  int c = 0x00ffffff;
  if (((uf << 1) ^ (0xffffffff)) < c)
  {
    return uf;
  }
  else
  {
    return uf ^ (0x80000000);
  }
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x)
{
  /*
   * Convert integer x to its bit-level representation as a single-precision floating point value.
   */
  int n = 0xffffffff;        // Exponent mask
  int e = 0;                 // Exponent
  int tmp = 0;               // Temporary variable
  int tmp2 = 0;              // Temporary variable
  int cp = 0;                // Comparison variable
  int cp2 = 0;               // Comparison variable
  int sign = x & 0x80000000; // Sign bit (0x80000000 or 0x0)

  if (x == 0x80000000)
  {
    return 0xcf000000; // Special case for minimum negative integer
  }
  if (x == 0)
  {
    return 0; // Special case for zero
  }
  if (sign)
  {
    x = -x; // Make x positive
  }

  x = x & 0x7fffffff; // Remove sign bit
  tmp = x;
  while (tmp)
  {
    tmp = tmp >> 1;
    n++;
  }

  x = x - (0x1 << n); // Remove highest bit
  if (n < 24)
  {
    x = x << (23 - n); // Shift mantissa left if necessary
  }
  else
  {
    tmp2 = x >> (n - 23);
    cp2 = 0x1 << (n - 24);
    cp = x & ((cp2 << 1) - 1);
    if (cp < cp2)
    {
      x = tmp2;
    }
    else
    {
      if (tmp2 == 0x7fffff)
      {
        x = 0;
        n++;
      }
      else
      {
        if (cp == cp2)
        {
          x = ((tmp2) & 0x1) + tmp2;
        }
        else
        {
          x = tmp2 + 1;
        }
      }
    }
  }
  e = (127 + n) << 23; // Calculate exponent
  return sign | e | x; // Combine sign, exponent, and mantissa
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf)
{
  /*
   * Double the floating point value represented by uf.
   * If uf is NaN, return uf.
   */
  int tmp = uf;                                          // Temporary variable
  int sign = ((uf >> 31) << 31); /* 0x80000000 or 0x0 */ // Sign bit
  int exp = uf & 0x7f800000;                             // Exponent
  int f = uf & 0x7fffff;                                 // Fraction

  tmp = tmp & 0x7fffffff; /* remove sign */
  if ((tmp >> 23) == 0x0)
  {
    tmp = tmp << 1 | sign; // If uf is denormalized, multiply the significand by 2
    return tmp;
  }
  else if ((tmp >> 23) == 0xff)
  {
    return uf; // If uf is NaN or infinity, return uf
  }
  else
  {
    if ((exp >> 23) + 1 == 0xff)
    {
      return sign | 0x7f800000; // If the result would be too large, return infinity
    }
    else
    {
      return sign | (((exp >> 23) + 1) << 23) | f; // Multiply the exponent by 2
    }
  }
  return tmp;
}
