#ifndef Connection_H
#define Connection_H

#include <WinSock2.h>
#include <WS2TCPIP.h>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
using std::string;
using std::to_string;
using std::vector;
struct ClientInfo
{
	SOCKET Sock ;
	string ClientIP;
};
class TCPServer
{
public:
	int PORT;
	string IP;
	TCPServer(int PORT = 6969 , string ipv4 = "127.0.0.1")
	{
		WSADATA Windows_Socket_info;
		WORD VerionOfWindows_Socket = MAKEWORD(2, 2);
		int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
		if (res != 0)
		{
			throw "WSAStartup Error  " + to_string(res);
		}
		this->PORT = PORT;
		this->IP = ipv4;
		CreatSocket();
		std::clog << "[Log]: Server Start On " << ipv4 << " IP Address in " << PORT << " Port \n";
		Listen();
		std::clog << "[Log]: Start Listening \n";
	}
	~TCPServer()
	{
		WSAGetLastError();
		closesocket(Server_sock);
		WSACleanup();
	}
	ClientInfo BeginAccepting()
	{
		SOCKET NewClient_Sock;
		char ClientIP[256];
		sockaddr_in client_address;
		int client_address_size = sizeof(client_address);
		NewClient_Sock = accept(Server_sock, (sockaddr*)&client_address, &client_address_size);
		if (NewClient_Sock == INVALID_SOCKET) {
			closesocket(NewClient_Sock); //clean up
			WSACleanup(); //clean up
		}
		inet_ntop(AF_INET, &client_address.sin_addr, ClientIP, 256);  //NEW
		ClientInfo NewClient{ NewClient_Sock , ClientIP };
		return NewClient;
	}
private:
	SOCKET Server_sock;
	bool CreatSocket()
	{
		sockaddr_in server_address;
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(PORT);
		server_address.sin_addr.S_un.S_addr = inet_addr(IP.c_str());
		Server_sock = socket(AF_INET, SOCK_STREAM, 0);
		int status = ::bind((SOCKET)Server_sock, (sockaddr*)&server_address, sizeof(server_address));
		if (status == SOCKET_ERROR) {
			closesocket(Server_sock); 
			WSACleanup(); 
			return 0;
		}
		return 1;
	}
	bool Listen( int ListenLen = SOMAXCONN)
	{
		int status = listen(Server_sock, ListenLen);

		if (status == SOCKET_ERROR) {
			closesocket(Server_sock); 
			WSACleanup(); 
			return 0;
		}
		return 1;
	}
};





#endif // !Connection_H