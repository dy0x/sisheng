#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pinyin.h"
#include "input.h"

static int read_line(char *buffer, size_t size) {
  for (;;) {
    if (fgets(buffer, size, stdin) == NULL) {
      fprintf(stderr, "Invalid input or EOF\n");
      return 1;
    }

    if (strchr(buffer, '\n') == NULL) {
      int ch;
      do {
        ch = getchar();
      } while (ch != '\n' && ch != EOF);
      printf("Input was too long. Try again!\n");
      continue;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    return 0;
  }
}

static int parse_int(const char *str, int *out) {
  char *end;

  errno = 0;
  const long value = strtol(str, &end, 10);

  if (end == str) {
    return 1;
  }
  if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
    return 1;
  }

  while (*end == ' ' || *end == '\t') {
    end++;
  }

  if (*end != '\0') {
    return 1;
  }

  *out = (int)value;
  return 0;
}

enum menu_result read_menu_choice(int min, int max, int *choice) {
  char buffer[64];
  for (;;) {
    printf("Selection (%d-%d): ", min, max);

    if (read_line(buffer, sizeof(buffer)) != 0) {
      return MENU_EOF;
    }

    if (strcmp(buffer, "Q") == 0 || strcmp(buffer, "q") == 0) {
      return MENU_QUIT;
    }

    if (parse_int(buffer, choice) == 0 && *choice >= min && *choice <= max) {
      return MENU_CHOICE;
    }
    printf("Invalid! Try again... ");
  }
}