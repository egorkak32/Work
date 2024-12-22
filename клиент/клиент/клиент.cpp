#include <windows.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void SendActiveWindowInfo(SOCKET sock) {
    char windowTitle[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
    send(sock, windowTitle, strlen(windowTitle), 0);
}

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in server;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080); // Порт сервера
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес сервера
    connect(sock, (struct sockaddr*)&server, sizeof(server));
    while (true) {
        SendActiveWindowInfo(sock);
        Sleep(5000);
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}