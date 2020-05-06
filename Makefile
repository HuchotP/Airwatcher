# CFLAGS = -O3  (for best performance)
# CFLAGS = -g   (for debugging)
CFLAGS = -g -Wall

LIBS = -lm


all: Airwatcher

Airwatcher: src/main.c
	g++ $(CFLAGS) -o bin/Airwatcher main.c $(LIBS)

clean:
	rm -f bin/*

.PHONY: all clean