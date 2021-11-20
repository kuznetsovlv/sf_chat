#Makefile
objects = main.o user.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: user.h
user.o: user.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
