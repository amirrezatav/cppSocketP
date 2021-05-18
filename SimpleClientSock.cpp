#include<WS2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;

#define ServerPORT 6969
#define ServerIP "127.0.0.1"
#define BUFFERLEN 1 * 1024

int main(int argc, char* argv[])
{
	// INITIALIZE Win Socket
	WSADATA Win_Socket_Info;
	SOCKET MyConnection;

	if (WSAStartup(MAKEWORD(2, 2), &Win_Socket_Info) != 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}
	cout << "\nInitialised...";

	// CREATE SOCKET
	if ((MyConnection = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "\nCould not create socket :" << WSAGetLastError();
		WSACleanup();
	}
	cout << "\nSocket created...";

	// FILL IN HINT STRUCTURE 
	sockaddr_in Server_Info;
	Server_Info.sin_family = AF_INET;
	Server_Info.sin_port = htons(ServerPORT);
	if (inet_pton(AF_INET, ServerIP, &Server_Info.sin_addr) <= 0)
	{
		cerr << "Failed. Error Code : " << WSAGetLastError();
		WSACleanup();
		return 1;
	}

	//CONNECT TO SERVER
	while (true)
	{
		int connectionResult = connect(MyConnection, (struct sockaddr*)&Server_Info, sizeof(Server_Info));
		if (connectionResult == SOCKET_ERROR)
		{
			cerr << "\nCan not Connect to server ... !";
		}
		else
			break;
		Sleep(2 * 1000);
	}


	cout << "\nConnected\n";

	//Send some data
	char Buffer[BUFFERLEN];
	string MESSAGE;
	while (true)
	{
		cout << "\n-> Write your Message : ";
		std::getline(std::cin, MESSAGE);
		if (!MESSAGE.empty())
		{
			if (send(MyConnection, MESSAGE.c_str() , MESSAGE.length() + 1 , 0) < 0)
			{
				cerr << ("\nSend failed");
				return 1;
			}
			ZeroMemory(Buffer, BUFFERLEN);
			int byteRecieved = recv(MyConnection, Buffer, BUFFERLEN, 0);
			if (byteRecieved > 0)
			{
				cout << "Server > " << string(Buffer , byteRecieved);
			}
			
		}
	}

	return 0;
}
