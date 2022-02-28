#Makefile
client_objects = chat-client.o
server_objects = chat-server.o
standard = c++17

.PHONY: all
all: chat-client chat-server

chat-client: ${client_objects}
	gcc -o chat-client ${client_objects} -lstdc++
chat-server: ${server_objects}
	gcc -o chat-server ${server_objects} -lstdc++

chat-client.o:
chat-server.o:

.PHONY: clean
clean:
	-rm -f chat-client chat-server *.o *.data 2>/dev/null
