OBJ = src/main.o src/list.o src/P11.o src/P12.o src/P21.o src/P22.o src/P23.o
FLAGS = -Wall -Iinclude -std=c99
EXE = run

all: $(OBJ)
	gcc $(OBJ) $(FLAGS) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

%.o : %.c
	gcc -c $*.c $(FLAGS) -o $*.o