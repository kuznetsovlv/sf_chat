#Makefile
common = memory_allocation_exception.o message.o network_exception.o send.o user.o utils.o
client_objects = chat-client.o client.o input.o logger.o message_logger.o ${common}
server_objects = chat-server.o cripto.o server.o sql.o ${common}
standard = c++20

.PHONY: all
all: chat-client chat-server

chat-client: ${client_objects}
	gcc -o chat-client ${client_objects} -lstdc++
chat-server: ${server_objects}
	gcc -o chat-server ${server_objects} -lstdc++ -std=${standard} -pthread -lmysqlclient

chat-client.o: chat-client.cpp client.h utils.h
	gcc -o chat-client.o chat-client.cpp -c -std=${standard}
chat-server.o: chat-server.cpp server.h utils.h
	gcc -o chat-server.o chat-server.cpp -c -std=${standard}

client.o: client.h client.cpp input.h network_exception.h message.h message_logger.h rtype.h send.h user.h utils.h
cripto.o: cripto.h
input.o: input.h
logger.o: logger.h
network_exception.o: network_exception.h
memory_allocation_exception.o: memory_allocation_exception.h
message.o: message.h user.h
message_logger.o: message_logger.h logger.h message.h
send.o: send.h rtype.h
server.o: server.h server.cpp config.h network_exception.h message.h rtype.h send.h sql.h user.h utils.h
	gcc -o server.o server.cpp -c -std=${standard}
sql.o: sql.h sql.cpp cripto.h message.h user.h utils.h
	gcc -o sql.o sql.cpp -c -std=${standard}
user.o: user.h
utils.o: utils.h memory_allocation_exception.h message.h rtype.h user.h

.PHONY: clean
clean:
	-rm -f chat-client chat-server *.o *.data *.log 2>/dev/null
