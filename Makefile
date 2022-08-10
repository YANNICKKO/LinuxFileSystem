CC=gcc
CFLAGS=-Wextra -g
OBJ=tema3.o functii_dir.o functii_fis.o
TARGET=tema3

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *~

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

