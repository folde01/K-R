#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUFSIZE 100 

char buf[BUFSIZE];
int bufp = 0;

main() {
  int n, array[SIZE], getint(int *);
  for (n = 0; n < SIZE; n++)
    array[n] = -999;

  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    ;

  for (n = 0; n < SIZE; n++)
    printf("array[%d]: %d\n", n, array[n]);
}

int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
    //ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  
  if (c == '+' || c == '-')
    c = getch();

  if (!isdigit(c)) {
    ungetch(c);
    return 0;
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  *pn *= sign;

  if (c != EOF)
    ungetch(c);

  return c;
}

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters in buffer.\n");
  else
    buf[bufp++] = c;
}
