CC := gcc
CFLAGS := -g
INCLUDE := -I ~/project/libsense/include
LDFLAGS := -L ~/project/libsense/lib -lsense -lm
DEPS := project.h

%.o: %.c $(DEPS)
	        $(CC) -c $(CFLAGS) $< $(INCLUDE)

all: project inputtest outputtest

project: main.o input.o output.o framebuffer.o
	$(CC) -o game $(INCLUDE) main.o input.o output.o $(LDFLAGS)

inputtest: inputtest.o input.o
	$(CC) -o inputtest $(INCLUDE) input.o inputtest.o $(LDFLAGS)

outputtest: outputtest.o output.o
	$(CC) -o outputtest $(INCLUDE) output.o outputtest.o  $(LDFLAGS)

clean:
	        rm game inputtest outputtest input.o output.o main.o inputtest.o outputtest.o

