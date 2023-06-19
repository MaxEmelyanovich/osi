# Лабораторная работа №4. (Вариант 7)
## Задача
Написать программы для консольного процесса Boss и консольных процессов Parent, Child. Для моделирования
передачи сообщений ввести специальные события (c автоматическим сбросом). Принимать сообщение можно только от двух АКТИВНЫХ процессов Child (использовать семафор) и одного
АКТИВНОГО процесса Parent (использовать мьютекс), передача остальных сообщений от других процессов
должна временно блокироваться (находиться в режиме ожидания).
## Процесс Boss:
1. Инициализация объектов синхронизации;
2. запрашивает у пользователя количество процессов Parent и количество процессов Child, которые он должен
запустить;
3. запрашивает кол-во сообщений, принятых от Parent или Child
4. запускает заданное количество процессов Parent, Child;
5. принимает от каждого процесса Parent, Child сообщения, выводит и кто его отправил на консоль в одной
строке.
6. завершает свою работу.
## Процесс Parent:
1. синхронизировать работу процессов Parent с помощью мьютекса
2. передачу сообщений реализовать с помощью событий
3. запрашивает с консоли сообщения и передает их (по одному) процессу Boss;
4. завершает свою работу.
## Процесс Child:
1. синхронизировать работу процессов Child с помощью семафора
2. передачу сообщений реализовать с помощью событий
3. запрашивает с консоли сообщения и передает их (по одному) процессу Boss;
4. завершает свою работу.