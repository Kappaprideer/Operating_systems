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



test_static_O:
	make static
	$(CC) -O $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_O.txt
test_shared_O:
	make shared
	$(CC) -O $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_O.txt

test_dynamic_O:
	make dynamic
	./main < ./test_files/test.txt > ./test_files/result_dynamic_O.txt





test_static_O1:
	make static
	$(CC) -O1 $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_O1.txt
test_shared_O1:
	make shared
	$(CC) -O1 $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_O1.txt




test_static_O2:
	make static
	$(CC) -O2 $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_O2.txt
test_shared_O2:
	make shared
	$(CC) -O2 $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_O2.txt




test_static_O3:
	make static
	$(CC) -O3 $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_O3.txt
test_shared_O3:
	make shared
	$(CC) -O3 $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_O3.txt


test_static_O0:
	make static
	$(CC) -O0 $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_O0.txt
test_shared_O0:
	make shared
	$(CC) -O0 $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_O0.txt



test_static_Os:
	make static
	$(CC) -Os $(FLAGS) main.c -o main -L. -l$(SHORT_LIB_NAME)
	./main < ./test_files/test.txt > ./test_files/result_static_Os.txt
test_shared_Os:
	make shared
	$(CC) -Os $(FLAGS) main.c -l$(SHORT_LIB_NAME) -L. -o main
	./main < ./test_files/test.txt > ./test_files/result_shared_Os.txt

test_all_static:
	make test_static_O
	make test_static_O1
	make test_static_O2
	make test_static_O3
	make test_static_O0
	make test_static_Os

test_all_shared:
	make test_shared_O
	make test_shared_O1
	make test_shared_O2
	make test_shared_O3
	make test_shared_O0
	make test_shared_Os

all:
	make test_all_static
	make test_all_shared
