#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include<WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#define BUFFERLEN 1 * 1024
#define PORT 6969
using namespace std;

int main()
{

	//INITIALIZE Win Socket
	WSADATA Windows_Socket_info;
	WORD VerionOfWindows_Socket = MAKEWORD(2, 2);
	int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
	if (res != 0)
	{
		std::cerr << "INITIALIZE WinSock Error : " << res;
		return 0;
	}

	//CREATE LISTENING SOCKET
	SOCKET Server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Server_sock == SOCKET_ERROR) {
		std::cerr << "ABORT\n";
		closesocket(Server_sock); //clean up
		WSACleanup(); //clean up
		return 0;
	}
	//BIND THE IP ADDRESS AND PORT TO A SOCKET 
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.S_un.S_addr = INADDR_ANY; // or inet_addr("127.0.0.1");

	int status = ::bind(Server_sock, (sockaddr*)&server_address, sizeof(server_address));

	if (status == SOCKET_ERROR) {
		std::cerr << "ABORT\n";
		closesocket(Server_sock); //clean up
		WSACleanup(); //clean up
		return 0;
	}

	// TELL WINDSOCK THE SOCKET IS FOE LISTENNING 
	status = listen(Server_sock, SOMAXCONN);
	if (status < 0) {
		std::cerr << "ABORT\n";
		closesocket(Server_sock); //clean up
		WSACleanup(); //clean up
		return 0;
	}

	//WAIT FOR CONNECTION
	sockaddr_in client_address; 
	int client_address_size = sizeof(client_address);  

	SOCKET NewClient = accept(Server_sock, (sockaddr*)&client_address, &client_address_size);
	if (NewClient == INVALID_SOCKET) 
	{
		std::cerr << "ABORT\n";
		closesocket(NewClient); //clean up
		WSACleanup(); //clean up
	}

	char clientip[NI_MAXHOST];
	char cliantport[NI_MAXSERV];

	ZeroMemory(clientip , NI_MAXHOST); // memset(clientip , 0 , NI_MAXHOST);
	ZeroMemory(cliantport, NI_MAXSERV);
	
	if (getnameinfo((sockaddr*)&client_address, sizeof(client_address), clientip, NI_MAXHOST, cliantport, NI_MAXSERV , 0) == 0 )
	{
		cout << clientip << "Connected on port " << cliantport;
	}
	else
	{
		inet_ntop(AF_INET, &client_address.sin_addr, clientip, NI_MAXHOST);
		cout << clientip << "Connected on port " << ntohs(client_address.sin_port);
	}
	char buffer[BUFFERLEN];
	//RECEIVE MESSAGE
	while (true)
	{
		ZeroMemory(buffer, BUFFERLEN);
		int ByteRecieved = recv(NewClient, buffer, sizeof(buffer), 0);
		if (ByteRecieved == SOCKET_ERROR) {
			std::cout << "Error in Recv()\n";
			closesocket(NewClient); //clean up
			WSACleanup(); //clean up
			return 0;
		}
		if (ByteRecieved == 0)
		{
			std::cout << "Client Disconnected\n";
			closesocket(NewClient); //clean up
			WSACleanup(); //clean up
			return 0;
		}
		std::cerr << clientip << ": " << buffer << std::endl;
		string message;
		cin >> message;
		send(NewClient, message.c_str(), message.length() + 1, 0);
	}

	WSAGetLastError();
	
	system("pause");
	closesocket(Server_sock);
	WSACleanup();

}
