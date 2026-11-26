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

#define MAX_WINS 2

static void clear_screen(void) { printf("\033[2J\033[H"); }

static void show_tone_choices(Pinyin word) {
  char pinyin[64];
  for (int i = 0; i < 5; i++) {
    if (format_syllable(word, i, pinyin, sizeof(pinyin)) != 0) {
      fprintf(stderr, "Could not format pinyin.\n");
      return;
    }
    printf("  %d - %s\n", i + 1, pinyin);
  }
}

static void run_single_tone_mode(int max_wins) {
  const int min = 1, max = 5;
  int wins = 0;
  int response;

  clear_screen();

  while (wins < max_wins) {
    printf("\nSingle Tone Mode\n");
    printf("\nListen to the audio and select the corresponding pinyin:\n");
    printf("Current Score: (%d/%d)\n", wins, max_wins);
    Pinyin word;
    do{
      word = random_syllable();
    }while(!audio_file_exists(word));
    show_tone_choices(word);
    while (play_syllable_audio(word) != 0) {
      printf("Unable to play audio.\nPress 1 to retry or Q to quit.\n");
      if (read_menu_choice(1, 1, &response) != MENU_CHOICE) {
        return;
      }
    }
    if (read_menu_choice(min, max, &response) != MENU_CHOICE) {
      return;
    }
    clear_screen();
    if (response == word.tone) {
      wins += 1;
      printf("Correct!\n");
    } else {
      printf("Incorrect! Try again...\n");
    }
  }

  if (wins == max_wins){
    clear_screen();
    printf("Congratulations! You win!!\n");
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

  srand((unsigned int)time(NULL));
  if (read_menu_choice(min, max, &game_mode) != MENU_CHOICE) {
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
