.PHONY:all clean run

all:
	gcc -o app main.c -pthread -g 
run:
	valgrind --leak-check=full  --show-leak-kinds=all  --track-origins=yes  --verbose  --log-file=valgrind-out.txt ./app
clean:
	rm -rf app valgrind-out.txt