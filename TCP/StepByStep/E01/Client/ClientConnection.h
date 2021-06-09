#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <WS2tcpip.h>
#include <string>
#include "Packets.h"
#pragma comment (lib , "Ws2_32.lib")
using namespace std;
typedef void (*Connection_Handler)(bool flag);
typedef void (*Recive_Handler)(char* Buffer, int DataLegth);

class ClientConnection
{
public:
	bool IsRunning;
	ClientConnection();
	ClientConnection(string ip, int port, Connection_Handler, Recive_Handler);
	bool Init();
	void Start();
	void CleanUp();
	~ClientConnection();
private:
	
	Connection_Handler connectionHandler;
	Recive_Handler reciveHandler;
	string Serverip;
	SOCKET MySocket;
	int Serverport;
	void Run();
	SOCKET CreateSocket();

};


#endif // !CLINETCONNECTION_H


