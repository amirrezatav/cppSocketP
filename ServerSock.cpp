// Server Side  
#include <iostream>
#include <WS2tcpip.h>
#pragma  comment (lib,"Ws2_32.lib") // For Linker
using namespace std;

int main()
{
	// Initialize windows socket 
	WSADATA windows_socket_info;

	// WORD _> unsignd Short 
	WORD Socket_version = MAKEWORD(2, 2);

	int res = WSAStartup(Socket_version, &windows_socket_info);

	if (res != 0)
	{
		// cout = cerr
		cerr << "ERROR";
		return 0;
	}

	// Create Server Socket 

	sockaddr_in ServerInfo;
	ServerInfo.sin_family = AF_INET; // IPv4
	/// ServerInfo.sin_family = AF_INET6; // IPv6
	ServerInfo.sin_port = htons(666);
	ServerInfo.sin_addr.S_un.S_addr = INADDR_ANY;
	//ServerInfo.sin_addr.S_un.S_addr = inet_addr("192.168.1.50");
	
						   // IPv4		 TCP
	SOCKET SERVER = socket( AF_INET , SOCK_STREAM , 0);

	res = bind(SERVER, (sockaddr*)& ServerInfo, sizeof(ServerInfo));

	if (res == SOCKET_ERROR)
	{
		cerr << "ERROR";
		closesocket(SERVER);
		WSACleanup();
		return 0;
	}

	res = listen(SERVER , SOMAXCONN);

	if (res == SOCKET_ERROR)
	{
		cerr << "ERROR";
		closesocket(SERVER);
		WSACleanup();
		return 0;
	}

	//WAIT FOR CONNECTION
	// ...
}
