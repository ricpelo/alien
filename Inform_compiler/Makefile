SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

.PHONY: clean all

all: inform

$(OBJ): %.o: %.c
	gcc $(CFLAGS) -DLINUX -Wall -Wextra -Wno-uninitialized $^ -c -o $@

inform: $(OBJ)
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -f *.o inform
