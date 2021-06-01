#pragma once
#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include<WS2tcpip.h>
#pragma comment (lib , "Ws2_32.lib")
#include <string>
#include "PACKET.h"
#include <thread>
using std::string;
using std::thread;

typedef void (*Accept_Handler)(int socketid);
typedef void (*MessageRecieverHandler)(int socketid ,  char*  buffer , const int& datalength);

class ClientConnection
{
public:
	ClientConnection();
	ClientConnection(string ip, int port, MessageRecieverHandler , Accept_Handler);
	~ClientConnection();
	bool Init();
	void Start();
	void Send(const char* buffer , int Length);
	bool IsRunning = false;
private :
	void Run();
	SOCKET CreatSocket();
	void Cleanup();
	char BUFFER[BUFFER_SIZE];
	MessageRecieverHandler RecieverHandler;
	Accept_Handler AcceptHandler;
	string Serverip; 
	int Serverport;
	SOCKET MySock;
};

#endif // !TCPLISTENER_H

