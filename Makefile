src = $(wildcard src/*.c)
obj = $(src:.c=.o)

CCFLAGS = -pthread -Wall -O2

aire: $(obj)
	$(CC) $(CCFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) aire
