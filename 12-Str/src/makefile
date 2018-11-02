IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
CXXFLAGS=-std=c++17
WARNING=-Werror=return-type # Enforce all functions to have returns

ODIR=obj
LDIR=../lib

LIBS=-lm

# Input dependencies here (.h) files
_DEPS = Vec.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Vec.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# $@ refers to target name
# $< refers to first
$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS) $(WARNING)

test_vec: obj/test_vec.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	./test_vec

test_list: obj/test_list.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	./test_list

test_str: obj/test_str.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	./test_str

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
