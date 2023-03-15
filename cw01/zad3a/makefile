CC = gcc
FLAGS = -Wall
LIB_NAME = lib_one
SHORT_LIB_NAME = _one
SOURCE_NAME = library

static_lib:
	$(CC) $(FLAGS) -c $(SOURCE_NAME).c -o  $(LIB_NAME).o
	ar rcs $(LIB_NAME).a $(LIB_NAME).o
	make clean

shared_lib:
	$(CC) -fPIC $(FLAGS) -c $(SOURCE_NAME).c -o $(LIB_NAME).o
	$(CC) -shared -fPIC $(FLAGS) -o $(LIB_NAME).so $(LIB_NAME).o
	make clean

static:
	make static_lib
	$(CC) $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)

shared:
	make shared_lib
	$(CC) $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main

dynamic:
	make shared_lib
	$(CC) $(FLAGS) -I. main.c -ldl -D DYNAMIC -o main

clean:
	rm -f *.o

clean_all:
	rm -f *.so
	rm -f *.a
	rm -f *.o
	rm -r main

set_path:
	export LD_LIBRARY_PATH=/home/endrew/Github/Operating_systems/cw01/zad3a/

test_static:
	make static
	./main < ./test_files/test.txt > ./test_files/result_static.txt

test_shared:
	make shared
	./main < ./test_files/test.txt > ./test_files/result_shared.txt

test_dynamic:
	make dynamic
	./main < ./test_files/test.txt > ./test_files/result_dynamic.txt

all:
	make test_static
	make test_shared
