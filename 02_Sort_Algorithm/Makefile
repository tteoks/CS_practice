CC=gcc
TARGET = main
OBJS= sort_lib.o utils.o
NUM_ARRAY=1020

ALL : $(TARGET)

sort_lib.o: ./src/sort_lib.c
	$(CC) -c -g -o ./libs/sort_lib.o -I./include ./src/sort_lib.c

utils.o: ./src/utils.c
	$(CC) -c -g -o ./libs/utils.o -I./include ./src/utils.c

$(TARGET) : $(OBJS) main.c
	$(CC) -o main -I./include -L./libs -lsort_lib.o -lutils.o -g main.c -DNUM_ARRAY=$(NUM_ARRAY)

clean: 
	rm -f ./libs/* $(TARGET)
