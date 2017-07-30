SRC =   test.c \
				auth-api.c

OBJ = $(SRC:.c=.o)

CFLAGS = -W -Wall -Wextra -g3 --std=gnu99 -lrt
LDFLAGS = -ldl -lrt -Wl,--export-dynamic

test: test.out

test.out: $(OBJ)
	$(CC) $(OBJ) -o core.out $(CFLAGS) $(LDFLAGS)

all:
	$(CC) -fPIC -o auth-api.so auth-api.c -shared $(CFLAGS)

clean:
        rm -rfv $(OBJ) *.so *.o

.PHONY: all clean test
