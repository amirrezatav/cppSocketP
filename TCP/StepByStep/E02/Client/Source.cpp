#include "CleintConnection.h"
#include <thread>
#include <iostream>
#include "Serialize.h"
CleintConnection tcpConnection;
void Client(bool flag)
{

}
void Reciev(char* buffer, int size)
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
		
		cout << "Server : " << string(msp.Buffer, msp.size) << endl;
	}
	default:
		break;
	}
}
void sendmessage()
{
	while (!tcpConnection.IsRunning);
	cout << "Enter your Message : ";
	string message;
	getline(cin, message);

	// Packting
	MessagePacket msp;
	msp.header = Header::message;
	msp.size = message.length();
	memcpy(msp.Buffer, message.c_str(), msp.size);

	string username;

	char BUFFER[SIZE_Message];
	memset(BUFFER, 0, SIZE_Message);
	Serialize<MessagePacket>::serialize(BUFFER, msp);

	send(tcpConnection.MySocket, BUFFER, SIZE_Message, 0);
}
int main()
{
	tcpConnection = CleintConnection("127.0.0.1", 7071, Client, Reciev);
	if (tcpConnection.Init())
	{
		thread ConnectionThread = thread([&]() {tcpConnection.Start(); });
		thread SendThread = thread([&]() {
			while (true)
				sendmessage();
			});
		ConnectionThread.join();
		ConnectionThread.join();
	}
	else
	{
		return 0;
	}
}
