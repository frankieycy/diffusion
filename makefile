all: main run clean plot

main: main.c
	@clang -o main main.c

run:
	@./main

clean:
	@rm -rf main

plot:
	@python plot.py
