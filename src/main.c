#include "main.h"
#include "pinyin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu_response(int max) {
  char buffer[32];
  char *end;

  for (;;) {
    printf("Selection (1-%d) ", max);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      fprintf(stderr, "Invalid input or EOF\n");
      return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
      int ch = getchar();
      if (ch != '\n' && ch != EOF) {
        while (ch != '\n' && ch != EOF) {
          ch = getchar();
        }
        printf("Input was too long. Try again!\n");
        continue;
      }
    }

    const long input = strtol(buffer, &end, 10);

    while (*end == ' ' || *end == '\t') {
      end++;
    }

    if ((*end == '\n' || *end == '\0') && input >= 1 && input <= max) {
      return (int)input;
    }

    printf("Invalid! Try again... ");
  }
}

int play_audio(Pinyin *active_tones) {
#if defined(__APPLE__)
  if (system("afplay audio/hao3.mp3") != 0) {
    fprintf(stderr, "Could not play audio. Check that afplay is available.\n");
    return 1;
  }
#elif defined(__linux__)
  if (system("pw-play audio/hao3.mp3") != 0) {
    fprintf(stderr, "Could not play audio. Check that pw-play is available.\n");
    return 1;
  }
#else
  fprintf(stderr, "Audio playback is not supported on this OS.\n");
  return 1;
#endif

  return 0;
}

void start_single_tones() {
  for (size_t i = 0; i < active_tones_count; i++) {
    play_audio(&active_tones[i]);
  }
}

int main() {
  printf("Welcome to dy0x's Tone Trainer!\n");
  printf("Select which mode you would like:\n");
  printf("  1 - Single Tones\n");
  printf("  2 - Tone Pairs (Unavailable)\n");

  int input = menu_response(2);
  printf("You selected: %d \n", input);

  switch (input) {
  case 1:
    start_single_tones();
  case 2:
    printf("Sorry, that option is currently unavailable!\n");
  default:
    return 1;
  }
}
