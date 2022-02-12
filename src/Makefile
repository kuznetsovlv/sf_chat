#Makefile
objects = main.o client.o input.o message.o response.o request.o server.o serverRequest.o user.o

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: client.h request.h server.h
client.o: client.h dataResponse.h dataResponse.cpp input.h message.h request.h response.h server.h serverRequest.h user.h
input.o: input.h
message.o: message.h user.h
response.o: response.h
request.o: request.h client.h message.h
server.o: server.h client.h dataResponse.h dataResponse.cpp message.h request.h response.h serverRequest.h user.h
serverRequest.o: serverRequest.h
user.o: user.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
