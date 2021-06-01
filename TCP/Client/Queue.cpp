#include "Queue.h"
ClientConnection* Queue::myConnection = nullptr;

 Queue*  Queue::UploadQueue(std::string FilePath)
{
	try
	{
		auto queue = new Queue();
		queue->FileName = FileHandler::GetFileNameWhitOutExtention(FilePath);
		queue->FileExtention = FileHandler::GetFileExtention(FilePath);
		queue->Type = QUEUETYPE::Upload;
		queue->readfile = std::ifstream(FilePath, std::ios::binary);
		if (!queue->readfile)
			throw string("File Can not Open!");
		queue->Length = queue->readfile.seekg(0, std::ios::end).tellg();
		queue->Index = 0;
		queue->QueueID = rand() % 9000 + 1000;
		queue->Trasnfered = 0;
		return queue;
	}
	catch (...)
	{
		return nullptr;
	}
}
Queue* Queue::DownloadQueue(std::string FileName, std::string FileExtention, long Size, int QueuID)
{
	try
	{
		auto queue = new Queue();
		queue->FileName = FileName;
		queue->FileExtention = FileExtention;
		queue->FilePath = FileHandler::Combine(".",FileHandler::TempPath(FileName));
		queue->Type = QUEUETYPE::Download;
		queue->writefile = std::ofstream(queue->FilePath , std::ios::binary);
		if (queue->writefile)
			throw std::string("Error");
		queue->Length = Size;
		queue->QueueID = QueuID;
		queue->Trasnfered = 0;
		return queue;
	}
	catch (...)
	{
		return nullptr;
	}
}
void Queue::Start()
{
	this->Runnig = true;
	this->SendThread = std::thread( [&](){TransferProc(this); });
}
void Queue::Close()
{

}
void Queue::Write(const char const* bytes, long readsize)
{
	std::lock_guard<std::mutex>guard (RecieveDOOR);
	this->writefile.write(bytes, readsize);
	this->Trasnfered += readsize;
}
void Queue::TransferProc(Queue *queue)
{
	while (queue->Runnig && queue->Index < queue->Length)
	{
		if (myConnection == NULL)
			throw string("Connection Error");
		SendDOOR.lock();
		memset(queue->buffer, 0, FilePacket_SIZE);
		if (!queue->Runnig) break;

		long read = (queue->Length - queue->Index) < FilePacket_SIZE ? (queue->Length - queue->Index) : FilePacket_SIZE;

		queue->readfile.read(queue->buffer, read);

		FilePacket fp;
		fp.head = Header::Chunck;
		fp.QueueID = queue->QueueID;
		fp.Buffer = queue->buffer;
		fp.Read = read;
		char Buufer[sizeof(fp)];

		Serialize<FilePacket>::serialize( Buufer , fp);
		Queue::myConnection->Send(Buufer , sizeof(fp));
		queue->Index += read;

		queue->Trasnfered += read;
		queue->Progress = (int)((queue->Trasnfered * 100) / queue->Length);
		if (queue->LastProgress < queue->Progress)
		{
			queue->LastProgress = queue->Progress;
		}
		SendDOOR.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	queue->Close();
}
Queue::Queue()
{
	myConnection = NULL;
}