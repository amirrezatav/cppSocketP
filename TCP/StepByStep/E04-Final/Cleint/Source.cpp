#include "CleintConnection.h"
#include <thread>
#include <iostream>
#include "Serialize.h"
#include <mutex>
#include "Queue.h"
CleintConnection tcpConnection;
std::mutex ClientLiatDoor;
std::mutex QueueListDoor;
std::map<int, Queue*> QueueList;

void Client(bool flag)
{

}
void __stdcall changeprogress(int queueid, int i)
{
	QueueListDoor.lock();
	if (i == 100)
	{
		QueueList.erase(queueid);
	}
	QueueListDoor.unlock();
	clog << i << " % " << endl;
}
void StartDownload(int socketid, int queueid)
{
	StartPacket sp;
	sp.header = Header::start;
	sp.QueueID = queueid;
	char Buffer[sizeof(StartPacket)];
	memset(Buffer, 0, sizeof(StartPacket));
	Serialize<StartPacket>::serialize(Buffer, sp);
	send(socketid, Buffer, sizeof(StartPacket), 0);
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
		
		cout << "\nServer : " << string(msp.Buffer, msp.size) << endl;
	}
	break;
	case Header::queue:
	{
		QueuePacket qp;
		Serialize<QueuePacket>::deserialize(buffer, qp);
		Queue* item = Queue::Download(tcpConnection.MySocket, qp.QueueID, qp.FileName, qp.FileExtention, qp.Size, changeprogress);
		QueueListDoor.lock();
		QueueList.insert(std::pair<int, Queue*>(qp.QueueID, item));
		QueueListDoor.unlock();
		StartDownload(tcpConnection.MySocket, qp.QueueID);
	}
	break;
	case Header::start:
	{
		StartPacket sp;
		Serialize<StartPacket>::deserialize(buffer, sp);
		QueueListDoor.lock();
		auto item = QueueList.find(sp.QueueID);
		if (item != QueueList.end())
		{
			item->second->Start();
		}
		QueueListDoor.unlock();
	}
	break;
	case Header::chunck:
	{
		FilePacket fp;
		Serialize<FilePacket>::deserialize(buffer, fp);
		QueueListDoor.lock();
		auto item = QueueList.find(fp.QueueId);
		Queue* queue = nullptr;
		if (item != QueueList.end())
			queue = item->second;
		QueueListDoor.unlock();
		queue->Write(fp.Buffer, fp.Read);
	}
	break;
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
void SendFile(string path)
{
	
	QueueListDoor.lock();
	int id;
	do
	{
		id = rand() % 9000 + 1000;
	} 
	while (QueueList.find(id) != QueueList.end());
	Queue* item = Queue::Upload(tcpConnection.MySocket, path, id, changeprogress);
	QueueList.insert(std::pair<int, Queue*>(id, item));
	QueueListDoor.unlock();

	QueuePacket qp;
	qp.header = Header::queue;
	memcpy(qp.FileExtention, item->FileExtention.c_str(), item->FileExtention.size());
	memcpy(qp.FileName, item->FileName.c_str(), item->FileName.size());
	qp.QueueID = id;
	qp.Size = item->Length;
	const int size = sizeof(QueuePacket);
	char Buffer[size];
	memset(Buffer, 0, size);
	Serialize< QueuePacket>::serialize(Buffer, qp);
	send(tcpConnection.MySocket, Buffer, size, 0);
}
int main()
{
	tcpConnection = CleintConnection("127.0.0.1", 7071, Client, Reciev);
	if (tcpConnection.Init())
	{
		thread ConnectionThread = thread([&]() {tcpConnection.Start(); });
		thread SendThread = thread([&]() {
			int m;
			std::cin >> m;
				SendFile("C:\\Users\\amirr\\Desktop\\AP_99\\Document\\CPPCLI_CSharpCLR.zip");
			});
		ConnectionThread.join();
		SendThread.join();
	}
	else
	{
		return 0;
	}
}