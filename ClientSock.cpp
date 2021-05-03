/*
	Create a TCP Client with socket 
*/

#include<stdio.h>
#include<WS2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;
int main(int argc, char* argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char* message;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}

	cout << "Initialised.\n";

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Could not create socket :" << WSAGetLastError();
	}

	cout << "Socket created.\n";


	server.sin_family = AF_INET;
	server.sin_port = htons(6969);
	if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}

	//Connect to remote server
	if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		cerr << "connect error";
		return 1;
	}

	cout << "Connected";

	//Send some data
	
	while (true)
	{
		char a[512];
		std::cin >> a;
		if (send(s, a, strlen(a) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		puts("Data Send\n");
	}

	return 0;
}
