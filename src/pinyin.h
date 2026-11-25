typedef struct {
  const char *name;
  const int tone[2];
  int num_tones;
} Pinyin;

extern Pinyin active_tones[];
