#ifndef _aes128_h
#define _aes128_h

typedef struct {
  unsigned char **bytes;
  int length;
} byteString;

byteString readInput(const char *);

#endif
