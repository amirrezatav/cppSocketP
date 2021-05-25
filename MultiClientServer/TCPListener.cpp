#include "TCPListener.h"
TCPListener::TCPListener()
{

}
TCPListener::TCPListener(string ip, int port, MessageRecieverHandler mrh , Accept_Handler ah)
	: ip(ip) , port(port) , RecieverHandler (mrh) , AcceptHandler(ah)
{


}
TCPListener::~TCPListener()
{
	Cleanup();
}
bool TCPListener::Init()
{
	WSADATA windows_Socket_info;
	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(version, &windows_Socket_info);
	return res == 0;
}
void TCPListener::Start()
{
	TCPListener::Server = CreatSocket();
	if (Server != INVALID_SOCKET)
	{
		FD_SET(Server, &master);
		Read = master;
		BeginConnection();
	}
}
void TCPListener::Send(SOCKET client, const char* buffer, int Length)
{
	send(client, buffer, Length, 0);
}
void TCPListener::BeginConnection()
{
	Read = master;
	int SocketCount = select(0, &Read, nullptr, nullptr , nullptr);
	thread NewConnectionTH;
	thread NEWRecievedTH;
	// proccess Socket 
	if(SocketCount != -1 )
	for (int i = 0; i < SocketCount; i++)
	{
		SOCKET sp = Read.fd_array[i];
		if (sp == Server) // Accetp a new connection 
		{
			SOCKET clinet = accept(Server , nullptr , nullptr);
			FD_SET(clinet, &master);
			NEWRecievedTH = thread([&]() {AcceptHandler(clinet); });
		}
		else
		{
			memset (BUFFER , 0 , BUFFER_SIZE); // ZeroMemory(BUFFER, BUFFER_SIZE); 
			int bytesIN = recv(sp , BUFFER , BUFFER_SIZE , 0);
			if (bytesIN <= 0)
			{
				closesocket(sp);
				FD_CLR(sp , &master);
			}
			else
			{
				NEWRecievedTH = thread([&]() {RecieverHandler(sp, BUFFER , bytesIN ); });
			}
		}
	}
	if (IsRunning)
	{
		BeginConnection();
	}
	NewConnectionTH.join();
	NEWRecievedTH.join();
}
void TCPListener::Cleanup()
{
	TCPListener::IsRunning = false;
	closesocket(TCPListener::Server);
	WSACleanup();
}
SOCKET TCPListener::CreatSocket()
{
	SOCKET serversock = socket(AF_INET, SOCK_STREAM, 0);
	if (serversock != INVALID_SOCKET)
	{
		sockaddr_in serveradders;
		serveradders.sin_family = AF_INET;
		serveradders.sin_port = htons(port);
		serveradders.sin_addr.S_un.S_addr = INADDR_ANY; // inet_pton( AF_INET , ip.c_str() , NULL);
		int status = ::bind(serversock , (sockaddr*)&serveradders ,sizeof(serveradders));
		if (status != SOCKET_ERROR)
		{
			status = listen(serversock , SOMAXCONN);
			if (status == SOCKET_ERROR)
			{
				Cleanup();
				return -1;
			}
		}
		else
		{
			
			return -1;
		}
		IsRunning = true;
		return serversock;
	}
	else
	{
		Cleanup();
		return -1;
	}
}