#include "pinyin.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const Pinyin single_syllables[] = {
    {.name = "hao3", .tone = {3}, .num_tones = 1},
    {.name = "niu1", .tone = {1}, .num_tones = 1},
    {.name = "niu2", .tone = {2}, .num_tones = 1},
    {.name = "niu3", .tone = {3}, .num_tones = 1},
    {.name = "niu4", .tone = {4}, .num_tones = 1}};

static const char *vowel_a[] = {"ā", "á", "ǎ", "à"};
static const char *vowel_e[] = {"ē", "é", "ě", "è"};
static const char *vowel_i[] = {"ī", "í", "ǐ", "ì"};
static const char *vowel_o[] = {"ō", "ó", "ǒ", "ò"};
static const char *vowel_u[] = {"ū", "ú", "ǔ", "ù"};
static const char *vowel_v[] = {"ǖ", "ǘ", "ǚ", "ǜ"};

static const size_t single_syllables_count =
    sizeof(single_syllables) / sizeof(single_syllables[0]);

Pinyin random_syllable(void) { return single_syllables[rand() % single_syllables_count]; }

static int vowel_position(Pinyin word) {
  const char *name = word.name;
  char target = 'a';
  char *result = strchr(name, target);
  if (result != NULL) {
    return result - name;
  }

  target = 'e';
  result = strchr(name, target);
  if (result != NULL) {
    return result - name;
  }

  const char *new_target = "ou";
  result = strstr(name, new_target);
  if (result != NULL) {
    return result - name;
  }

  int index = -1;
  for (size_t i = 0; i < strlen(word.name); i++) {
    if (word.name[i] == 'a' || word.name[i] == 'e' || word.name[i] == 'i' ||
        word.name[i] == 'o' || word.name[i] == 'u') {
      index = i;
    }
  }
  return index;
}

int format_syllable(Pinyin word, int tone, char *output, size_t output_size) {

  int position = vowel_position(word);
  int word_length = strlen(word.name) - 1;
  const char *replacement;

  if (tone > 3 || tone < 0) {
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
  default:
    return 1;
  }

  size_t needed = word_length + strlen(replacement);
  if (needed > output_size) {
    return 1;
  }

  size_t write_index = 0;
  for (size_t i = 0; i < word_length; i++) {
    if (i == position) {
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
