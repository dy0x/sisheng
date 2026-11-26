CC = cc
SANITIZE = -fsanitize=address,undefined
CFLAGS = -std=c23 -pedantic -O0 -g -Wall -Wextra -Wshadow -Wconversion $(SANITIZE)
LDFLAGS = $(SANITIZE)
TARGET = build/sisheng

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=build/%.o)
DEPS = $(OBJS:.o=.d)

TEST_SRCS = $(wildcard tests/test_*.c)
TEST_BINS = $(patsubst tests/%.c,build/%,$(TEST_SRCS))
LIB_OBJS = $(filter-out build/main.o,$(OBJS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) $(TEST_BINS)
	@rmdir build 2>/dev/null || true

test: $(TEST_BINS)
	for t in $(TEST_BINS); do ./$$t || exit 1; done

build/test_%: tests/test_%.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

-include $(DEPS)

.PHONY: all run clean test
