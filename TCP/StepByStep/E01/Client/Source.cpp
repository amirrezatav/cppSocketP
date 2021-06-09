#include "ClientConnection.h"
#include <thread>
ClientConnection tcpConnection;
void Client(bool flag)
{

}

void Reciev(char* buffer, int size)
{

}

int main()
{
	tcpConnection = ClientConnection("127.0.0.1", 7071, Client, Reciev);
	if (tcpConnection.Init())
	{
		thread ConnectionThread = thread([&]() {tcpConnection.Start(); });
		ConnectionThread.join();
	}
	else
	{
		return 0;
	}
}