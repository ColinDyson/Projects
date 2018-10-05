#include <stdio.h>

int main(int argc, char const *argv[]) {

  char c;

  printf("Enter a character:\n");
  scanf("%c", &c);
  printf("ASCII value of character %c: %d\n", c, c);

  return 0;
}
