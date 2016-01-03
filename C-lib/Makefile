
LIB_FILES = sn3218.c st7036.c cap1166.c dothat.o

LIBOFILES = $(LIB_FILES:%.c=%.o)

all : libdothat.a test

libdothat.a: $(LIBOFILES)
	rm -f $@
	ar cq $@ $(LIBOFILES)

test: test.c libdothat.a
	cc -o test test.c -L. -ldothat
