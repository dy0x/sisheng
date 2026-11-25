#include "pinyin.h"
#include <stddef.h>

Pinyin active_tones[2] = {{.name = "hao3", .tone = {3}, .num_tones = 1},
                          {.name = "hao3", .tone = {3}, .num_tones = 1}};

const size_t active_tones_count =
    sizeof(active_tones) / sizeof(active_tones[0]);
