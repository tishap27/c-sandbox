CC = gcc
CFLAGS = -pedantic -ansi -Wall -Wextra
TARGET = bank_system_TishaPatel
OBJS = main.o account.o operations.o display.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c account.h operations.h display.h
	$(CC) $(CFLAGS) main.c -c

account.o: account.c account.h
	$(CC) $(CFLAGS) account.c -c

operations.o: operations.c operations.h account.h
	$(CC) $(CFLAGS) operations.c -c

display.o: display.c display.h account.h
	$(CC) $(CFLAGS) display.c -c

clean:
	rm -f $(OBJS) $(TARGET)
