#include "TCPListener.h"
#include "Serialize.h"
#include <thread>
#include <iostream>
#include <mutex>
#include "Queue.h"
map<string, int> ClientList;
static int ClientNum = 0;
TCPListener tcpServer;
std::mutex ClientLiatDoor;
std::mutex QueueListDoor;
std::map<int, Queue*> Queue_List;

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
void __stdcall changeprogress(int queueid , int i )
{
	QueueListDoor.lock();
	if (i == 100)
	{
		Queue_List.erase(queueid);
	}
	QueueListDoor.unlock();
}
void StartDownload(int socketid , int queueid)
{
	StartPacket sp;
	sp.header = Header::start;
	sp.QueueID = queueid;
	char Buffer[sizeof(StartPacket)];
	memset(Buffer, 0, sizeof(StartPacket));
	Serialize<StartPacket>::serialize(Buffer, sp);
	send(socketid , Buffer , sizeof(StartPacket) , 0);
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
	break;
	case Header::queue:
	{
		QueuePacket qp;
		Serialize<QueuePacket>::deserialize(buffer, qp);
		Queue* item = Queue::Download(socketid, qp.QueueID, qp.FileName, qp.FileExtention, qp.Size, changeprogress);
		QueueListDoor.lock();
		Queue_List.insert(std::pair<int, Queue*>(qp.QueueID, item));
		QueueListDoor.unlock();
		StartDownload(socketid , qp.QueueID);
	}
	break;
	case Header::start:
	{
		StartPacket sp;
		Serialize<StartPacket>::deserialize(buffer, sp);
		QueueListDoor.lock();
		auto item = Queue_List.find(sp.QueueID);
		if (item != Queue_List.end())
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
		auto item = Queue_List.find(fp.QueueId);
		Queue* queue = nullptr;
		if (item != Queue_List.end())
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
void SendFile(string path)
{
	string username;
	ClientLiatDoor.lock();
	do
	{
		cout << "Enter UserName : ";
		getline(cin, username);
	} while (ClientList.find(username) == ClientList.end());
	int ClinetID = ClientList.find(username)->second;
	ClientLiatDoor.unlock();
	QueueListDoor.lock();
	int id;
	do
	{
		id = rand() % 9000 + 1000;
	} while (Queue_List.find(id) != Queue_List.end());
	Queue* item = Queue::Upload(ClinetID, path, id, changeprogress);
	Queue_List.insert(std::pair<int, Queue*>(id, item));
	QueueListDoor.unlock();

	QueuePacket qp;
	qp.header = Header::queue;
	memcpy(qp.FileExtention, item->FileExtention.c_str(), item->FileExtention.size());
	memcpy(qp.FileName, item->FileName.c_str(), item->FileName.size());
	qp.QueueID = id;
	qp.Size = item->Lenght;
	const int size = sizeof(QueuePacket);
	char Buffer[size];
	memset(Buffer , 0 , size);
	Serialize< QueuePacket>::serialize(Buffer, qp);
	send(ClinetID , Buffer , size ,0);
}
int main()
{
	tcpServer = TCPListener("127.0.0.1", 7071, Client, Reciev);
	if (tcpServer.Init())
	{
		thread ConnectionThread = thread([&]() {tcpServer.Start();});
		thread SendThread = thread([&]() {
			while (!tcpServer.IsRunning);
			string path;
			cout << "Enter Path : ";
			getline ( cin, path);
			SendFile(path);
			});
		ConnectionThread.join();
		SendThread.join();
	}
	else
	{
		return 0;
	}
}