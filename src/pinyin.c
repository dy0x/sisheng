#include "pinyin.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const Pinyin single_syllables[] = {
    {.name = "hao3", .tone = {3}, .num_tones = 1},
    {.name = "niu1", .tone = {1}, .num_tones = 1},
    {.name = "niu2", .tone = {2}, .num_tones = 1},
    {.name = "niu4", .tone = {4}, .num_tones = 1},
    {.name = "nong1", .tone = {1}, .num_tones = 1},
    {.name = "nong2", .tone = {2}, .num_tones = 1},
    {.name = "nong3", .tone = {3}, .num_tones = 1},
    {.name = "ai1", .tone = {1}, .num_tones = 1},
    {.name = "ai2", .tone = {2}, .num_tones = 1},
    {.name = "ai4", .tone = {4}, .num_tones = 1},
};

static const char* vowel_a[] = {"ā", "á", "ǎ", "à", "a"};
static const char* vowel_e[] = {"ē", "é", "ě", "è", "e"};
static const char* vowel_i[] = {"ī", "í", "ǐ", "ì", "i"};
static const char* vowel_o[] = {"ō", "ó", "ǒ", "ò", "o"};
static const char* vowel_u[] = {"ū", "ú", "ǔ", "ù", "u"};
static const char* vowel_v[] = {"ǖ", "ǘ", "ǚ", "ǜ", "ü"};

static const size_t single_syllables_count =
    sizeof(single_syllables) / sizeof(single_syllables[0]);

Pinyin random_syllable(void) {
  return single_syllables[(size_t)rand() % single_syllables_count];
}

int audio_file_exists(Pinyin syllable){
    char path[256];
    snprintf(path, sizeof(path),"audio/%s.mp3",syllable.name);

    FILE *f = fopen(path,"r");
    if (f == NULL){
        return 0;
    }
    fclose(f);
    return 1;
}

static ptrdiff_t vowel_position(Pinyin word) {
  const char* name = word.name;
  char target = 'a';
  char* result = strchr(name, target);
  if (result != NULL) {
    return result - name;
  }

  target = 'e';
  result = strchr(name, target);
  if (result != NULL) {
    return result - name;
  }

  const char* new_target = "ou";
  result = strstr(name, new_target);
  if (result != NULL) {
    return result - name;
  }

  ptrdiff_t index = -1;
  for (size_t i = 0; i < strlen(word.name); i++) {
    if (word.name[i] == 'a' || word.name[i] == 'e' || word.name[i] == 'i' ||
        word.name[i] == 'o' || word.name[i] == 'u') {
      index = (ptrdiff_t)i;
    }
  }
  return index;
}

int format_syllable(Pinyin word, int tone, char* output, size_t output_size) {
  ptrdiff_t position = vowel_position(word);
  size_t word_length = strlen(word.name) - 1;
  const char* replacement;

  if (tone > 4 || tone < 0) {
    return 1;
  }

  if (position < 0) {
    return 1;
  }

  switch (word.name[position]) {
    case 'a':
      replacement = vowel_a[tone];
      break;
    case 'e':
      replacement = vowel_e[tone];
      break;
    case 'i':
      replacement = vowel_i[tone];
      break;
    case 'o':
      replacement = vowel_o[tone];
      break;
    case 'u':
      replacement = vowel_u[tone];
      break;
    case 'v':
      replacement = vowel_v[tone];
    default:
      return 1;
  }

  size_t needed = word_length + strlen(replacement);
  if (needed > output_size) {
    return 1;
  }

  size_t write_index = 0;
  for (size_t i = 0; i < word_length; i++) {
    if (i == (size_t)position) {
      for (size_t j = 0; replacement[j] != '\0'; j++) {
        output[write_index] = replacement[j];
        write_index++;
      }
    } else {
      output[write_index] = word.name[i];
      write_index++;
    }
  }
  output[write_index] = '\0';

  return 0;
}
