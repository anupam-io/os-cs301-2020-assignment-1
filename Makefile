all: compile run

compile: 
	gcc shell.c -o shell -lreadline
run:
	./shell
clean:
	rm -rf shell