# CFLAGS = -O3  (for best performance)
# CFLAGS = -g   (for debugging)
CFLAGS = -g -Wall

LIBS = -lm


all: Airwatcher

Airwatcher: ./src/main.cpp
	g++ $(CFLAGS) -o bin/Airwatcher $^ $(LIBS)

clean:
	rm -f bin/*

.PHONY: all clean