C = gcc
CFLAGS =  -O3 -Wall

SOURCES=rdft_ad.c hw_trig.c
OBJECTS=$(SOURCES:.c=.o)
EXEC = rdft_ad


EXEC: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXEC) $(OBJECTS)
