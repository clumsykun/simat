workspace := /home/dev/simat
include := $(workspace)/core/include
src := $(workspace)/core/simat
test := $(workspace)/test
lib := $(workspace)/core/lib


# simat.a: inspector.o
# 	ar rcs simat.a inspector.o

test_inspector.o: inspector.a
	gcc $(test)/test_inspector.c -I$(include)/simat -L$(lib) -lins -o $(lib)/test_inspector.o

inspector.a:
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/inspector.c -o $(lib)/inspector.o
	ar rcs $(lib)/libins.a $(lib)/inspector.o

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