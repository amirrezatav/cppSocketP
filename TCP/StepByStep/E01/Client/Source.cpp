#include "CleintConnection.h"
#include <thread>
CleintConnection tcpConnection;
void Client(bool flag)
{

}

void Reciev(char* buffer, int size)
{

}

int main()
{
	tcpConnection = CleintConnection("127.0.0.1", 7071, Client, Reciev);
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
