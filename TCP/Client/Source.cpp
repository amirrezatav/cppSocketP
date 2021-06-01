#include <iostream>
#include "ClientConnection.h"
#include "Queue.h"
#include "PACKET.h"
void Accept(int socketid)
{
	char Host[NI_MAXHOST];
	char Service[NI_MAXSERV];
	//std::cout << "Accept" << std::endl;
}
void Recieve(int socketid, const char* const buffer, const int& datalength)
{

	string Message = string(buffer, datalength);
	//std::cout << "Recieve : " << Message << std::endl;
	TCPListener::Send(socketid,Message.c_str(),Message.size()+1);
}
int main()
{
	ClientConnection myConnection = ClientConnection("127.0.0.1",7071,Recieve,Accept) ;
	 Queue::myConnection = &myConnection;
	if (myConnection.Init())
	{
		
		thread th([&](){myConnection.Start();});
		
		th.join();

	}
}
