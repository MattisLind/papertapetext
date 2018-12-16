#define PUNCH_CS 0177554
#define PUNCH_DB 0177556
#define CONSOLE_RX_CS 0177560
#define CONSOLE_RX_DB 0177562
#define CONSOLE_TX_CS 0177564
#define CONSOLE_TX_DB 0177566


int printPaperTapeChar (int, int (*)(int)); 


int putchar (int ch)
{
  while (!(0200 & * ((volatile int *) (CONSOLE_TX_CS)))); // wait for TX ready
  *((volatile int *) (CONSOLE_TX_DB)) = ch;
  return 0;
}

int  putPunchChar (int ch)
{
  while (!(0200 & * ((volatile int *) (PUNCH_CS)))); // Wait for punch ready
  *((volatile int *) (PUNCH_DB)) = ch;
  return 0;
}

void puts (char * str) {
  char ch;
  while ((ch=*str++)) {
    putchar(ch);
  }
}

char getchar () {
  while (!(0200 & *((volatile int *) (CONSOLE_RX_CS)))); // Wait for character received
  return *((volatile int *) (CONSOLE_RX_DB));
}

char buf[40];

int main ()
{
  int i, ch;
  while(1) {
    puts("PUNCHED PAPER TAPE WRITER>");
    i=0;
    do {
      ch = getchar();
      if ((ch == 0x0d) || (ch == 0x0a) || (i==40)) {
	break;
      }
      buf[i]=ch;
      i++;
      putchar(ch);
    } while (1);
    buf[i]=0;
    putchar(0x0d); putchar(0x0a);
    i=0;
    while ((ch = buf[i])!=0) {
      printPaperTapeChar(ch, putPunchChar);
    }
  }
  return 0;
}




