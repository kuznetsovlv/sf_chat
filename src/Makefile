#Makefile
common = memoryAllocationException.o message.o networkException.o send.o user.o utils.o
client_objects = chat-client.o client.o input.o ${common}
server_objects = chat-server.o cripto.o server.o sql.o ${common}
standard = c++17

.PHONY: all
all: chat-client chat-server

chat-client: ${client_objects}
	gcc -o chat-client ${client_objects} -lstdc++
chat-server: ${server_objects}
	gcc -o chat-server ${server_objects} -lstdc++ -std=${standard} -pthread -lmysqlclient

chat-client.o: client.h utils.h
chat-server.o: chat-server.cpp server.h utils.h
	gcc -o chat-server.o chat-server.cpp -c -std=${standard}

client.o: client.h client.cpp input.h networkException.h message.h rtype.h send.h user.h utils.h
cripto.o: cripto.h
input.o: input.h
networkException.o: networkException.h
memoryAllocationException.o: memoryAllocationException.h
message.o: message.h user.h
send.o: send.h rtype.h
server.o: server.h server.cpp config.h networkException.h message.h rtype.h send.h sql.h user.h utils.h
	gcc -o server.o server.cpp -c -std=${standard}
sql.o: sql.h sql.cpp cripto.h message.h user.h utils.h
	gcc -o sql.o sql.cpp -c -std=${standard}
user.o: user.h
utils.o: utils.h memoryAllocationException.h message.h rtype.h user.h

.PHONY: clean
clean:
	-rm -f chat-client chat-server *.o *.data 2>/dev/null
