#ifndef ClientS_H
#define ClientS_H
#include <WinSock2.h>
#include <WS2TCPIP.h>
#include <vector>
#include <string>
#include "Connection.hpp"
#include <sstream>
#include <bitset>
#include "FileProccess.hpp"
using namespace std;
using Json = nlohmann::json;
#define BUFFERLENGTH 80 * 1024
enum Header
{
	FileInfo,
	Message,
	File,
	SendAuthorize
};
class Clinets
{
public:
	ClientInfo Client;
	TCPServer* Server;
	WriteRecievedFile* file;
	Clinets(TCPServer* server)
	{
		Server = server;
		AcceptConnection();
	}
	~Clinets()
	{
		delete(Server);
	}
private:
	void AcceptConnection()
	{
		auto v = Server->BeginAccepting();
		Client = (v);
		char RecievedBufferSize[8 * sizeof(long)];
		std::clog << "[Log]: Client Connected \n";
		BeginRecive(Client.Sock);
	}
	bool SendBufferSize(long buffersize, SOCKET Client)
	{
		stringstream st;
		st << bitset<8 * sizeof(long)>(buffersize);
		int status = send(Client, st.str().c_str(), 8 * sizeof(long), 0);;
		if (status < 0)
			return 0;
		return 1;
	}
	bool Send(const char* buffer, long buffersize, SOCKET Client)
	{
		if (SendBufferSize(buffersize , Client))
		{
			std::clog << "[Log]: Send Data \n";
			int status = send(Client, buffer, buffersize, 0);
			if (status < 0)
				return 0;
			return 1;
		}
		return 0;
	}
public:void BeginRecive(SOCKET Client)
{
	while (true)
	{
		char tmpbuffer[BUFFERLENGTH]{0};
		char RecievedBufferSize[8 * sizeof(long)];
		int iResult = recv(Client, RecievedBufferSize, 8 * sizeof(long), 0);
		if (iResult > 0)
		{
			long RecievedSize = std::stol(RecievedBufferSize, 0, 2);

			if (RecievedSize > 0)
			{
				std::clog << "[Log]: Recieved Data \n";

				recv(Client, tmpbuffer, BUFFERLENGTH, 0);
				Proccess(tmpbuffer, RecievedSize);
			}
		}
	}
}
	void Proccess(char* buffer ,const long& buffersize)
	{
		Json  json ;
		Header Head = Header::File;
		try
		{
			json = Json::parse(string(buffer, buffersize));
			Head = json["type"].get<Header>();
		}
		catch (...)
		{
			// Ignor
		}
		switch (Head)
		{
		case Header::FileInfo :
		{
			string Extention = json["Extention"].get<string>();
			string Filename = json["Filename"].get<string>();
			long size = json["size"].get<long>();
			file = new WriteRecievedFile(Filename, Extention, size);
			Json sendjson;
			sendjson["type"] = Header::SendAuthorize;
			Send(sendjson.dump().c_str(), sizeof(sendjson), Client.Sock);
		}
			break;
		case Header::File:
			file->StartWrite(buffer, buffersize);
			break;
		default:
			break;
		}

		
	}
};


#endif // !Client_H
