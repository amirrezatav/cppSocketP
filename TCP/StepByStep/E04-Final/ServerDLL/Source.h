#ifndef SOURCE_H
#define SOURCE_H
#include <windows.h>

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

typedef void(* UIChangeProgress)(int queueid, int value);
typedef void(* UINewClient)(string username , bool flag);
typedef void(* UINewRecieve)(int Queueid, std::string Name, std::string Extention);

UIChangeProgress  uiChangeProgress;
UINewClient  uiNewClient;
UINewRecieve  uiNewRecieve;


#ifdef UI_ALPI
#define  UI_ALPI __declspec(dllexport)
#else
#define  UI_ALPI __declspec(dllimport)
#endif // DEBUG


void  Client(int Socketid, bool flag);
void  changeprogress(int queueid, int i);
void  Recieve(int socketid, char* buffer, int size);


extern "C" UI_ALPI void  Startup(string ip, int port, UIChangeProgress  uiChangeprogress, UINewClient uiNewclient, UINewRecieve  uiNewrecieve);

extern "C" UI_ALPI void StartDownload( int queueid);
extern "C" UI_ALPI void sendmessage();
extern "C" UI_ALPI int SendFile(string path, string username);
#endif // !SOURCE_H
