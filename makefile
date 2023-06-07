workspace := /home/dev/simat
lib       := $(workspace)/core/lib
i         := $(workspace)/core/include
ib        := $(workspace)/core/include/open_blas
st        := $(workspace)/core/simat
test      := $(workspace)/test
blas      := /opt/OpenBLAS/lib/libopenblas.a

cc	      := gcc
ar        := ar
flag      := -std=c99 -lpthread

simat.a: libbasic.a
	$(cc) $(flag) -I$(i)/simat -c $(st)/distance.c -o $(lib)/distance.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/stats.c -o $(lib)/stats.o
	cd $(lib); $(ar) -x libbasic.a
	$(ar) rcs $(lib)/libsimat.a $(lib)/ds.o \
								$(lib)/watcher.o \
								$(lib)/dtypes.o \
								$(lib)/copy.o \
								$(lib)/elemental.o \
								$(lib)/matrix.o \
								$(lib)/vector.o \
								$(lib)/view.o \
								$(lib)/dataset.o \
								$(lib)/basic.o \
								$(lib)/distance.o \
								$(lib)/stats.o

libbasic.a:
	$(cc) $(flag) -I$(i)/simat -c $(st)/ds.c -o $(lib)/ds.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/watcher.c -o $(lib)/watcher.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/dtypes.c -o $(lib)/dtypes.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/copy.c -o $(lib)/copy.o
	$(cc) $(flag) -I$(i)/simat -I$(ib) -c $(st)/elemental.c -o $(lib)/elemental.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/matrix.c -o $(lib)/matrix.o
	$(cc) $(flag) -I$(i)/simat -I$(ib) -c $(st)/vector.c -o $(lib)/vector.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/view.c -o $(lib)/view.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/dataset.c -o $(lib)/dataset.o
	$(cc) $(flag) -I$(i)/simat -c $(st)/basic.c -o $(lib)/basic.o
	$(ar) rcs $(lib)/libbasic.a $(lib)/ds.o \
								$(lib)/watcher.o \
								$(lib)/dtypes.o \
								$(lib)/copy.o \
								$(lib)/elemental.o \
								$(lib)/matrix.o \
								$(lib)/vector.o \
								$(lib)/view.o \
								$(lib)/dataset.o \
								$(lib)/basic.o

test_simat.o: simat.a
	$(cc) -I$(i) -I$(i)/simat -I$(test) \
								$(test)/test_vector.c \
								$(test)/test_matrix.c \
								$(test)/test_stats.c \
								$(test)/test_distance.c \
								$(test)/test_simat.c -L$(lib) -lsimat -lm $(blas) $(flag) -o $(lib)/test_simat.o

test_basic.o: libbasic.a
	$(cc) -I$(i) -I$(i)/simat -I$(test) \
							    $(test)/test_vector.c \
								$(test)/test_matrix.c \
							    $(test)/test_basic.c \
								-L$(lib) -lsimat -lm $(flag) -o $(lib)/test_basic.o

.PHONY: clean

clean:
	rm -fr $(lib)/*.o $(lib)/*.a
