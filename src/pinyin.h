#ifndef PINYIN_H
#define PINYIN_H

#include <stddef.h>
typedef struct {
  const char *name;
  const int tone[2];
  int num_tones;
} Pinyin;

Pinyin random_syllable(void);
int format_syllable(Pinyin word, int tone, char *output, size_t output_size);

#endif
