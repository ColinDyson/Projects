#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "aes128.h"

typedef uint8_t byte;
typedef uint32_t word;

static const byte Rcon[255] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
  0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
  0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
  0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
  0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
  0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
  0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
  0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
  0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
  0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
  0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
  0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
  0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
  0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
  0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
  0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

static int N_k = 4; //length of key, in 32-bit words
static int N_b = 4; //number of columns in the State, in 32-bit words
static int N_r = 10; //number of rounds
static int N_s = 256; //size of s-box (by definition), in 8-bit bytes
static char *SBOX_NAME = "aes_sbox.txt";
static char *INV_SBOX_NAME = "aes_inv_sbox.txt";
byte *sbox;
byte *inv_sbox;

int read_input(const char *input_filename, int file_length, byte *input_string) {
  FILE *in = fopen(input_filename, "r");

  if (in == NULL) {
    printf("ERROR: Cannot open %s\n", input_filename);
    return(1);
  }
  
  for (int i = 0; i < file_length; i++) {
    fscanf(in, "%xhh", &input_string[i]);
  }

  fclose(in);
  return 0;
}

/*Print the contents of string as bytes represented by two hexadecimal characters.*/
int print_bytes_as_hex(int string_length, byte *byte_string ) {
  const int WORDS_PER_LINE = 4; //number of 32-bit words to print before adding a newline

  if (byte_string == NULL) {
    printf("ERROR: Attempting to print string with value NULL\n");
    return 1;
  }
  for (int i = 0; i < string_length; i++) {
    if (i % (WORDS_PER_LINE * sizeof(word)/sizeof(byte)) == 0) {
      printf("\n");
    }
    printf("%02x ", byte_string[i]);
  }
  printf("\n");

  return 0;
}

/*Counts the number of bytes of message text in the input. Excludes whitespace.*/
int find_input_length(const char *file_name) {
  int file_length = 0;
  FILE *in = fopen(file_name, "r");

  if (in == NULL) {
    printf("ERROR: Cannot open %s\n", file_name);
    return(1);
  }

  while (fscanf(in, "%x") != EOF) {
    file_length++;
  }

  fclose(in);

  return file_length;
}

int print_key_schedule(FILE *out, word *key_schedule) {
  fprintf(out, "Key Schedule:\n");

  for (int i = 0; i < N_b * (N_r + 1); i++) { //size of schedule by definition
    fprintf(out, "%08x", key_schedule[i]);
    if (i % 4 == 3) {
      fprintf(out, "\n");
    }
    else {
      fprintf(out, ",");
    }
  }

  return 0;
}

int words_to_bytes(int n) {
  return n * sizeof(word) / sizeof(byte);
}

int bytes_to_words(int n) {
  return n / sizeof(word) / sizeof(byte);
}

/*Substitutes each byte in the word with the corresponding byte in the S-box*/
word sub_word(word w) {
  byte *curr_byte;

  for (int i = 0; i < 4; i++) {
    curr_byte = ((byte *)&w + i);
    *curr_byte = sbox[*curr_byte];
  }
  return w;
}

word rot_word(word w) {
  w = (w << 8) | ((w & 0xFF000000) >> 24);

  return w;
}

int cipher(byte *in, byte *out) {
  print_bytes_as_hex(16, in);
  return 0;
}

int key_expansion(byte *key, word *key_schedule) {
  word temp;

  int i;

  //First 4 words of the key schedule are equal to the key
  for (i = 0; i < N_k; i++) {
    word new_word = key[4 * i] << 24;
    new_word |= key[4 * i + 1] << 16;
    new_word |= key[4 * i + 2] << 8;
    new_word |= key[4 * i + 3];
    key_schedule[i] = new_word;
  }

  i = N_k;

  while (i < N_b * (N_r + 1)) {
    temp = key_schedule[i - 1];

    if (i % N_k == 0)  {
      temp = rot_word(temp);
      temp = sub_word(temp);
      //Construct word with byte 0 as the rcon value for i / N_k
      word r_con_word = Rcon[i / N_k] << 24;
      temp ^= r_con_word;
    }
    key_schedule[i] = key_schedule[i - N_k] ^ temp;

    i++;
  }
  return 0;
}

int print_output_header(const char *input_filename, const char *key_filename, word *key_schedule, const char *output_filename) {
  FILE *out = fopen(output_filename, "w");

  if (out == NULL) {
    printf("ERROR: Cannot open %s\n", output_filename);
    return(1);
  }

  fprintf(out, "PlainText Filename: \"%s\"\n", input_filename);
  fprintf(out, "Key Filename: \"%s\"\n\n", key_filename);
  
  print_key_schedule(out, key_schedule);

  fclose(out);

  return 0;
}


int encrypt(byte *in, byte *out, word* key_schedule) {
  return 0;
}

int decrypt(byte *in, byte *out, word *key_schedule) {
  return 0;
}

int main(int argc, char const *argv[]) {
  const char *output_filename = "output.txt";

  if (argc < 3) {
    printf("ERROR: Must provide filenames of both the message and the key\n");
    return 1;
  }

  const char *input_filename = argv[1];
  const char *key_filename = argv[2];

  if (argc == 4) {
    //Output filename provided
    output_filename = argv[3];
  }

  int input_length = find_input_length(input_filename);

  byte *input_string = calloc(sizeof(byte), input_length);
  byte *output_string = calloc(sizeof(byte), input_length);
  byte *key = calloc(sizeof(word), N_k);
  word *key_schedule = calloc(sizeof(word), N_b * (N_r + 1));
  sbox = calloc(sizeof(byte), N_s);
  inv_sbox = calloc(sizeof(byte), N_s);

  read_input(input_filename, input_length, input_string);
  read_input(key_filename, words_to_bytes(N_k), key);
  read_input(SBOX_NAME, N_s, sbox);
  read_input(INV_SBOX_NAME, N_s, inv_sbox);

  key_expansion(key, key_schedule);

  print_output_header(input_filename, key_filename, key_schedule, output_filename);
  
  encrypt(input_string, output_string, key_schedule);

  //decrypt();

  return 0;
}
