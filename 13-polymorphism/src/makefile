IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
CXXFLAGS=-std=c++17
WARNING=-Werror=return-type # Enforce all functions to have returns

ODIR=obj
LDIR=../lib

LIBS=-lm

# Input dependencies here (.h) files
_DEPS = grade.h median.h Core.h Grad.h average.h Student_info.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = grade.o median.o Core.o Grad.o average.o Student_info.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# $@ refers to target name
# $< refers to first
$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS) $(WARNING)

main: $(OBJ) obj/main.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../mix_grades.txt | ./$@

test_core_only: $(OBJ) obj/test_core_only.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../grades.txt | ./$@

test_grad_only: $(OBJ) obj/test_grad_only.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS) $(LIBS)
	cat ../grades.txt | ./$@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
