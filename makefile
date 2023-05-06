workspace := /home/dev/simat
simat_include := $(workspace)/core/include
simat_src := $(workspace)/core/simat
simat_test := $(workspace)/test
simat_lib := $(workspace)/core/Lib

test_flags.o:
	gcc -lm -std=c99 -I$(simat_include)/simat $(simat_src)/flags.c $(simat_test)/test_flags.c -o $(simat_lib)/test_flags.o
clean:
	rm $(workspace)/core/Lib/*.o
