#Makefile
objects = main.o message.o user.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: user.h message.h
message.o: message.h user.h
user.o: user.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
