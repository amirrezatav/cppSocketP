#include "ClientConnection.h"
ClientConnection::ClientConnection()
{

}
ClientConnection::ClientConnection(string ip, int port, MessageRecieverHandler mrh , Accept_Handler ah)
	: Serverip(ip) , Serverport(port) , RecieverHandler (mrh) , AcceptHandler(ah)
{


}
ClientConnection::~ClientConnection()
{
	Cleanup();
}
bool ClientConnection::Init()
{
	WSADATA windows_Socket_info;
	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(version, &windows_Socket_info);
	return res == 0;
}
void ClientConnection::Start()
{
	ClientConnection::MySock = CreatSocket();
	if (MySock != INVALID_SOCKET)
	{
		Run();
	}
}
void ClientConnection::Send(const char* buffer, int Length)
{
	send(MySock, buffer, Length, 0);
}
void ClientConnection::Run()
{
	thread NEWRecievedTH;
	int bytesIN = recv(MySock, BUFFER, BUFFER_SIZE, 0);
	if (bytesIN <= 0)
	{
		closesocket(MySock);
		return;
	}
	else
	{
		if (bytesIN >= 1)
			NEWRecievedTH = thread([&]() {RecieverHandler(MySock, BUFFER, bytesIN); });
	}
	Run();
	NEWRecievedTH.join();
}
void ClientConnection::Cleanup()
{
	ClientConnection::IsRunning = false;
	closesocket(ClientConnection::MySock);
	WSACleanup();
}
SOCKET ClientConnection::CreatSocket()
{
	SOCKET MySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (MySocket != INVALID_SOCKET)
	{
		sockaddr_in Server_Info;
		Server_Info.sin_family = AF_INET;
		Server_Info.sin_port = htons(Serverport);
		if (inet_pton(AF_INET, Serverip.c_str(), &Server_Info.sin_addr) <= 0)
		{
			Cleanup();
			return -1;
		}
		//CONNECT TO SERVER
		int connectionResult = connect(MySocket, ( sockaddr*)&Server_Info, sizeof(Server_Info));

		if (connectionResult == SOCKET_ERROR)
		{
			Cleanup();
			return -1;
		}
		AcceptHandler(MySocket);
		IsRunning = true;
		return MySocket;
	}
	else
	{
		Cleanup();
		return -1;
	}
}