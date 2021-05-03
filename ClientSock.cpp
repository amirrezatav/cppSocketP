#include<WS2tcpip.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;

#define ServerPORT 6969
#define ServerIP "127.0.0.1"
#define BUFFERLEN 1 * 1024

int main(int argc, char* argv[])
{
	WSADATA Win_Socket_Info;
	SOCKET MyConnection;
	struct sockaddr_in Server_Info;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &Win_Socket_Info) != 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}

	cout << "\nInitialised...";

	//Create a socket
	if ((MyConnection = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "\nCould not create socket :" << WSAGetLastError();
	}

	cout << "\nSocket created...";


	Server_Info.sin_family = AF_INET;
	Server_Info.sin_port = htons(ServerPORT);
	if (inet_pton(AF_INET, ServerIP, &Server_Info.sin_addr) <= 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}

	//Connect to remote server
	while (true)
	{
		if (connect(MyConnection, (struct sockaddr*)&Server_Info, sizeof(Server_Info)) < 0)
			cerr << "\nconnection error ... !";
		else
			break;
		Sleep(2 * 1000);
	}
	

	cout << "\nConnected\n";

	//Send some data
	
	while (true)
	{
		char Buffer[BUFFERLEN];
		cout << "\n-> Write your Message : ";
		std::cin >> Buffer;
		if (send(MyConnection, Buffer, strlen(Buffer) , 0) < 0)
		{
			puts("\nSend failed");
			return 1;
		}
		puts(">>>>> Data Send\n");
	}

	return 0;
}
