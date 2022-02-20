#Makefile
objects = main.o client.o cripto.o file.o input.o message.o messages.o response.o request.o server.o serverRequest.o user.o utils.o
standard = c++17

.PHONY: all
all: chat

chat: ${objects}
	gcc -o chat ${objects} -lstdc++

main.o: main.cpp client.h request.h server.h user.h users.h cripto.h
	gcc -o main.o main.cpp -c -std=${standard}
client.o: client.h dataResponse.h dataResponse.cpp input.h message.h request.h response.h server.h serverRequest.h user.h
cripto.o: cripto.h
file.o: file.cpp file.h
	gcc -o file.o file.cpp -c -std=${standard}
input.o: input.h
message.o: message.h user.h
messages.o: messages.cpp messages.h file.h message.h utils.h
	gcc -o messages.o messages.cpp -c -std=${standard}
response.o: response.h
request.o: request.h client.h message.h
server.o: server.h client.h dataResponse.h dataResponse.cpp message.h messages.h request.h response.h serverRequest.h user.h
serverRequest.o: serverRequest.h
user.o: user.h
users.o: users.cpp users.h user.h
	gcc -o users.o users.cpp -c -std=${standard}
utils.o: utils.h

.PHONY: clean
clean:
	-rm -f chat *.o 2>/dev/null
