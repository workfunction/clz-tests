CC ?= gcc
CFLAGS_common = -std=gnu99 
CFLAGS_omp = -fopenmp -lgomp

SRC_common := src/main.c

SRC := $(filter-out src/main.c, $(wildcard src/*))
EXEC := $(addprefix bin/, $(basename $(notdir $(SRC))))

.PHONY: all bin clean check run plot

all : bin $(EXEC)

check :
	make --eval=CHK=1

bin :
	mkdir -p bin

bin/% : $(SRC_common) src/%.c
ifeq ($(CHK), 1)
	$(CC) $(CFLAGS_common) $(CFLAGS_omp) -DCHK $^ -I./inc/ -o $@
else
	$(CC) $(CFLAGS_common) -DFUNC='"$*"' $^ -I./inc/ -o $@
endif

clean :
	rm -rf bin output
	rm -f result.png

run :
	mkdir -p output
	./bin/clz_binary_search
	./bin/clz_byte_shift
	./bin/clz_Harley
	./bin/clz_iteration
	./bin/clz_recursive

plot : clean run $(wildcard output/*)
	gnuplot script/plot.gp
	eog result.png

