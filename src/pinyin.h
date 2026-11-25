#include <stddef.h>
typedef struct {
  const char *name;
  const int tone[2];
  int num_tones;
} Pinyin;

extern Pinyin active_tones[];
extern const size_t active_tones_count;
