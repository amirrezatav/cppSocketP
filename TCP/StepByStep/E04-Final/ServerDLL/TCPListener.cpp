#include "pch.h"
#include "TCPListener.h"

TCPListener::TCPListener()
{

}
__stdcall TCPListener::TCPListener(string ip, int port, Client_Handler  clientHandler, Recive_Handler  reciveHandler)
	: ip(ip) , port(port) , clientHandler(clientHandler) , reciveHandler(reciveHandler)
{

}
bool TCPListener::Init()
{
	WSADATA WindowsSocketInof;
	WORD Version = MAKEWORD(2, 2);
	int res = WSAStartup(Version , &WindowsSocketInof);
	return res == 0;
}
void TCPListener::Start()
{
	Server = CreateSocket();
	if (Server != INVALID_SOCKET)
	{
		IsRunning = true;
		FD_ZERO(&master);
		FD_ZERO(&Read);
		FD_SET(Server, &master);
		Read = master;
		while (true)
			Run();
	}
	else
	{
		throw exception("Start Function : Server Connection Failed!");
	}
}
void TCPListener::CleanUp()
{
	IsRunning = false;
	closesocket(Server);
	WSACleanup();
}
TCPListener::~TCPListener()
{
	CleanUp();
}
void  TCPListener::Run()
{
	Read = master;
	int SocketCount = select(0, &Read, nullptr, nullptr, nullptr);
	if (SocketCount <= 0)
	{
		CleanUp();
		throw exception("Run Function : Server Connection Failed!");
	}
	else
	{
		for (int i = 0; i < SocketCount; i++)
		{
			SOCKET SelectedSocket = Read.fd_array[i];
			if (SelectedSocket == Server)
			{
				SOCKET NewClient = accept(Server, nullptr, nullptr);
				FD_SET(NewClient, &master);
				clientHandler(NewClient, true);
			}
			else
			{
				char BUFFER[SIZE_Buffer];
				memset(BUFFER, 0, SIZE_Buffer);
				int ByteRecv = recv(SelectedSocket, BUFFER, SIZE_Buffer, 0);
				if (ByteRecv <= 0)
				{
					FD_CLR(SelectedSocket , &master);
					clientHandler(SelectedSocket, false);
				}
				else
				{
					if (ByteRecv >= 1)
						reciveHandler(SelectedSocket, BUFFER, ByteRecv);
				}
			}
		}
	}
}
SOCKET TCPListener::CreateSocket()
{
	SOCKET Server = socket(AF_INET, SOCK_STREAM, 0);
	if (Server != INVALID_SOCKET)
	{
		sockaddr_in ServerAddress;
		ServerAddress.sin_family = AF_INET; // IP v4
		ServerAddress.sin_port = htons(port);
		ServerAddress.sin_addr.S_un.S_addr = INADDR_ANY;
		int res = ::bind(Server , (sockaddr*)&ServerAddress , sizeof(ServerAddress));
		if (res != SOCKET_ERROR)
		{
			res = listen(Server, SOMAXCONN);
			if (res != SOCKET_ERROR)
			{
				return Server;
			}
			else
			{
				closesocket(Server);
				CleanUp();
				return -1;
			}
		}
		else
		{
			closesocket(Server);
			CleanUp();
			return -1;
		}
	}
	else
	{
		closesocket(Server);
		CleanUp();
		return -1;
	}
}