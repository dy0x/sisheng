#include "main.h"
#include "pinyin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WINS 5

int menu_response(int max) {
  char buffer[64];
  char *end;

  for (;;) {
    printf("Selection (1-%d): ", max);

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

int play_audio(Pinyin active_tones) {
  const char *filename = active_tones.name;
  char command[256];

#if defined(__APPLE__)
  snprintf(command, sizeof(command), "afplay audio/%s.mp3", filename);
  if (system(command) != 0) {
    fprintf(stderr, "Could not play audio. Check that afplay is available.\n");
    return 1;
  }
#elif defined(__linux__)
  snprintf(command, sizeof(command), "pw-play audio/%s.mp3", filename);
  if (system(command) != 0) {
    fprintf(stderr, "Could not play audio. Check that pw-play is available.\n");
    return 1;
  }
#else
  fprintf(stderr, "Audio playback is not supported on this OS.\nGet a better "
                  "operating system!");
  return 1;
#endif
  return 0;
}

void render_tui(Pinyin word) {
  char pinyin[64];
  for (size_t i = 0; i < 4; i++) {
    if (format_pinyin(word, i, pinyin, sizeof(pinyin)) != 0) {
      fprintf(stderr, "Could not format pinyin.\n");
      return;
    };
    printf("  %zu - %s\n", i + 1, pinyin);
  }
}

void start_active_tones(int max_wins) {
  int wins = 0;
  int response;
  while (wins <= max_wins) {
    printf("\033[2J\033[H");
    printf("\nSingle Tone Mode\n");
    printf("\nListen to the audio and select the corresponding pinyin:\n");
    printf("Current Score: (%d/%d)\n", wins,max_wins);
    Pinyin word = get_word();
    render_tui(word);
    play_audio(word);
    response = menu_response(4);
    if (response == word.tone[0]) {
      wins += 1;
      printf("Correct!\n");
    } else {
      printf("Incorrect! Try again...\n");
    }
  }
}

int main() {
  printf("\033[2J\033[H");
  printf("Welcome to dy0x's Tone Trainer!\n");
  printf("Select which mode you would like:\n");
  printf("  1 - Single Tones\n");
  printf("  2 - Tone Pairs (Unavailable)\n");

  srand(time(NULL));
  int game_mode = menu_response(2);

  switch (game_mode) {
  case 1:
    start_active_tones(MAX_WINS);
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
