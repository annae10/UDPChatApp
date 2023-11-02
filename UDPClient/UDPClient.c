#include <stdio.h>
#include <Windows.h>

#define PORT 99991

struct sockaddr_in srvto;
struct sockaddr_in srv;

int nSocket;

int main() {
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

	memset(&srvto, 0, sizeof(srvto));
	srvto.sin_family = AF_INET;
	srvto.sin_port = htons(PORT);
	srvto.sin_addr.s_addr = inet_addr("192.168.1.8");

	sprintf(sBuffer, "%s", "Client msg:");
	nRet = sendto(socket, sBuffer, 1024, 0,
		(struct sockaddr*)&srvto, sizeof(struct sockaddr));
	if (nRet < 0)
	{
		printf("\failed to get the message delivered");
		exit(EXIT_FAILURE);
	}
	else
	{
		memset(&srv, 0, sizeof(srv));
		int nLen = sizeof(struct sockaddr);
		nRet = recvfrom(socket, sBuffer, 1024, 0,
			(struct sockaddr*)&srv, &nLen);
		if (nRet < 0)
		{
			printf("\not able to receive the response…";
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("\got reply from server:8s",
				sBuffer);
		}
	}
	printf("\nPress any key to close the client");
	getchar();
}
