#include "TCPListener.h"
#include "Serialize.h"
#include <thread>
#include <iostream>
#include <mutex>
map<string, int> ClientList;
static int ClientNum = 0;
TCPListener tcpServer;
std::mutex ClientLiatDoor;
void Client(int Socketid , bool flag)
{
	std::lock_guard<mutex>Door(ClientLiatDoor);
	std::clog << "\nNew Connect\n";
	if (flag)
	{
		ClientList.insert(pair<string, int>("Amirreza" + to_string(ClientNum++), Socketid));
	}
	else
	{
		string username;
		for (auto target : ClientList)
		{
			if (target.second == Socketid)
			{
				username = target.first;
				break;
			}
		}
		ClientList.erase(username);
	}
}

void Reciev(int socketid , char* buffer , int size)
{
	Packet pk;
	Serialize<Packet>::deserialize(buffer, pk);
	switch (pk.header)
	{
	case Header::message:
	{
		MessagePacket msp;
		Serialize<MessagePacket>::deserialize(buffer, msp);
		string username;
		for (auto target : ClientList)
		{
			if (target.second == socketid)
			{
				username = target.first;
				break;
			}
		}
		cout << username << string(msp.Buffer, msp.size) << endl;
	}
	default:
		break;
	}
}
void sendmessage()
{
	while (!tcpServer.IsRunning);
	
	cout << "\nEnter your Message : ";
	string message;
	getline(cin, message);

	// Packting
	MessagePacket msp;
	msp.header = Header::message;
	msp.size = message.length();
	memcpy(msp.Buffer, message.c_str(), msp.size);

	string username;
	ClientLiatDoor.lock();
	do
	{
		cout << "Enter UserName : ";
		getline(cin, username);
	} while (ClientList.find(username) == ClientList.end());
	int ClinetID = ClientList.find(username)->second;
	ClientLiatDoor.unlock();

	char BUFFER[SIZE_Message];
	memset(BUFFER, 0, SIZE_Message);
	Serialize<MessagePacket>::serialize(BUFFER, msp);

	send(ClinetID, BUFFER, SIZE_Message, 0);
}
int main()
{
	tcpServer = TCPListener("127.0.0.1", 7071, Client, Reciev);
	if (tcpServer.Init())
	{
		thread ConnectionThread = thread([&]() {tcpServer.Start();});
		thread SendThread = thread([&]() {
			while(true)
				sendmessage();
			});
		ConnectionThread.join();
		SendThread.join();
	}
	else
	{
		return 0;
	}
}
