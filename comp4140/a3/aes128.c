#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

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

#define N_k 4 //length of key, in 32-bit words
#define N_b 4 //number of columns in the State, in 32-bit words
#define N_r 10 //number of rounds
#define N_s 256 //size of s-box (by definition), in 8-bit bytes
char *SBOX_NAME = "aes_sbox.txt";
char *INV_SBOX_NAME = "aes_inv_sbox.txt";
byte *sbox;
byte *inv_sbox;

int read_input(const char *input_filename, int file_length, byte *input_string) {
  FILE *in = fopen(input_filename, "r");

  if (in == NULL) {
    printf("ERROR: Cannot open %s\n", input_filename);
    exit(1);
  }
  
  for (int i = 0; i < file_length; i++) {
    fscanf(in, "%xhh", &input_string[i]);
  }

  fclose(in);
  return 0;
}

/*Print the contents of string as bytes represented by two hexadecimal characters.*/
int print_bytes_as_hex(byte *byte_string, int string_length) {
  const int WORDS_PER_LINE = 4; //number of 32-bit words to print before adding a newline

  if (byte_string == NULL) {
    printf("ERROR: Attempting to print string with value NULL\n");
    exit(1);
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
    exit(1);
  }

  while (fscanf(in, "%x") != EOF) {
    file_length++;
  }

  fclose(in);

  return file_length;
}

int print_key_schedule(word *key_schedule, FILE *out) {
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

int print_output_header(const char *input_filename, const char *key_filename, word *key_schedule, FILE *out) {
  fprintf(out, "PlainText Filename: \"%s\"\n", input_filename);
  fprintf(out, "Key Filename: \"%s\"\n\n", key_filename);
  
  print_key_schedule(key_schedule, out);

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

int output_word(byte *output, FILE *f) {
  for (int i = 0; i < 16; i++) {
    fprintf(f, "%02x\t", output[i]);
    if (i % 4 == 3) {
      fprintf(f, "\t");
    }
  }

  fprintf(f, "\n");

  return 0;
}

int print_state(byte state[4][N_b]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%02x ", state[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return 0;
}

int add_round_key(byte state[4][N_b], word *round_key) {
  print_state(state);

  byte key[4][4] = {0};

  for (int col = 0; col < 4; col++) {
    key[0][col] = *((byte *)&round_key[col]);
    key[1][col] = *((byte *)&round_key[col] + 4);
    key[2][col] = *((byte *)&round_key[col] + 8);
    key[3][col] = *((byte *)&round_key[col] + 12);
  }

  print_state(key);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      state[row][col] ^= key[row][col];
    }
  }

  print_state(state);
  return 0;
}

int sub_bytes(byte state[4][N_b]) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < N_b; col++) {
      state[row][col] = sbox[state[row][col]];
    }
  }

  return 0;
}

int shift_rows(byte state[4][N_b]) {
  for (int row = 0; row < N_b; row++) {
    for (int shift = 0; shift < row; shift++) {
      byte temp = state[row][0];
      state[row][0] = state[row][1];
      state[row][1] = state[row][2];
      state[row][2] = state[row][3];
      state[row][3] = temp;
    }
  }

  return 0;
}

byte xtime2(byte value) {
  byte result = value << 1;
  if (result >> 7 == 1) {
    result ^= 0x1b;
  }

  return result;
}

byte xtime3(byte value) {
  byte result = xtime2(value);
  result = result ^ value;

  return result;
}

int mix_columns(byte state[4][N_b]) {
  for (int col = 0; col < N_b; col++) {
    state[0][col] = xtime2(state[0][col]) ^ xtime3(state[1][col]) ^ state[2][col] ^ state[3][col];
    state[1][col] = state[0][col] ^ xtime2(state[1][col]) ^ xtime3(state[2][col]) ^ state[3][col];
    state[2][col] = state[0][col] ^ state[1][col] ^ xtime2(state[2][col]) ^ xtime3(state[3][col]);
    state[3][col] = xtime3(state[0][col]) ^ state[1][col] ^ state[2][col] ^ xtime2(state[3][col]);
  }
  
  return 0;
}

int encrypt(byte *in, byte *out, word *key_schedule, FILE *f) {
  fprintf(f, "\n\nENCRYPTION PROCESS\n");
  fprintf(f, "------------------\n");
  fprintf(f, "Plain Text:\n");
  output_word(in, f);

  //we treat the state as a one dimensional array
  byte state[4][N_b] = {0};
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      state[row][col] = in[(4 * col) + row];
    }
  }
  printf("round key: %08x\n", key_schedule[0]);
  printf("round key: %08x\n", key_schedule[1]);
  printf("round key: %08x\n", key_schedule[2]);
  printf("round key: %08x\n\n", key_schedule[3]);
  add_round_key(state, &key_schedule[0]);
  //print_state(state);

  for (int round = 1; round <= N_r - 1; round++) {
    sub_bytes(state);
    shift_rows(state);
    mix_columns(state);
    add_round_key(state, &key_schedule[round * N_b]);
    fprintf(f, "Round %d\n---------\n", round);
    output_word((byte *)state, f);
  }

  sub_bytes(state);
  shift_rows(state);
  add_round_key(state, &key_schedule[N_b * N_r]);

  fprintf(f, "Last Round %d\n---------\n");
  output_word((byte *)state, f);

  for (int row = 0; row < N_b; row++) {
    out[row] = state[row][0] << 24;
    out[row] |= state[row][1] << 16;
    out[row] |= state[row][2] << 8;
    out[row] |= state[row][3];
  }

  return 0;
}

int decrypt(byte *in, byte *out, word *key_schedule, const char *output_filename) {
  //TODO
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

  FILE *out = fopen(output_filename, "w");
  if (out == NULL) {
    printf("ERROR: Cannot open %s\n", output_filename);
    exit(1);
  }

  print_output_header(input_filename, key_filename, key_schedule, out);
  
  encrypt(input_string, output_string, key_schedule, out);
  fprintf(out, "Ciphertext:\n");
  output_word(output_string, out);
  //decrypt();

  fclose(out);

  free(input_string);
  free(output_string);
  free(key);
  free(key_schedule);
  free(sbox);
  free(inv_sbox);
  return 0;
}
