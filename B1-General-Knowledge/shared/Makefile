.PHONY:all clean my_objs my_shared install

my_objs:
	gcc -c ./main.c -o ./objs/main.o -I ./inc
	gcc -c -fPIC ./src/hello_class.c -o ./objs/hello_class.o -I ./inc
	gcc -c -fPIC ./src/hello_world.c -o ./objs/hello_world.o -I ./inc
my_shared:
	gcc -shared ./objs/hello_class.o ./objs/hello_world.o -o ./libs/shared/libmd.so
install:
	cp -f ./libs/shared/libmd.so /usr/lib 
all:my_objs my_shared install
	gcc ./objs/main.o -L./libs/shared -lmd -o ./bin/use-shared-library
clean:
	rm -rf ./objs/*
	rm -rf ./libs/shared/libmd.so
	rm -rf ./bin/use-shared-library