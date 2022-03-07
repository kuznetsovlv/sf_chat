#Makefile
common = message.o user.o utils.o
client_objects = chat-client.o ${common}
server_objects = chat-server.o cripto.o file.o messages.o users.o server.o ${common}
standard = c++17

.PHONY: all
all: chat-client chat-server

chat-client: ${client_objects}
	gcc -o chat-client ${client_objects} -lstdc++
chat-server: ${server_objects}
	gcc -o chat-server ${server_objects} -lstdc++ -std=${standard} -pthread

chat-client.o: rtype.h utils.h
chat-server.o: server.h server.cpp utils.h
	gcc -o chat-server.o chat-server.cpp -c -std=${standard}

cripto.o: cripto.h
file.o: file.h file.cpp
	gcc -o file.o file.cpp -c -std=${standard}
message.o: message.h user.h
messages.o: messages.h messages.cpp file.h message.h utils.h
	gcc -o messages.o messages.cpp -c -std=${standard}
server.o: server.h server.cpp file.h message.h messages.h rtype.h user.h users.h utils.h
	gcc -o server.o server.cpp -c -std=${standard}
user.o: user.h
users.o: users.h users.cpp cripto.h file.h user.h utils.h
	gcc -o users.o users.cpp -c -std=${standard}
utils.o: utils.h message.h rtype.h user.h

.PHONY: clean
clean:
	-rm -f chat-client chat-server *.o *.data 2>/dev/null
