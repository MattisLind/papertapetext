volatile unsigned short * txcsr = (unsigned short *) 0177564; 
volatile unsigned short * txbuf = (unsigned short *) 0177566;
volatile unsigned short * rxcsr = (unsigned short *) 0177560; 
volatile unsigned short * rxbuf = (unsigned short *) 0177562;
volatile unsigned short * punchcsr = (unsigned short *) 0177554; 
volatile unsigned short * punchbuf = (unsigned short *) 0177556;

int printPaperTapeChar (int, int (*)(int)); 


int putchar (int ch)
{
  while (!(0200 & *txcsr)) {
  };
  *txbuf = ch;
  return 0;
}

int  putPunchChar (int ch)
{
  while (!(0200 & *punchcsr)) {
  };
  *punchbuf = ch;
  return 0;
}

void puts (char * str) {
  char ch;
  while ((ch=*str++)) {
    putchar(ch);
  }
}

char getchar () {
  while (!(0200 & *rxcsr)) {
  };
  return *rxbuf;
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




