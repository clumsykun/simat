workspace := /home/dev/simat
include := $(workspace)/core/include
src := $(workspace)/core/simat
test := $(workspace)/test
lib := $(workspace)/core/lib


# simat.a: inspector.o
# 	ar rcs simat.a inspector.o

inspector.o:
	gcc -lm -std=c99 -I$(include)/simat -c $(src)/inspector.c -o $(lib)/inspector.o

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