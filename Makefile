
CFLAGS = -g
SRC = src/**/*.c src/main.c

all: output build

output:
	mkdir -p result

build: src/main.c
	cc $(CFLAGS) $(SRC) -o result/daisy

run: output build
	result/daisy

debug: output build
	gdb result/daisy

clean:
	rm -rf result
