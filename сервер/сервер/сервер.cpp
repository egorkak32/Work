#include <iostream>
#include <string>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


void start_server() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    std::cout << "Сервер запущен и ожидает подключений..." << std::endl;

    while (true) {
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        std::cout << "Подключен клиент: " << inet_ntoa(client_addr.sin_addr) << std::endl;

        while (true) {
            char buffer[1024] = { 0 };
            size_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                break;
            }
            std::cout << "Активное окно: " << std::string(buffer, bytes_received) << std::endl;
        }

        close(client_socket);
    }
}

int main() {
    start_server();
    return 0;
}