CC = gcc
CSTD = c99

SDL_CFLAGS = $(shell sdl2-config --cflags)
CF = $(CFLAGS) -std=c99

f_obj.o: f_obj.c f_obj.h
	$(CC) $(CF) -c -o $@ $<

f_png.o: f_png.c f_png.h
	$(CC) $(CF) -c -o $@ $<

g_lsl.o: g_lsl.c g_lsl.h
	$(CC) $(CF) $(SDL_CFLAGS) -c -o $@ $<

v_3dt.o: v_3dt.c v_3dt.h
	$(CC) $(CF) -c -o $@ $<

vects.o: vects.c vects.h
	$(CC) $(CF) -c -o $@ $<
