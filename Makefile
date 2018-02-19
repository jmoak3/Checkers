IDIR =./include
CC=g++
CFLAGS=-I$(IDIR) -std=c++17

ODIR=./obj
SRCDIR=./src

_DEPS = Board.h Piece.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Checkers.o Board.o Piece.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TESTOBJ = Test.o Board.o Piece.o 
TESTOBJ = $(patsubst %,$(ODIR)/%,$(_TESTOBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

checkermake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

test: $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS) 


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core