CC ?= gcc
CFLAGS_common = -Wall -std=gnu99 -O0

SRC_common := src/main.c

SRC := $(filter-out src/main.c, $(wildcard src/*))
EXEC := $(addprefix bin/, $(basename $(notdir $(SRC))))

.PHONY: all bin clean
all : bin $(EXEC)

bin :
	mkdir -p bin

bin/% : $(SRC_common) src/%.c
	$(CC) $(CFLAGS_common) $^ -Iinc/ -o $@

clean :
	rm -rf bin
