CC = gcc
CFLAGS = -Wall -fpic -I./Inc -DDEBUG_PRINTS_ENABLED
DUT_SRC_PATH = ./Src
STUB_SRC_PATH = ./DriversPCSimulation
default: all

all: simulation.o \
	logger_circular_buffer.o \
	logger_keyboard.o

	$(CC) $(CFLAGS) -shared -o simulation.so simulation.o \
		logger_circular_buffer.o \
		logger_keyboard.o

main.o:  simulation.c
	$(CC) $(CFLAGS) -c simulation.c

logger_keyboard.o:  $(DUT_SRC_PATH)/logger_keyboard.c
	$(CC) $(CFLAGS) -c $(DUT_SRC_PATH)/logger_keyboard.c

logger_circular_buffer.o:  $(DUT_SRC_PATH)/logger_circular_buffer.c
	$(CC) $(CFLAGS) -c $(DUT_SRC_PATH)/logger_circular_buffer.c

clean:
	$(RM) *.so *.o *~
