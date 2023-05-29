workspace := /home/dev/simat
lib       := $(workspace)/core/lib
i         := $(workspace)/core/include
st        := $(workspace)/core/simat
test      := $(workspace)/test

cc	      := gcc
ar        := ar
flag      := -std=c99

simat.a: libbasic.a
	$(cc) $(flag) -I$(i)/simat -c $(st)/distance.c -o $(lib)/distance.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/stats.c -o $(lib)/stats.o
	cd $(lib); $(ar) -x libbasic.a
	$(ar) -rcs libsimat.a $(lib)/*.o
	rm $(lib)/*.o

test_vector.o: libbasic.a
	$(cc) $(test)/test_vector.c -I$(i) -I$(i)/simat -L$(lib) -lbasic -lm -o $(lib)/test_vector.o
	rm $(lib)/libbasic.a

libbasic.a:
	$(cc) $(flag) -I$(i)/simat -c $(st)/inspector.c -o $(lib)/inspector.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/dtypes.c -o $(lib)/dtypes.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/matrix.c -o $(lib)/matrix.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/vector.c -o $(lib)/vector.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/view.c -o $(lib)/view.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/basic.c -o $(lib)/basic.o
	$(ar) rcs $(lib)/libbasic.a $(lib)/inspector.o\
								$(lib)/dtypes.o\
								$(lib)/matrix.o\
								$(lib)/vector.o\
								$(lib)/view.o\
								$(lib)/basic.o
	rm $(lib)/*.o


.PHONY: clean

clean:
	rm -fr $(lib)/*.o $(lib)/*.a
