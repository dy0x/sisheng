#ifndef PINYIN_H
#define PINYIN_H

#include <stddef.h>
typedef struct {
  const char *name;
  const int tone[2];
  int num_tones;
} Pinyin;

Pinyin get_word();
int format_pinyin(Pinyin word, int tone, char *output, size_t output_size);

#endif
