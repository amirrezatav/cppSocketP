#include "ClientConnection.h"

ClientConnection::ClientConnection()
{

}
ClientConnection::ClientConnection(string ip, int port, Connection_Handler clientHandler, Recive_Handler reciveHandler)
	: Serverip(ip), Serverport(port), connectionHandler(clientHandler), reciveHandler(reciveHandler)
{

}
bool ClientConnection::Init()
{
	WSADATA WindowsSocketInof;
	WORD Version = MAKEWORD(2, 2);
	int res = WSAStartup(Version, &WindowsSocketInof);
	return res == 0;
}
void ClientConnection::Start()
{
	MySocket = CreateSocket();
	if (MySocket != INVALID_SOCKET)
	{
		IsRunning = true;
		connectionHandler(true);
		while (true)
			Run();
	}
	else
	{
		throw exception("Start Function : Server Connection Failed!");
	}
}
void ClientConnection::CleanUp()
{
	IsRunning = false;
	closesocket(MySocket);
	WSACleanup();
}
ClientConnection::~ClientConnection()
{
	CleanUp();
}
void ClientConnection::Run()
{
	char BUFFER[SIZE_Buffer];
	memset(BUFFER, 0, SIZE_Buffer);
	int ByteRecv = recv(MySocket, BUFFER, SIZE_Buffer, 0);
	if (ByteRecv <= 0)
	{
		connectionHandler( false);
	}
	else
	{
		if (ByteRecv >= 1)
			reciveHandler(BUFFER, ByteRecv);
	}
}
SOCKET ClientConnection::CreateSocket()
{
	SOCKET MySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (MySocket != INVALID_SOCKET)
	{
		sockaddr_in ServerAddress;
		ServerAddress.sin_family = AF_INET; // IP v4
		ServerAddress.sin_port = htons(Serverport);
		ServerAddress.sin_addr.S_un.S_addr = INADDR_ANY;
		int res = inet_pton(AF_INET, Serverip.c_str(), &ServerAddress.sin_addr);
		if (res <= 0)
		{
			CleanUp();
		}
		else
		{
			res = connect(MySocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
			if (res != SOCKET_ERROR)
			{
				return MySocket;
			}
			else
			{
				closesocket(MySocket);
				CleanUp();
				return -1;
			}
		}
	}
	else
	{
		closesocket(MySocket);
		CleanUp();
		return -1;
	}
}