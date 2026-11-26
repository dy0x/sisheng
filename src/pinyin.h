#ifndef PINYIN_H
#define PINYIN_H

#include <stddef.h>
typedef struct {
  char name[16];
  int tone;
} Pinyin;

Pinyin random_syllable(void);
int audio_file_exists(Pinyin syllable);
int format_syllable(Pinyin word, int tone, char *output, size_t output_size);

#endif
