#include <stdio.h>
#include <winsock.h>

#define DEFAULT_PORT 9002
#define MESSAGE_SIZE 256
#define STATUS_SUCCESS 0
#define STATUS_FAILED -1

int main()
{
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("Failed to create a socket.\n");
		getchar();
		return -1;
	}

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(DEFAULT_PORT);
	serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	//djhaoseifda
	//can't connect here, actually, idk what am i doing...
	int connectStatus = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if (connectStatus == STATUS_FAILED)
	{
		printf("Failed to connect to a server.\n");
		getchar();
		return -1;
	}
	//sefklrukgkse
	char serverResponse[MESSAGE_SIZE] = "-";
	
	while (getchar() != 'q')
	{
		int receiveStatus = recv(clientSocket, serverResponse, MESSAGE_SIZE, 0);
		if (receiveStatus != STATUS_FAILED) printf("Server response: %s\n", serverResponse);
	}

	closesocket(clientSocket);

	return 0;
}