#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "aes128.h"

typedef uint8_t byte;

int read_input(const char *inFile, int file_length, byte *input_string) {
  FILE *in = fopen(inFile, "r");

  if (in == NULL) {
    printf("ERROR opening %s\n", inFile);
    return(1);
  }
  
  for (int i = 0; i < file_length; i++) {
    fscanf(in, "%xhh", &input_string[i]);
  }

  fclose(in);
  return 0;
}

int print_bytes_as_hex(int string_length, byte *string ) {
  if (string == NULL) {
    printf("ADADADQDASDF");
  }
  for (int i = 0; i < string_length; i++) {
    printf("%02x ", string[i]);
  }

  return 0;
}

int find_input_length(const char *file_name) {
  int file_length = 0;
  FILE *in = fopen(file_name, "r");

  if (in == NULL) {
    printf("ERROR opening %s\n", file_name);
    return(1);
  }

  while (fscanf(in, "%x") != EOF) {
    file_length++;
  }

  fclose(in);

  return file_length;
}

int main(int argc, char const *argv[]) {
  int input_length = find_input_length(argv[1]);

  byte *input_string = malloc(sizeof(byte)*input_length);
  read_input(argv[1], input_length, input_string);
  print_bytes_as_hex(input_length, input_string);

  return 0;
}
