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


	fd_set master;
	FD_ZERO(&master);
	FD_SET(Server_sock, &master);


	//WAIT FOR CONNECTION
	while (true)
	{
		fd_set Read = master;

		int socketcount = select(0, &Read, nullptr, nullptr, nullptr);

		for (int i = 0; i < Read.fd_count; i++)
		{
			SOCKET sock = Read.fd_array[i];
			if (sock == Server_sock) // Accetp a new connection
			{

				sockaddr_in client_address;
				int client_address_size = sizeof(client_address);

				SOCKET NewClient = accept(Server_sock, (sockaddr*)&client_address, &client_address_size);
				if (NewClient == INVALID_SOCKET)
				{
					std::cerr << "ABORT\n";
					closesocket(NewClient); //clean up
					WSACleanup(); //clean up
				}

				char Host[NI_MAXHOST];
				char Service[NI_MAXSERV];

				ZeroMemory(Host, NI_MAXHOST); // memset(clientip , 0 , NI_MAXHOST);
				ZeroMemory(Service, NI_MAXSERV);

				if (getnameinfo((sockaddr*)&client_address, sizeof(client_address), Host, NI_MAXHOST, Service, NI_MAXSERV, 0) == 0)
				{
					cout << Host << "Connected on port " << Service << endl;
				}
				else
				{
					inet_ntop(AF_INET, &client_address.sin_addr, Host, NI_MAXHOST);
					cout << Host << "Connected on port " << ntohs(client_address.sin_port) << endl;
				}
				char buffer[BUFFERLEN];


				// Add the new connection to list of connected client 
				FD_SET(NewClient, &master);
			}
			else// Accept a new massage
			{
				char buf[4096];
				ZeroMemory(buf, 4096);
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					string str(buf, bytesIn);
					cout << str;
					send(sock, str.c_str(), str.size()+1,0); // Echo Message To Client 
				}
			}
		}

	}

	WSAGetLastError();

	system("pause");
	closesocket(Server_sock);
	WSACleanup();

}
