#Makefile
common = message.o user.o utils.o
client_objects = chat-client.o ${common}
server_objects = chat-server.o ${common}
standard = c++17

.PHONY: all
all: chat-client chat-server

chat-client: ${client_objects}
	gcc -o chat-client ${client_objects} -lstdc++
chat-server: ${server_objects}
	gcc -o chat-server ${server_objects} -lstdc++

chat-client.o: rtype.h utils.h
chat-server.o:

message.o: message.h user.h
user.o: user.h
utils.o: utils.h message.h rtype.h user.h

.PHONY: clean
clean:
	-rm -f chat-client chat-server *.o *.data 2>/dev/null
