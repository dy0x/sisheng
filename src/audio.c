#include "audio.h"
#include "pinyin.h"
#include <stdio.h>
#include <stdlib.h>

int play_syllable_audio(Pinyin syllable) {
  const char *filename = syllable.name;
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
