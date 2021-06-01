#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include "Client.h"
#include "PACKET.h"
enum QUEUETYPE
{
	Download,
	Upload
};
class Queue
{
private:
	Queue();
	void TransferProc(Queue*); // For Upload
	int QueueID;
	std::string FilePath;
	std::string FileName;
	std::string FileExtention;
	std::thread SendThread;

	std::mutex SendDOOR;
	std::mutex RecieveDOOR;

	std::ifstream readfile;
	std::ofstream writefile;

	bool Runnig;
	
	Client* client;

	char buffer[SIZE_FilePacket];
public:
	long Trasnfered;
	long Index;
	int Progress, LastProgress;
	long Length;
	QUEUETYPE Type;

	static Queue*  UploadQueue(Client* client , std::string FilePath);
	static Queue* DownloadQueue(std::string FileName , std::string FileExtention , long Size , int QueuID);

	void Start();
	void Close();
	void Write(const char const* bytes, long size); // For Downlaod
};
#endif
