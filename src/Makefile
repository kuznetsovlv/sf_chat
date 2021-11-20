#Makefile
objects = main.o message.o server.o user.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: message.h server.h user.h
message.o: message.h user.h
server.o: server.h
user.o: user.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
