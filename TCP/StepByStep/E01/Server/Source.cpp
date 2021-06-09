#include "TCPListener.h"
#include <thread>
#include <iostream>
TCPListener tcpServer;
void Client(int Socketid , bool flag)
{
	std::clog << "Connect";
}

void Reciev(int socketid , char* buffer , int size)
{

}

int main()
{
	tcpServer = TCPListener("127.0.0.1", 7071, Client, Reciev);
	if (tcpServer.Init())
	{
		thread ConnectionThread = thread([&]() {tcpServer.Start();});
		ConnectionThread.join();
	}
	else
	{
		return 0;
	}
}