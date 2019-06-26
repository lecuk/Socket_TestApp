#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define DEFAULT_PORT 9002
#define MESSAGE_SIZE 256

int main()
{
	char data[MESSAGE_SIZE] = "Hello world!";

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		printf("Failed to create a socket.\n");
		getchar();
		return -1;
	}

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(DEFAULT_PORT);
	serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	int bindStatus = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if (bindStatus == -1)
	{
		printf("Failed to bind a server.\n");
		getchar();
		return -1;
	}

	while (getchar() != 'q')
	{
		listen(serverSocket, 4);

		int clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket != -1)
		{
			printf("Sent data to client: %i\n", clientSocket);
			send(clientSocket, data, MESSAGE_SIZE, 0);
		}
	}

	closesocket(serverSocket);

	return 0;
}