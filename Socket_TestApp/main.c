#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define DEFAULT_PORT 9002
#define MESSAGE_SIZE 256
#define STATUS_SUCCESS 0
#define STATUS_FAILED -1

int main()
{
	WSADATA wsaData;

	int wsaStartupStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaStartupStatus == STATUS_FAILED)
	{
		printf("Failed to initialize WSA.\n");
		getchar();
		return -1;
	}

	char data[MESSAGE_SIZE] = "Hello world!";

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		printf("Failed to create a socket.\n");
		getchar();
		return -1;
	}

	char sAddress[64];
	printf("Enter server IP: ");
	scanf_s("%s", sAddress, 64);

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(DEFAULT_PORT);
	serverAddress.sin_addr.S_un.S_addr = inet_addr(sAddress);

	printf("Binding...\n");
	int bindStatus = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if (bindStatus == STATUS_FAILED)
	{
		printf("Failed to bind a server: %d\n", WSAGetLastError());
		getchar();
		getchar();
		return -1;
	}
	printf("Successfully started a server.\n");

	listen(serverSocket, 4);

	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	if (clientSocket != INVALID_SOCKET)
	{
		char message[MESSAGE_SIZE];
		while (1)
		{
			scanf_s("%s", message, MESSAGE_SIZE);
			if (!strcmp(message, "quit")) break;
			send(clientSocket, message, MESSAGE_SIZE, 0);
			printf("Sent data to client: \"%s\"\n", message);
		}
	}

	closesocket(serverSocket);

	WSACleanup();

	return 0;
}