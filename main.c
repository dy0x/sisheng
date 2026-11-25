#include "main.h"
#include "pinyin.h"
#include "vendor/miniaudio/miniaudio.h"
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

int play(Pinyin *active_tones) {
  ma_engine engine;
  if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    printf("Failed to initialize audio engine.\n");
    return -1;
  }

  ma_engine_play_sound(&engine, "hao3.mp3", NULL);

  printf("Press Enter to quit...\n");
  getchar();
  ma_engine_uninit(&engine);
  return 0;
}

void start_single_tones() { play(active_tones); }

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
