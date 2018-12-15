#include <stdio.h>

int printPaperTapeChar (int, int (*)(int)); 


int main ()
{
  int ch;
  while (EOF != (ch = fgetc(stdin))) {
    printPaperTapeChar(ch, putchar);
  }
  return 0;
}
