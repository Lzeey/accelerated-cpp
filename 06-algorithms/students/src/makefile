IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
CXXFLAGS=-std=c++11

ODIR=obj
LDIR=../lib

LIBS=-lm

# Input dependencies here (.h) files
_DEPS = grade.h median.h Student_info.h analysis.h average.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = grade.o median.o Student_info.o analysis.o average.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# $@ refers to target name
# $< refers to first
$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analysis: $(OBJ) obj/quick_analysis.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../grades.txt | ./$@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
