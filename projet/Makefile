CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm -lSDL2_mixer

INC = sdl2-light.h graphismes.h donnes.h initialisation.h audio.h
SRC = main.c sdl2-light.c sdl2-ttf-light.c graphismes.c donnes.c initialisation.c audio.c
SRCTEST = tests.c donnes.c
OBJ = $(SRC:%.c=%.o)
OBJTEST = $(SRCTEST:%.c=%.o)

PROG = spacebattle
PROGTEST = test

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG) $(PROGTEST)
	rm -rf latex html

test: $(OBJTEST)
	gcc $(CFLAGS) $(OBJTEST) $(LDFLAGS) -o $@ -Wall