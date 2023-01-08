# sf_chat
First test project for Skillfactory course of C++

The simple network chat.

## Developers:

- Kuznetsov Leonid.

## Solution:
Now realised network client-server connection. Added connection to MySQL data base. The app consists of two parts: client (chat-client, based on Client class) and server (chat-server, based on Server class). Both parts have been written for Linux OS.

At the last update added Multithreading into client part. Also added classes Logger and MessageLogger to memorise messages at client side.

## Classes:
1. class Client - base of the client part app is used to communication with server.
2. class Server - base of the server part, here is a base functionality: communication with differen service to save user's and message's data and to provide messages to clients.
3. class User - information about user.
4. class Message - information about message.
5. class SQL - provides interaction between the app and MySQL database.
6. class Logger - Saves strings into file and reads it's lines.
7. class MessageLogger - inherits from Logger to log objects of Message

## How to use:
The app was tested with `Linux Mint 20.3` and `21` and `Fedora 36`. To compilate use `gcc 9.3.0` or higher and `make` utility.

App is compiled to 2 binary files: `chat-server` - server and `chat-client`. You should install apropriate msql library before compiling.

Before first start `chat-server` pursue command `mysql < init.sql` to initiate database.

To start `chat-client` use command `/src/chat-client [ip]` where `ip` is server's ip addres by default it is `127.0.0.1`