CC = gcc
CFLAGS = -g -Wall
TARGET = main
OBJECTS =main1.c product.o
.SUFFIXS= .c.o
main_debug : $(TARGET)
main_debug : DEBUGOPTION= -DDEBUG
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(DEBUGOPTION) -o $@ $^

.c.o :
	$(CC) $(CFLAGS) $(DEBUGOPTION) -c $<

clean :
	rm *.o $(TARGETS)
