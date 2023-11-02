#include <stdio.h>
#include <winsock.h>

#define PORT 99991

struct sockaddr_in srv;
struct sockaddr_in cli;

int nSocket;

int main()
{
	WSADATA w;
	int nRet = -1;
	char sBuffer[1024] = { 0, };

	if (WSAStartup(MAKEWORD(2, 2), &w) < 0) 
	{
		printf("\failed WSAStartup");
		exit(EXIT_FAILURE);
	}
	nSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket < 0)
	{
		printf("\socket creation failed");
		exit(EXIT_FAILURE);
		
	}
	memset(&srv, 0, sizeof(srv));
	memset(&cli, 0, sizeof(cli));

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;
	nRet = bind(nSocket, (struct sockaddr*)&srv, sizeof(srv));
	if (nRet < 0)
	{
		printf("bind failed");
		exit(EXIT_FAILURE);
	}

	int nLen = sizeof(struct sockaddr);
	while (1)
	{
		nRet = recvfrom(nSocket, sBuffer, 1024, 0,
			(struct sockaddr*)&cli, &nLen);
		if (nRet < 0)
		{
			printf("\recvfrom failed");
			exit(EXIT_FAILURE);
		}	
		else {
			//Reply to client and print message from client
			printf("\message from client:\n%s",
				sBuffer);
			nRet = sendto(socket, "Reply from server",
				1024, 0, (struct sockaddr*)&cli,
				sizeof(struct sockaddr));
			if (nRet < 0)
			{
				printf("\nResponse not sent");
				exit(EXIT_FAILURE);
			}
			else {
				printf("Responce sent...");
			}
		}
	}
		
}
