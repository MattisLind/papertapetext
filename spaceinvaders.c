


#define PUNCH_CS 0177554
#define PUNCH_DB 0177556

char invaderOne [] = {0x70, 0x18, 0x7d, 0xb6, 0xbc, 0x8c, 0xbc, 0xb6, 0x7d, 0x18, 0x70, 0x00};
char invaderTwo [] = {0x1e, 0xb8, 0x7d, 0x36, 0x3c, 0x3c, 0x3c, 0x36, 0x7d, 0xb8, 0x1e, 0x00};

int  putPunchChar (int ch)
{
  while (*((volatile char *) (PUNCH_CS))>=0); // Wait for punch ready
  *((volatile int *) (PUNCH_DB)) = ch;
  return 0;
}


void punchInvader(char * invader) {
  char ch;
  int i;
  while ((ch = invader[i++])!=0) {
    putPunchChar(ch);
  }
}



int main () {
  while(1) {
    punchInvader(invaderOne);
    putPunchChar(0);
    putPunchChar(0);
    putPunchChar(0);
    punchInvader(invaderTwo);
    putPunchChar(0);
    putPunchChar(0);
    putPunchChar(0);
  }
}
