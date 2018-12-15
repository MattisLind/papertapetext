
OBJS=papertape.o main.o

CC=cc

all: papertape papertape-pdp11.abs

papertape: $(OBJS)
	$(CC) -o $@ $?

%.o:%.c
	$(CC) -c -o $@ $^

.PHONY: clean

clean:
	@rm -f $(OBJS)
	@rm -f papertape

papertape-pdp11.abs: papertape-pdp11.bin
	bin2abs $^ 0200 > $@

papertape-pdp11.bin: papertape-pdp11.o 
	pdp11-aout-objcopy -O binary $^ $@

# to get the rigt order in the binary crt0.s has to be the first file

papertape-pdp11.o: crt0.s papertape.c main-pdp11.c 
	pdp11-aout-gcc -Os -m10  -Ttext 80 -msoft-float  -nostartfiles  -nodefaultlibs  -nostdlib   $^  -o testplot.o

install:
	@cp papertape /usr/local/bin

space: 
	@dd if=/dev/zero of=$@ bs=1 count=20

leader:
	@echo "WWW.DATORMUSEUM.SE PAPER TAPE PRINTER" > tmp
	@papertape < tmp > $@
	@rm -f tmp 

punchedpapertape: leader space DEC-11-L2PC-PO.ptap space papertape-pdp11.abs space
	@ cat $^ > $@ 