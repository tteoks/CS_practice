CC=gcc
TARGET = main
OBJS= $(BUILD_DIR)/sort_lib.o $(BUILD_DIR)/utils.o
NUM_ARRAY=5000
BUILD_DIR=libs

ALL : $(TARGET)

$(BUILD_DIR)/sort_lib.o: ./src/sort_lib.c $(BUILD_DIR)
	$(CC) -c -g -o ./libs/sort_lib.o -I./include ./src/sort_lib.c

$(BUILD_DIR)/utils.o: ./src/utils.c $(BUILD_DIR)
	$(CC) -c -g -o ./libs/utils.o -I./include ./src/utils.c

$(TARGET) : $(OBJS) main.c
	$(CC) -o main -I./include -L./libs -lsort_lib.o -lutils.o -g main.c -DNUM_ARRAY=$(NUM_ARRAY)

$(BUILD_DIR): 
	mkdir $(BUILD_DIR)

clean: 
	rm -f ./libs/* $(TARGET)
