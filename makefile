workspace := /home/dev/simat
lib       := $(workspace)/core/lib
i         := $(workspace)/core/include
ib        := $(workspace)/core/include/open_blas
st        := $(workspace)/core/simat
ds        := $(workspace)/core/dataset
test      := $(workspace)/test
blas      := /opt/OpenBLAS/lib/libopenblas.a

cc	      := gcc
ar        := ar
flag      := -std=c99 -lpthread


test_simat.o: simat.a dataset.a
	$(cc) -I$(i) -I$(ds) -I$(st) -I$(st)/basic -I$(test) \
								$(test)/test_vector.c \
								$(test)/test_matrix.c \
								$(test)/test_stats.c \
								$(test)/test_distance.c \
								$(test)/test_simat.c -L$(lib) -lsimat -lds -lm $(blas) $(flag) -o $(lib)/test_simat.o

dataset.a: simat.a
	mkdir -p $(lib)/dataset
	$(cc) $(flag) -I$(i) -I$(st) -I$(st)/basic -c $(ds)/st_dataset.c -o $(lib)/dataset/st_dataset.o
	$(ar) rcs $(lib)/libds.a $(lib)/dataset/st_dataset.o \


simat.a:
	mkdir -p $(lib)/simat
	$(cc) $(flag) -c $(st)/basic/st_ds.c -o $(lib)/simat/st_ds.o
	$(cc) $(flag) -c $(st)/basic/st_watcher.c -o $(lib)/simat/st_watcher.o
	$(cc) $(flag) -c $(st)/basic/st_dtypes.c -o $(lib)/simat/st_dtypes.o
	$(cc) $(flag) -c $(st)/basic/st_copy.c -o $(lib)/simat/st_copy.o
	$(cc) $(flag) -I$(ib) -c $(st)/basic/st_elemental.c -o $(lib)/simat/st_elemental.o
	$(cc) $(flag) -c $(st)/basic/st_vector.c -o $(lib)/simat/st_vector.o
	$(cc) $(flag) -c $(st)/basic/st_matrix.c -o $(lib)/simat/st_matrix.o
	$(cc) $(flag) -c $(st)/basic/st_view.c -o $(lib)/simat/st_view.o
	$(cc) $(flag) -c $(st)/basic/st_basic.c -o $(lib)/simat/st_basic.o
	$(cc) $(flag) -c $(st)/st_distance.c -o $(lib)/simat/st_distance.o
	$(cc) $(flag) -c $(st)/st_stats.c -o $(lib)/simat/st_stats.o

	$(ar) rcs $(lib)/libsimat.a $(lib)/simat/st_ds.o \
								$(lib)/simat/st_watcher.o \
								$(lib)/simat/st_dtypes.o \
								$(lib)/simat/st_copy.o \
								$(lib)/simat/st_elemental.o \
								$(lib)/simat/st_vector.o \
								$(lib)/simat/st_matrix.o \
								$(lib)/simat/st_view.o \
								$(lib)/simat/st_basic.o \
								$(lib)/simat/st_distance.o \
								$(lib)/simat/st_stats.o


.PHONY: clean


clean:
	rm -fr $(lib)/*
