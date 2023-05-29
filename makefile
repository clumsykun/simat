workspace := /home/dev/simat
include := $(workspace)/core/include
src := $(workspace)/core/simat
test := $(workspace)/test
lib := $(workspace)/core/lib


# simat.a: inspector.o
# 	ar rcs simat.a inspector.o

# test_vector.o: basic.a
# 	gcc $(test)/test_vector.c \
# 	-I$(include) \
# 	-I$(include)/simat \
# 	-L$(lib) -lbasic \
# 	-o $(lib)/test_vector.o

# basic.a:
# 	gcc -lm -std=c99 -I$(include)/simat -fpic -shared \
# 	-c $(src)/inspector.c \
# 	   $(src)/dtypes.c \
# 	   $(src)/vector.c \
# 	   $(src)/matrix.c \
# 	   $(src)/view.c \
# 	   $(src)/basic.c \

# 	ar rcs $(lib)/libbasic.a \
# 	   $(src)/inspector.o 
# 	   $(src)/dtypes.o \
# 	   $(src)/vector.o \
# 	   $(src)/matrix.o \
# 	   $(src)/view.o \
# 	   $(src)/basic.o \

# SOURCE      :=inspector.c
# OBJS        :=division.o
# TARGET      :=libc_a.a

# #compile and lib parameter
# CC			:=gcc
# LIBS        :=
# LDFLAGS     :=-L
# DEFINES     :=
# INCLUDE     :=-I
# CFLAGS      :=
# CXXFLAGS    :=

# #link parameter
# AR          :=ar;

# #link
# $(TARGET):$(OBJS)
# #注意下面的命令需要先使用    Tab       键,再输入命令
# 	$(AR) -r $@ $^ 

# #complie
# $(OBJS):$(SOURCE)
# 	$(CC) -c $^ -o $@
# #clear
# 	rm -fr *.o


test_vector.o: basic.a
	gcc $(test)/test_vector.c \
	-I$(include) \
	-I$(include)/simat \
	-L$(lib) -lbasic -lm \
	-o $(lib)/test_vector.o

simat.a: basic.a
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/distance.c -o $(lib)/distance.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/stats.c -o $(lib)/stats.o
	ar rcs $(lib)/libsimat.a $(lib)/libbasic.a $(lib)/distance.o $(lib)/distance.o

basic.a:
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/inspector.c -o $(lib)/inspector.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/dtypes.c -o $(lib)/dtypes.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/matrix.c -o $(lib)/matrix.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/vector.c -o $(lib)/vector.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/view.c -o $(lib)/view.o
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/basic.c -o $(lib)/basic.o
	ar rcs $(lib)/libbasic.a \
	$(lib)/inspector.o \
	$(lib)/dtypes.o \
	$(lib)/matrix.o \
	$(lib)/vector.o \
	$(lib)/view.o \
	$(lib)/basic.o

.PHONY: clean
clean:
	rm -fr $(lib)/*.o $(lib)/*.a
