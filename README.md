# IT_School
Задача приложения: реализация простого key-value хранилища, взаимодействие с которым происходит через подключение по tcp.

## Аргументы запуска
    -p - Порт для TCP сервера

    -m - Максимальное количество клиентов

    -f - Файл для инициализации репозитория

Ключи необязательны, в случае отсутствия ключа будет использовано значение из src/Settings.h

## Поддерживаемые команды
    PUT <key> <value>

    GET <key>

    DELETE <key>
    
    DUMP <filename>

    COUNT

P.S. Подключение boost asio через fetch content дело долгое, если библиотека у вас установлена, быстрее будет подключить свою