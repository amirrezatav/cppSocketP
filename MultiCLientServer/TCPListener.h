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
typedef void (*MessageRecieverHandler)(int socketid , const char* const buffer , const int& datalength);

class TCPListener
{
public:
	TCPListener();
	TCPListener(string ip, int port, MessageRecieverHandler , Accept_Handler);
	~TCPListener();
	bool Init();
	void Start();
	static void Send(SOCKET client ,const char* buffer , int Length);
	bool IsRunning = false;
private :
	void Run();
	SOCKET CreatSocket();
	fd_set master;
	fd_set Read;
	void Cleanup();
	char BUFFER[SIZE_BUFFER];
	MessageRecieverHandler RecieverHandler;
	Accept_Handler AcceptHandler;
	string ip; 
	int port;
	SOCKET Server;
};

#endif // !TCPLISTENER_H

