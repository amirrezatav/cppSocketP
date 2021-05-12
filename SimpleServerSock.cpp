#include<iostream>
#include<WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#define BUFFERLEN 1 * 1024
#define PORT 6969

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
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.S_un.S_addr = INADDR_ANY;

	SOCKET Server_sock = socket(AF_INET, SOCK_STREAM, 0);

	int status = bind(Server_sock, (sockaddr*)&server_address, sizeof(server_address));

	if (status == SOCKET_ERROR) {
		std::cout << "ABORT\n";
		closesocket(Server_sock); //clean up
		WSACleanup(); //clean up
		return 0;
	}
flag:;

	status = listen(Server_sock, SOMAXCONN);

	if (status == SOCKET_ERROR) {
		std::cout << "ABORT\n";
		closesocket(Server_sock); //clean up
		WSACleanup(); //clean up
		return 0;
	}
	std::cout << "Waiting for listening . . ." << std::endl;

	//WAIT FOR CONNECTION
	sockaddr_in client_address; //NEW
	int client_address_size = sizeof(client_address);  //NEW

	SOCKET neclinet;
	neclinet = accept(Server_sock, (sockaddr*)&client_address, &client_address_size);

	if (neclinet == INVALID_SOCKET) {
		std::cout << "ABORT\n";
		closesocket(neclinet); //clean up
		WSACleanup(); //clean up
		goto flag;
	}

	std::cout << "Connected . . ." << std::endl;

	//RECEIVE MESSAGE
	std::cout << "Waiting for recv . . ." << std::endl;
	char client_ip[256];  //NEW

	inet_ntop(AF_INET, &client_address.sin_addr, client_ip, 256);  //NEW

	while (true)
	{
		char buffer[BUFFERLEN]{ 0 };
		status = recv(neclinet, buffer, sizeof(buffer), 0);
		if (status < 0) {
			std::cout << "abort\n";
			closesocket(neclinet); //clean up
			WSACleanup(); //clean up
			return 0;
		}
		std::cerr << client_ip << ": " << buffer << std::endl;
	}

	WSAGetLastError();

	system("pause");
	closesocket(Server_sock);
	WSACleanup();

}
