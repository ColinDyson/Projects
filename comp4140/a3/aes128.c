#include <stdio.h>
#include "aes128.h"

/*
Args
0 - executable name
1 - input file name
2 - output file name
*/
int main(int argc, char const *argv[]) {

  byteString *input = readInput(argv[1]);
  FILE *outFile;
  int inBytes = 0; //The length of the input file in bytes (- whitespace)

  if ((inFile = fopen(argv[1], "r")) == NULL) {
    printf("ERROR opening %s\n", argv[1]);
    return(1);
  }
  if ((outFile = fopen(argv[2], "w")) == NULL) {
    printf("ERROR opening %s\n", argv[2]);
    return(1);
  }

  while (fscanf(inFile, "%s") != EOF) {
    inBytes++;
  }

  printf("%d\n", inBytes);

  unsigned char in[inBytes][2];
  rewind(inFile);

  for (int i = 0; i < inBytes; i++) {
    fscanf(inFile, "%s", in[i]);
  }

  fclose(inFile);
  fclose(outFile);

  return 0;
}

byteString readInput(const char *in) {
  FILE *in = fopen(in);
}

void printByteArray(unsigned char *array, int length) {
  for (int i = 0; i < length; i++) {
    unsigned char buffer[3];
    snprintf(buffer, 3, "%s", array[i]);

    printf("%s\n", buffer);
  }
}
