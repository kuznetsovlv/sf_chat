#Makefile
objects = main.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o:

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
