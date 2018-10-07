IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
CXXFLAGS=-std=c++11

ODIR=obj
LDIR=../lib

LIBS=-lm

# Input dependencies here (.h) files
_DEPS = frame.h split.h find_url.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = frame.o split.o find_url.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# $@ refers to target name
# $< refers to first
$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_frame: $(OBJ) obj/frame_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	./test_frame

permuted_index: $(OBJ) obj/permuted_index.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../text.txt | ./$@

palindrome: obj/palindrome.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../words.txt | ./$@

find_url_test: $(OBJ) obj/find_url_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../url_in_text.txt | ./$@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
