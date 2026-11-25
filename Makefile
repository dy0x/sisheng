CC = cc
SANITIZE = -fsanitize=address,undefined
CFLAGS = -std=c2x -pedantic -O0 -g -Wall -Wextra -Wshadow -Wconversion $(SANITIZE)
LDFLAGS = $(SANITIZE)
TARGET = build/sisheng

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/%.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
	@rmdir build 2>/dev/null || true

-include $(DEPS)

.PHONY: all run clean
