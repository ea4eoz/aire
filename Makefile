src = $(wildcard src/*.c)
obj = $(src:.c=.o)

CFLAGS = -Wall -O2

aire: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) aire
