#include<iostream>
#include<WS2tcpip.h>
#include<vector>
#pragma comment (lib , "Ws2_32.lib")
using namespace std;
#define PORT  6969
#define BUFLEN 1024
struct Client
{
	sockaddr_in info;
	char* IP;
	bool isConnect;
};
vector<Client> Clients;
int main()
{
	json a;

	WSADATA windsow_socket_info;
	WORD VersionOFWindowsSocket;
	VersionOFWindowsSocket = MAKEWORD(2,2); 
	int res;
	res = WSAStartup(VersionOFWindowsSocket , &windsow_socket_info);
	if (res != 0)
	{
		// cerr = cout 
		cerr << "Initialize winSock Error : " << res; 
		return;
	}
	sockaddr_in server_address;         
	server_address.sin_family = AF_INET ; // Version IP (v4 = AF_INET , v6 = AF_INET6) 
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.S_un.S_addr = INADDR_ANY;
	//                                        TCP    // UDP SOCK_DGRAM
falg:;
	SOCKET server_SOCK = socket(AF_INET , SOCK_STREAM , 0);
	res = bind(server_SOCK, (sockaddr*)&server_address, sizeof(server_address));
	if (res != 0)
	{
		// cerr = cout 
		cerr << "bind Error : " << res;
		return;
	}
	res = listen(server_SOCK , SOMAXCONN);
	if (res != 0)
	{
		// cerr = cout 
		cerr << "listen Error : " << res;
		return;
	}
	cout << "Waiting For Accepting . . . " << endl;
	sockaddr_in Client_adder;
	int Client_len = sizeof(Client_adder);
	res = accept(server_SOCK , (sockaddr*) &Client_adder , &Client_len);
	if (res != 0)
	{
		// cerr = cout 
		cerr << "accept Error : " << res;
		closesocket(server_SOCK);
		goto falg;
	}
	char Clinet_IP[256];
	inet_ntop(AF_INET, &Client_adder.sin_addr, Clinet_IP, 256);
	// Save Info
	Client newclinet;
	newclinet.info = Client_adder;
	newclinet.IP = Clinet_IP;
	Clients.push_back(newclinet);
	cout << "Connect ..." << endl;
	char BUFFER[BUFLEN]{0};
	cout << "Waiting for recv";
	while (true)
	{
		res = recv(server_SOCK, BUFFER, BUFLEN, 0);
		if (res != 0)
		{
			// cerr = cout 
			cerr << "recv Error : " << res;
			closesocket(server_SOCK);
			WSACleanup();
		}
		cout << Clinet_IP << BUFFER << endl;
	}

	return 0;
}
