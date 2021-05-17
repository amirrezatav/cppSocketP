  
//-----------------------------------------------------
// Design Name : Just For Test Server
// File Name   : Client.cpp
// Function    : Bad Code
// Coder       : Amirreza Tavakoli
//-----------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<WS2tcpip.h>
#include <cstdio>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<iterator>
#include<sstream>
#include<string>
#include <cstdio>
#include "json.hpp"
#include <bitset>
#include "ProgressBar1.hpp"
#pragma comment (lib, "Ws2_32.lib")
using namespace std;
using Json = nlohmann::json;
#define BUFFERLENGTH 80 * 1024
#define ServerPORT 6969
#define ServerIP "127.0.0.1"
SOCKET MySocket;
sockaddr_in My_address;


enum Header
{
	FileInfo,
	Message,
	File,
	SendAuthorize
}; 

string GetFileName(string path)
{
	for (int i = path.length(); i >= 0; i--)
		if (path[i] == '\\')
			return path.substr(i + 1);
	return path;
}
string GetFileExtention(string path)
{
	string filename = GetFileName(path);
	size_t i = filename.rfind('.', filename.length());
	if (i != string::npos) {
		return(filename.substr(i, filename.length() - i));
	}
}
string GetFileNameWhitOutExtention(string path)
{
	string filename = GetFileName(path);
	size_t i = filename.rfind('.', filename.length());
	if (i != string::npos) {
		return(filename.substr(0, i));
	}
}
inline string TempPath(string Filename, string Extention = ".tmp")
{
	return Filename + Extention;
}
inline bool IsFileExist(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}
bool ConvertTmpToStableFile(const string& tmppath, const string& destinationpath)
{
	if (!IsFileExist(tmppath))
		return 0;
	if (rename(tmppath.c_str(), destinationpath.c_str()) != 0)
		ConvertTmpToStableFile(tmppath, GetFileNameWhitOutExtention(destinationpath) + "_Copy" + GetFileExtention(destinationpath));
	else
		return 1;
}



bool SocketConfig()
{
	

	WSADATA Windows_Socket_info;
	WORD VerionOfWindows_Socket = MAKEWORD(2, 2);
	int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
	if (res != 0)
	{
		std::cerr << "INITIALIZE WinSock Error : " << res;
		return 0;
	}
	MySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (MySocket == INVALID_SOCKET)
	{
		std::cerr << "INITIALIZE WinSock Error : " << res;
		closesocket(MySocket);
		return 0;
	}
	
	My_address.sin_family = AF_INET;//v4
	My_address.sin_port = htons(ServerPORT);//6969
	int status = inet_pton(AF_INET, ServerIP, &My_address.sin_addr);
	if (status <= 0)
	{
		cerr << "Faild . Error code = " << WSAGetLastError();
		return 0;
	}
	return 1;
}
void Connection(SOCKET& MySocket, sockaddr_in& My_address)
{
	while (true)
	{
		int status = connect(MySocket, (sockaddr*)&My_address, sizeof(My_address));
		if (status < 0)
			cerr << "[Log] :Please Wait Connection Error !\n";
		else
			break;
		Sleep(2 * 1000);

	}
	clog << "[Log] :Connected To Server !\n";

}

bool SendBufferSize(long buffersize)
{
	stringstream st;
	st << bitset<8 * sizeof(long) >(buffersize);
	int status = send(MySocket, st.str().c_str(), 8 * sizeof(long), 0);;
	if (status < 0)
	{
		cerr << "Send Error !\n";
		return 0;
	}
	clog << "[LOG] : Data Send\n";
	return 1;
}
bool Send(const char * buffer , long buffersize)
{
	if (SendBufferSize(buffersize))
	{
		int status = send(MySocket, buffer, BUFFERLENGTH, 0);
		if (status < 0)
		{
			cerr << "Send Error !\n";
			return 0;
		}
		clog << "[LOG] : Data Send\n";

		return 1;
	}
	return 0;
}
//struct Header
//{
//	long size;
//	string Extention;
//	string Filename;
//	Type type;
//	Json Encode()
//	{
//		Json json;
//		json["size"] = size;
//		json["Extention"] = Extention;
//		json["Filename"] = Filename;
//		json["type"] = type;
//		return  json;
//	}
//	void Decode(string input)
//	{
//		auto json = Json::parse(input);;
//		size = json["size"].get<int>();
//		Extention = json["Extention"].get<string>();
//		Filename = json["Filename"].get<string>();
//		type = json["type"].get<Type>();
//	}
//};

void SendFile(const string& source)
{
	char Buffer[BUFFERLENGTH];
	ifstream ifs(source, ios::binary);
	long size = ifs.seekg(0, ios::end).tellg();
	ifs.seekg(0, ios::beg);
	istreambuf_iterator<char> inputstream(ifs);
	long Current = 0;
	Json json;
	json["size"] = size;
	json["Extention"] = GetFileExtention(source);
	json["Filename"] = GetFileNameWhitOutExtention(source);
	json["type"] = Header::FileInfo;
	strcpy(Buffer, json.dump().c_str());

	Send(Buffer, json.dump().length());
	char License[1];
	char RecievedBufferSize[8 * sizeof(long)];
	long RecievedSize;
	int iResult = recv(MySocket, RecievedBufferSize, 8 * sizeof(long), 0);
	clog << "[LOG] : recv SendAuthorize Size\n";
	if (iResult > 0)
	{
		 RecievedSize = std::stol(RecievedBufferSize, 0, 2);
		 clog << "[LOG] : recv SendAuthorize Data\n";

		if (RecievedSize > 0)
		{
			recv(MySocket, Buffer, BUFFERLENGTH, 0);
		}
	}
	 json = Json::parse(string(Buffer, RecievedSize));

	Header Head = json["type"].get<Header>();
	clog << "[LOG] : Start File Sending\n";
	if (Header::SendAuthorize == Head)
	{
		
		while (Current < size)
		{
			long readindex = size - Current < BUFFERLENGTH  ? size - Current : BUFFERLENGTH ;
			copy_n(inputstream, readindex, Buffer);
			ifs.seekg(1, ios::cur);
			Current += readindex;
			Send(Buffer, readindex);
		}
		clog << "[LOG] : Finish\n";
	}
	ifs.close();
}
bool Recive(char* buffer, long& buffersize)
{
	int status = recv(MySocket, buffer, BUFFERLENGTH, 0);
	buffersize = strlen(buffer);

	if (status < 0) {
		std::cerr << "abort\n";
		closesocket(MySocket); //clean up
		WSACleanup(); //clean up
		return 0;
	}
}
void ReceiveFile(string path , int size)
{
	ofstream ofstmp(path, ios::binary);
	ostreambuf_iterator<char> outfile(ofstmp);
	char Buffer[BUFFERLENGTH];
	long Current = 0;
	while (Current < size)
	{
		long readindex ;
		Recive(Buffer, readindex);
		copy_n(Buffer, readindex, outfile);
		Current += readindex;
	}
	ofstmp.close();
}
int main()
{	
	if (SocketConfig())
	{
		Connection(MySocket, My_address);
		string path;
		cout << "File Path : (For Example : C:\\Users\\amirr\\Pictures\\Test.png)";
		getline(cin, path);
		SendFile(path);
	}
	closesocket(MySocket);
	WSACleanup();
}
