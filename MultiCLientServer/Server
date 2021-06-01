#include <iostream>
#include "TCPListener.h"
#include "Serialize.h"
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
	TCPListener listner = TCPListener("127.0.0.1",7071,Recieve,Accept) ;
	if (listner.Init())
	{
		int a;
		thread th([&](){listner.Start();});
		th.join();
	}
}
