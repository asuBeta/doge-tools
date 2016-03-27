# Makefile

GCC			= gcc

CFLAGS		= -Wall -fPIC -c
LDFLAGS		= -shared -o

LIB_NAME 	= libw9099s01

SRC_1		= w9099s01.c
SRC_ALL		= $(SRC_1)

OBJ_1		= w9099s01.o
OBJ_ALL		= $(OBJ_1)

SHARE_LIB	= $(LIB_NAME).so

all:$(OBJ_ALL)
	$(GCC) $(OBJ_ALL) $(LDFLAGS) $(SHARE_LIB)

$(OBJ_1):$(SRC_1)
	$(GCC) $(CFLAGS) $(SRC_1) -o $(OBJ_1)

clean:
	rm -rf *.o *.so
