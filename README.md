# sf_chat
First test project for Skillfactory course of C++

## Разработчики:

- Кузнецов Леонид.

## Решения:
В данной версии в приложении реализовано сетевое взаимодействие. Приложение разбито на две части: клиент (основу сотавляет класс Client) и сервер (основа - класс Server). Клиентская и серверная части написаны написаны под Linux, последние события (сейчас 13 марта 2022) меня сильно выбили из колеи, и самостоятельно разбираться с кросплатформенностью у меня попросту нет сил, поэтому все писалось под Linux, поэтой же причине не были реализованы изначально задумывавшийся (но необязательный по заданию функционал), как то:

1. Многопоточность в клиенте с целью возможности независимо отправлять сообщения и получать новые с сервера.
2. Ограничение ввода или возможность передачи и получения сообщений неограниченного размера.

В тоже время, для серверной части мне пришлось реализовать многопоточность, чтобы сервер мог одновременно взаимодействовать с несколькими клиентами, однако, поскольку многопоточность мы не проходили, мне пришлось самостоятельно с ней разбираться, и реализована она, надо полагать, весьма криво и неэффективно.... Надеюсь, в будущем я смогу исправить эти недоработки.

## Используемые типы:
1. class Client - предоставляет пользовательский интерфейс и обеспечивает взаимодействие пользователя с сервером.
2. class Server - основной функционал (создание пользователей, хранение пользователей и сообщений, отправка сообщений пользователям).
3. class User - информация о пользователе (логин, пароль, имя).
4. class Message - информация о сообщении (отправитель, получатель, сам текст сообщения)
5. class Files - работа с файлами: чтение произвольной строки и добавление строк в конец файла.
6. class Messages - расширяет Files для хранения сообщений.
7. class Users - расширяет Files для хранения пользователей.

## Запуск:
Приложение тестировалось под `Linux Mint 20.3`, `gcc 9.3.0`, используется утилита `make`. Исходники собираются в два исполняемых файла: `chat-server` - сервер и `chat-client` - клиент. При запуске `chat-client` из командной строки в аргументах можно указать ip сервера, поумолчанию `127.0.0.1`