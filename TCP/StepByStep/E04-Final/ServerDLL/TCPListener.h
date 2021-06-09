#ifndef TCPListener_H
#define TCPListener_H
#include <WS2tcpip.h>
#include <string>
#include "Packets.h"
#include <map>


#pragma comment (lib , "Ws2_32.lib")
using namespace std;
typedef void (* Client_Handler)(int SocketID, bool flag);
typedef void (*Recive_Handler)(int SockerID, char* Buffer, int DataLegth);

class TCPListener
{
public:
	bool IsRunning;
	TCPListener();
	TCPListener(string ip, int port, Client_Handler , Recive_Handler );
	bool Init();
	void Start();
	void CleanUp();
	~TCPListener();
private:
	fd_set master;
	fd_set Read;
	Client_Handler clientHandler;
	Recive_Handler reciveHandler;
	string ip;
	SOCKET Server;
	int port;
	void  Run();
	SOCKET CreateSocket();
};
#endif // !TCPListener_H
