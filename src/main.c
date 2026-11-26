#include "main.h"
#include "audio.h"
#include "input.h"
#include "pinyin.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WINS 5

static void clear_screen(void) { printf("\033[2J\033[H"); }


static void show_tone_choices(Pinyin word) {
  char pinyin[64];
  for (size_t i = 0; i < 4; i++) {
    if (format_syllable(word, i, pinyin, sizeof(pinyin)) != 0) {
      fprintf(stderr, "Could not format pinyin.\n");
      return;
    }
    printf("  %zu - %s\n", i + 1, pinyin);
  }
}

static void run_single_tone_mode(int max_wins) {
  const int min = 1, max = 4;
  int wins = 0;
  int response;

  clear_screen();

  while (wins < max_wins) {
    printf("\nSingle Tone Mode\n");
    printf("\nListen to the audio and select the corresponding pinyin:\n");
    printf("Current Score: (%d/%d)\n", wins, max_wins);
    Pinyin word = random_syllable();
    show_tone_choices(word);
    if (play_syllable_audio(word) == 1) {
      exit(1);
    };
    if (read_menu_choice(min,max,&response)!=MENU_CHOICE){
      return;
    }
    clear_screen();
    if (response == word.tone[0]) {
      wins += 1;
      printf("Correct!\n");
    } else {
      printf("Incorrect! Try again...\n");
    }
  }
}

int main(void) {
  int game_mode;
  const int min = 1, max = 2;

  // clear_screen();
  printf("Welcome to dy0x's Tone Trainer!\n");
  printf("Select which mode you would like:\n");
  printf("  1 - Single Tones\n");
  printf("  2 - Tone Pairs (Unavailable)\n");
  printf("  Q - Quit\n");

  srand(time(NULL));
  if (read_menu_choice(min,max,&game_mode)!=MENU_CHOICE){
    printf("Goodbye!\n");
    return 0;
  }

  switch (game_mode) {
  case 0:
    printf("Goodbye!\n");
    return 0;
  case 1:
    run_single_tone_mode(MAX_WINS);
    break;
  case 2:
    printf("Sorry, that option is currently unavailable!\n");
    break;
  default:
    return 1;
  }

  printf("Goodbye!\n");
  return 0;
}
