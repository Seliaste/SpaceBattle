CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h
SRC = main.c sdl2-light.c src/game_logic.c src/graphics.c
SRCTEST = src/tests/tests.c src/game_logic.c
OBJ = $(SRC:%.c=%.o)
OBJTEST = $(SRCTEST:%.c=%.o)

PROG = spacebattle

PROGTEST = tests

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $< -o $@

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

tests: $(OBJTEST)
	gcc $(CFLAGS) $(OBJTEST) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ $(OBJ) $(OBJTEST) $(PROG) $(PROGTEST)
	rm -rf latex html

