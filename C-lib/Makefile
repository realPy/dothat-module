
LIB_FILES = sn3218.c st7036.c cap1166.c dothat.o

LIBOFILES = $(LIB_FILES:%.c=%.o)

all : libdothat.a

libdothat.a: $(LIBOFILES)
	rm -f $@
	ar cq $@ $(LIBOFILES)
