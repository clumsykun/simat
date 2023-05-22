workspace := /home/dev/simat
simat_include := $(workspace)/core/include
simat_src := $(workspace)/core/simat
simat_test := $(workspace)/test
simat_lib := $(workspace)/core/Lib

test_inspector.o:
	gcc -lm -std=c99 -I$(simat_include)/simat $(simat_src)/inspector.c $(simat_test)/test_inspector.c -o $(simat_lib)/test_flags.o

test_vector.o:
	gcc -lm -std=c99 -I$(simat_include)/simat -I$(simat_include) \
	$(simat_src)/inspector.c \
	$(simat_src)/dtypes.c \
	$(simat_src)/vector.c \
	$(simat_src)/basic.c \
	$(simat_test)/test_vector.c \
	-o \
	$(simat_lib)/test_vector.o
clean:
	rm $(workspace)/core/Lib/*.o
