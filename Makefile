
OBJS=papertape.o main.o

CC=cc

all: papertape

papertape: $(OBJS)
	$(CC) -o $@ $?

%.o:%.c
	$(CC) -c -o $@ $^

.PHONY: clean

clean:
	@rm -f $(OBJS)
	@rm -f papertape
