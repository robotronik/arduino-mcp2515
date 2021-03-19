CC=gcc
CP=g++
CFLAGS=-Wall -O
LDFLAGS=
EXEC=main.out
SRC=$(wildcard *.c *.cpp)
SRP=$(SRC:.c=.o)
OBJ=$(SRP:.cpp=.o)
all: $(EXEC)
main.out: $(OBJ)
				$(CP) -o $@ $^ $(LDFLAGS)
%.o: %.c
				$(CC) -o $@ -c $< $(CFLAGS)
%.o: %.cpp
				$(CP) -o $@ -c $< $(CFLAGS)
clean:
				rm -f *.o core
mrproper: clean
				rm -f $(EXEC)
