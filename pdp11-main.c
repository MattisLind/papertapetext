#define PUNCH_CS 0177554
#define PUNCH_DB 0177556
#define CONSOLE_RX_CS 0177560
#define CONSOLE_RX_DB 0177562
#define CONSOLE_TX_CS 0177564
#define CONSOLE_TX_DB 0177566


int printPaperTapeChar (int, int (*)(int)); 


int putchar (int ch)
{
  while (*((volatile char *) (CONSOLE_TX_CS)) < 0); // wait for TX ready
  *((volatile int *) (CONSOLE_TX_DB)) = ch;
  return 0;
}

int  putPunchChar (int ch)
{
  while (*((volatile char *) (PUNCH_CS))<0); // Wait for punch ready
  *((volatile int *) (PUNCH_DB)) = ch;
  return 0;
}

int puts (const char * str) {
  char ch;
  while ((ch=*str++)) {
    putchar(ch);
  }
}

char getchar () {
  while (*((volatile char *) (CONSOLE_RX_CS))<0); // Wait for character received
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
      if (i==0 && ((ch==0x0d)||(ch==0x0a))) {
	continue; // Don't do anything if the user has't typed anything and also filter out CR LF sequence.
      } 
      if ((ch == 0x0d) || (ch == 0x0a) || (i==40)) {
	break;  // Max line length is 40 characters. Line is terminated by CR or LF.  
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




