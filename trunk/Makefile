#CC=gcc
CC=arm-linux-gcc
AS=arm-linux-as
STRIP =arm-linux-strip
EXEC = yuv2jpg
OBJS = main.o encoder.o dct.o marker.o readYUV.o quant.o huffman.o translate.o

CFLAGS += -DPOSIX -O3 -march=armv4 -mtune=arm9tdmi
#CFLAGS = -DPOSIX -g

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS) -lm
	$(STRIP) $(EXEC)
	cp $(EXEC) /tmp

%.o: %.s
	$(AS) -o $*.o $<
	
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o *.bak

