workspace   := /home/dev/simat
lib         := $(workspace)/core/lib
i           := $(workspace)/core/include
ib          := $(workspace)/core/include/open_blas
st          := $(workspace)/core/simat
ds          := $(workspace)/core/dataset
test        := $(workspace)/test
OpenBLAS    := /opt/OpenBLAS/lib/libopenblas.a

cc	        := gcc
ar          := ar
flag        := -std=c99 -pthread -msse4.1


test_simatall: cc_simat cc_dataset
	$(ar) rcs $(lib)/libsimatall.a $(lib)/simat/*.o $(lib)/dataset/*.o
	$(cc) -I$(i) -I$(ds) -I$(st) -I$(st)/basic -I$(test) \
								$(test)/test_vector.c \
								$(test)/test_matrix.c \
								$(test)/test_stats.c \
								$(test)/test_distance.c \
								$(test)/test.c \
								-L$(lib) -lsimatall -lm $(flag) $(OpenBLAS) \
								-o $(lib)/test_simatall.o

simatall: unpack_OpenBLAS cc_simat cc_dataset
	$(ar) rcs $(lib)/libsimatall.a $(lib)/OpenBLAS/*.o $(lib)/simat/*.o $(lib)/dataset/*.o

simat: cc_simat unpack_OpenBLAS
	$(ar) rcs $(lib)/libsimat.a $(lib)/OpenBLAS/*.o $(lib)/simat/*.o

cc_dataset:
	mkdir -p $(lib)/dataset
	$(cc) $(flag) -I$(i) -I$(st) -I$(st)/basic -c $(ds)/st_dataset.c -o $(lib)/dataset/st_dataset.o

cc_simat:
	mkdir -p $(lib)/simat
	$(cc) $(flag) -c $(st)/basic/st_b_ds.c -o $(lib)/simat/st_b_ds.o
	$(cc) $(flag) -c $(st)/basic/st_b_watcher.c -o $(lib)/simat/st_b_watcher.o
	$(cc) $(flag) -c $(st)/basic/st_c_struct.c -o $(lib)/simat/st_c_struct.o
	$(cc) $(flag) -c $(st)/basic/st_c_copy.c -o $(lib)/simat/st_c_copy.o
	$(cc) $(flag) -I$(ib) -c $(st)/basic/st_c_elemental.c -o $(lib)/simat/st_c_elemental.o
	$(cc) $(flag) -c $(st)/basic/st_d_vector.c -o $(lib)/simat/st_d_vector.o
	$(cc) $(flag) -c $(st)/basic/st_d_matrix.c -o $(lib)/simat/st_d_matrix.o
	$(cc) $(flag) -c $(st)/basic/st_d_view.c -o $(lib)/simat/st_d_view.o
	$(cc) $(flag) -c $(st)/basic/st_basic.c -o $(lib)/simat/st_basic.o
	$(cc) $(flag) -c $(st)/st_distance.c -o $(lib)/simat/st_distance.o
	$(cc) $(flag) -c $(st)/st_stats.c -o $(lib)/simat/st_stats.o

unpack_OpenBLAS:
	mkdir -p $(lib)/OpenBLAS
	ar -x $(OpenBLAS) --output /home/dev/simat/core/lib/OpenBLAS


.PHONY: clean


clean:
	rm -rf $(lib)/*
