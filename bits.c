/* 
 * CS:APP Data Lab 
 * 
 * <Justin Yara juya5998>
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
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
         //de morgans
int bitNor(int x, int y) {
  return ~x & ~y;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
//.. shifting 16 spots and 24 spots for the last 2 bytes, use 0xFF as all 11111111 to see if it is positive
//that is the positive case, negative test case 0x00
int fitsShort(int x) {
   // return !(!(x>>16 & 0xFF) ^ !(x>>24 & 0xFF)) | !(!(x>>16 & 0x0) ^ !(x>>24 & 0x0));
     //shift 16 places to the left
    //shift 16 spots back to the right
    //because of the shift, the number that is left in the last 2 bytes will tell us if it is - or +
    //use exclusive or to compare to the unmodified data to see if it fits
    //return with a bang because it will give us back a 1 with the exclusive or and it will return a
    //0 with the exclusive or, when we need a 1 if it fits. bang op will return the opposite
    return !( ((x<<16)>>16)^x);
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {//declare constant 73, that is bit pattern 0100 1001, start of our desired pattern
    //shift over to the next byte and populate with the next desired pattern, which is 36,
    //then populate the next area with 146, by shifting over 8, then we only have to fill in the last area
    //with 73 and we don't have to do any shifts
  return ((((73<<24)|36<<16)|146<<8)|73);
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//0x55 is equal to 01010101, this makes our number to test for even numbered bits
//i add piece it together like i did in the previous problem, and used or the same way.
//after that i used & of the original information (x) , and that will tell me 
//if they are the same. It returns a big 32 byte number
//by using !, that turns a 0 if its a 0, and if its any other number it returns a 1
int anyEvenBit(int x) {
   return !!(((((0x55<<24)| 0x55<<16)|0x55<<8)|0x55)&x);
    
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
/*
   * get rid of all bits except LSB so value is only either 1 or 0
   * then transform the 1 or the 0 into 0 (00000000...) 
   * or -1 (11111111....) in order to populate the other bits
   */

  // get rid of all bits except the LSB
  x = x & 1;
  // get the opposite of x
  // this makes x all ones if the LSB was zero
  // and all ones except the LSB if the LSB was one
  x = ~x;
  // add one. 
  // if x is all ones, then it rolls over to all zeros
  // if x has a trailing zero, then it becomes all ones
  return x + 1;
    
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    return !x | (!!y);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
 	//shifts all 1s left by low bit
	int low = ~0<<lowbit;
	//shifts all 1s right by high bit
	int high = ~0<<highbit;
	//shift highbit over 1 more and then complements it
	high = ~(high << 1);
	//returns 
  return high&low;

}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    int three = ((x << 1) + x); //shifting 1 to the right, add variable that is given, makes entire 
    //variable populate with that number
    int bias = (three >> 31) & 3; //create variable bias, shift that number 31 spots to the left, anding it 
    //by 3 to compare to 3
    return (three + bias) >> 2; //return the sum and shift to the left by 2. , like dividing by 4
    
   
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    //
    int sign = x >> 31; //start of our mask . right shift of 31,
    
    int tmin = 1 << 31; //shift it all the way back to create tmin, left shift of 31
    
    int tmax = ~tmin; // max is the opposite or the tilda of tmin
    
    int overflow = 0; //create overflow variable and start it at 0
    
    int threex, twox = x << 1; // left shift of 1, multiplying by 2, so byte will be double the original
    //both variables equal 2x. three x is declared only two x
    
    overflow = x ^ twox; //returns 1's if only 1 of the bits in the two in comparison
    //are equal to 1
    //shows differences between x and two x 
    
  
    //overflow is exlusive or on twox, the pattern that was shifted to the right by 1
    //over flow is now equal to the original byte pattern, that is exclusive or'd with the original
    //pattern that was right shifted by 1
    
    threex = twox + x;  //three x is equal to twox + x, thus creating three x
    
    overflow |= twox ^ threex; // piece it all together, by xor on twox and threex 
    // all the differences = overflow , records differences between all 3 of them, check to 
    //make sure there is no overflow on anything 
    
    overflow >>=31; //overflow = overflow >> 31, all being shifted , getting most sig bit 
    
    return (overflow & ((sign & tmin) | (~sign & tmax))) | (~overflow & threex);
    //returning overflow 
    //& operation to sign and tmin, added together using or operation with the tilda of the sign 'and'ed together
    //with tmax, then glued together again with or op with tilda overflow 'and'ed with threex

    
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    /*
    xor preserves parity, so just xor
   * bits 1 & 2, then the first two bits with the second two, etc. until
   * there is just one parity bit left.
   */

  // xoring two bits returns # of 1s % 2 in those two bits
  // so just xor every bit with the bit to its right
  // then those bits with the 2nd bit to the right
  // then the 4th to the right etc.
  // until you xor a bit with the 16th to its right
  // then the result is stored in the LSB
  x = x ^ (x >> 1); //right shift
  x = x ^ (x >> 2); //right shift
  x = x ^ (x >> 4); //right shift 
  x = x ^ (x >> 8);
  x = x ^ (x >> 16);
  return x & 1;

}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    //banging and shift right is checking if its in the upper half
    
    int num = 0; //creating int number and setting to 0
    num = (!!(x >> 16)) << 4;  
    
    //multiplying by 4 if it is in upper half, if not you mult 4 by 0
    //if statement, adding however much we shift by
    
    num = num + ((!!(x >> (num + 8))) << 3); //checking thurd section of bits
    num = num + ((!!(x >> (num + 4))) << 2);
    num = num + ((!!(x >> (num + 2))) << 1);
    num = num + (!!(x >> (num + 1)));
    
    return num;
}
    //find the first 1 
//     int y31 = ((x >> 31) & 0x1);
//     int y30 = (((x << 1)>>30)& 0x1);  //the 31st bit has been brought to the first place
//     int y29 = (((x << 2)>>29)& 0x1);
//     int y28 = (((x << 3)>>28)& 0x1);       //tells me how many 0's are followed
//     int y27 = (((x << 4)>>27)& 0x1);
//     int y26 = (((x << 5)>>26)& 0x1);
//     int y25 = (((x << 6)>>25)& 0x1);//we have the trend of log2 of numbers, we take advantage of thistrend
//     int y24 = (((x << 7)>>24)& 0x1);//by being able to count up the zero's behind a number to add them up 
//     int y23 = (((x << 8)>>23)& 0x1);//to equal the log of that number
//     int y22 = (((x << 9)>>22)& 0x1);
//     int y21 = (((x << 10)>> 21)& 0x1);
//     int y20 = (((x << 11)>> 20)& 0x1);//shift over, then back, then & it with all 1's
//     int y19 = (((x << 12)>> 19)& 0x1);
//     int y18 = (((x << 13)>> 18)& 0x1);
//     int y17 = (((x << 14)>> 17)& 0x1);
//     int y16 = (((x << 15)>> 16)& 0x1);
//     int y15 = (((x << 16)>> 15)& 0x1);
//     int y14 = (((x << 17)>> 14)& 0x1);
//     int y13 = (((x << 18)>> 13)& 0x1);
//     int y12 = (((x << 19)>> 12)& 0x1);
//     int y11 = (((x << 20)>> 11)& 0x1);
//     int y10 = (((x << 21)>> 10)& 0x1);//checking every single bit position , ignoring the last spot because 
//                                       //it is log and the last spot is negative
//     int y9  = (((x << 22)>> 9)& 0x1);
//     int y8 =  (((x << 23)>> 8)& 0x1);
//     int y7 =  (((x << 24)>> 7)& 0x1);
//     int y6 =  (((x << 25)>> 6)& 0x1);
//     int y5 =  (((x << 26)>> 5)& 0x1);
//     int y4 =  (((x << 27)>> 4)& 0x1);
//     int y3 =  (((x << 28)>> 3)& 0x1);
//     int y2 =  (((x << 29)>> 2)& 0x1);
//     int y1 =  (((x << 30)>> 1)& 0x1);
//     int total = (y1+y2+y3+y4+y5+y6+y7+y8+y9+y10+y11+y12+y13+y14+y15+y16+y17+y18+y19+y20+y21+y22+y23+y24+y25+y26+y27+y28+y29+y30+y31);
    
//     return total;
//     int temp, sum;
    
//     temp = (x >> 1) | x;
//     temp = (x >> 2) | x;
//     temp = (x >> 3) | x;
//     temp = (x >> 4) | x;
//     temp = (x >> 5) | x;
//     temp = (x >> 6) | x;
//     temp = (x >> 7) | x;
//     temp = (x >> 8) | x;
//     temp = (x >> 9) | x;
//     temp = (x >> 10) | x;
//     temp = (x >> 11) | x;
//     temp = (x >> 12) | x;
//     temp = (x >> 13) | x;
//     temp = (x >> 14) | x;
//     temp = (x >> 15) | x;
//     temp = (x >> 16) | x;
    
//     sum += !!(x >> 16);
//     sum += !!(x >> 15);
//      sum += !!(x >> 14);
//      sum += !!(x >> 13);
//      sum += !!(x >> 12);
//      sum += !!(x >> 11);
//      sum += !!(x >> 10);
//      sum += !!(x >> 9);
//      sum += !!(x >> 8);
//      sum += !!(x >> 7);
//      sum += !!(x >> 6);
//      sum += !!(x >> 5);
//      sum += !!(x >> 4);
//      sum += !!(x >> 3);
//      sum += !!(x >> 2);
//      sum += !!(x >> 1);
    
    
//     temp = (x & 0x1) | ((x>>1) & x);

//     return temp;
   
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
    int sign = x >> 31; //seeing if it is positive or negative, checking the last bit 
    
    int mod4 = x & 3; //create another int variable by using & op on original x And 3
    //checking to see if there are any 3's
    
    x = x>>2; //making x shift by 2
    return (x+x+x)+((mod4 + mod4 +mod4+(sign&3))>>2); //returning x + x + x, 
}
/*
 * Extra credit
 */
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
unsigned float_neg(unsigned uf) {
 return 2;
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
unsigned float_i2f(int x) {
  return 2;
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
unsigned float_twice(unsigned uf) {
  return 2;
}
