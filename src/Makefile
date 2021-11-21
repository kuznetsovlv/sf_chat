#Makefile
objects = main.o client.o message.o server.o user.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: client.h message.h request.h server.h user.h
client.o: client.h message.h request.h server.h user.h
message.o: message.h user.h
server.o: server.h client.h message.h request.h user.h
user.o: user.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
