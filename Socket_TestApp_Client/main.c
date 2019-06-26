#include <stdio.h>
#include <conio.h>
#include <winsock.h>

#define DEFAULT_PORT 9002
#define MESSAGE_SIZE 256
#define STATUS_SUCCESS 0
#define STATUS_FAILED -1

void printCurrentError()
{
	char buffer[128];
	strerror_s(buffer, 128, errno);
	printf("%s\n", buffer);
}

int main()
{
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("socket: %u\n", clientSocket);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("Failed to create a socket.\n");
		printCurrentError();
		getchar();
		getchar();
		return -1;
	}

	while (1)
	{
		char sAddress[64];
		printf("Enter server IP: ");
		scanf_s("%s", sAddress, 64);

		struct sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(DEFAULT_PORT);
		serverAddress.sin_addr.S_un.S_addr = inet_addr(sAddress);

		printf("Connecting...\n");
		int connectStatus = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
		if (connectStatus == STATUS_FAILED)
		{
			printf("Failed to connect to a server.\n");
			continue;
		}
		break;
	}

	printf("Connected!\n");
	char serverResponse[MESSAGE_SIZE] = "-";
	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 'q') break;
		}

		int receiveStatus = recv(clientSocket, serverResponse, MESSAGE_SIZE, 0);
		if (receiveStatus != STATUS_FAILED)
		{
			printf("Server sent some data: %s\n", serverResponse);
		}
	}

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}