// Write a function setbits(x,p,n,y) that returns x with
// the n bits that begin at position p set to the right-
// most bists of y, leaving the other bits unchanged.

// indebted bitwisecmd.com and stackoverflow.com/a/9175100/7014122

#include <stdio.h>

int setbits(unsigned, int, int, unsigned);

int main() {
  printf("%u\n", setbits(100, 4, 3, 255));
  return 0;
}

int setbits(unsigned x, int p, int n, unsigned y) {

  // get n bits from position p
  // return (x >> (p + 1 - n)) & ~(~0 << n);
  
  unsigned right, isolated, prep;
  
  // parenthetical values assume the above test invocation
  right = ~(~0 << n) & y; // obtain rightmost n bits of y (7)
  isolated = right << (p + 1 - n); // move bits 'right' to right-offset p, our "isolated" y (28)
  prep = ~right & x; // AND x with inverted y to get x with 0 in bits to be replaced (96)
  return prep | isolated; // OR with y to apply y's isolated bits to x

}
