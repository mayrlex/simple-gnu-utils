CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET_CAT = gcat
TARGET_GREP = ggrep

ROOT = src

CAT_SRCS = $(wildcard $(ROOT)/cat/*.c)
CAT_OBJS = $(patsubst %.c, %.o, $(CAT_SRCS))
CAT_HEADERS = $(wildcard $(ROOT)/cat/*.h)

GREP_SRCS = $(wildcard $(ROOT)/grep/*.c)
GREP_OBJS = $(patsubst %.c, %.o, $(GREP_SRCS))
GREP_HEADERS = $(wildcard $(ROOT)/grep/*.h)

RAWS = $(CAT_SRCS) $(GREP_SRCS) $(CAT_HEADERS) $(GREP_HEADERS)

all: $(TARGET_CAT) $(TARGET_GREP)

cat: $(TARGET_CAT)

grep: $(TARGET_GREP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_CAT): $(CAT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET_GREP): $(GREP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test-cat:
	@echo ">>> Running tests for \"cat\""
	./test/cat/test_max_coverage.sh

test-grep:
	@echo ">>> Running tests for \"grep\""
	./test/grep/test.sh

clang:
	clang-format --dry-run --Werror $(RAWS) || clang-format -i $(RAWS)

clang-check:
	clang-format -n $(RAWS)

clean:
	rm $(TARGET_CAT) $(TARGET_GREP) $(ROOT)/cat/*.o $(ROOT)/grep/*.o

rebuild: clean all

.PHONY: all clang clang-check clean rebuild test-cat test-grep cat grep