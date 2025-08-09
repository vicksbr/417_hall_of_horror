CFLAGS=-Wall -g

CC=gcc
SOURCES=417game.c object.c
EXECUTABLE=417hallofhorror

linux: $(SOURCES)
	$(CC) -o $(EXECUTABLE) $(SOURCES)

windows: $(SOURCES)
	x86_64-w64-mingw32-gcc -o $(EXECUTABLE).exe $(SOURCES)

clean:
	rm -f *.o $(EXECUTABLE) $(EXECUTABLE).exe
