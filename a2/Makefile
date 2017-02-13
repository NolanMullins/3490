OBJQ1 = main.o
OBJQ2 = q2.o
OBJ = main.o P11.o P12.o P21.o P22.o gen.o
OBJ2 = $(OBJ:.o=.tmp)
FLAGS =-Wall -Iinclude -std=c99

# -pthread

all: $(OBJ2)

%.tmp: %.o
	gcc $*.o $(FLAGS) -o $*

%.o : %.c
	gcc -c $*.c $(FLAGS) -o $*.o

run: test1 test2

test1:
	./P21
test2:
	./P22

#q2: $(OBJQ2) 
#	gcc $(OBJQ2) -o q2 $(FLAGS)

#q1: $(OBJQ1) 
#	gcc $(OBJQ1) -o $(EXE1) $(FLAGS)

clean:
	rm $(OBJQ1) $(OBJQ2) $(EXE2) $(OBJ) $(OBJ2:.tmp=)

#run:
#	./$(EXE)

#%.o: src/$*.c
#	gcc -c src/$*.c $(FLAGS) -o $*.o
#q2.o : src/q2.c
#	gcc -c src/$*.c $(FLAGS) -o $*.o
#main.o : src/main.c
#	gcc -c src/$*.c $(FLAGS) -o $*.o