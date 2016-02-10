CC = gcc
CSTD = c99

GUILE_CFLAGS = $(shell pkg-config guile-2.0 --cflags)
SDL_CFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -g -W -Wall -pedantic -std=$(CSTD) $(SDL_CFLAGS) $(GUILE_CFLAGS)

GUILE_LDFLAGS = $(shell pkg-config guile-2.0 --libs)
SDL_LDFLAGS = $(shell sdl2-config --libs)
LDFLAGS = -lGL -lGLEW -lm -lpng -lz  $(SDL_LDFLAGS) $(GUILE_LDFLAGS)

SOURCES = $(shell find . -name '*.c')
DEPS = $(shell find . -name '*.h')
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
EXECUTABLE = test

$(EXECUTABLE): pre $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

pre:
	@echo -e "C compiler: \t" $(CC) 
	@echo -e "C flags: \t" $(CFLAGS)
	@echo -e "Library flags: \t" $(LDFLAGS)

%.o: %.c $(DEPS)
	@echo "Building" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(EXECUTABLE)
