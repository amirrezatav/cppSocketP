#ifndef PACKET_H
#define PACKET_H
#define SIZE_Buffer (20*1024)
#define SIZE_FileBuffer (SIZE_Buffer-12)-1
#define SIZE_Message 1024
#define SIZE_MessageBuffer SIZE_Message-8-1

enum Header : char
{
	queue,
	start,
	chunck,
	message
};
struct Packet
{
	Header header;
};
struct StartPacket : public Packet
{
	int QueueID;
};
struct QueuePacket : public Packet
{
	char FileName[165];
	char FileExtention[205];
	long Size;
	int QueueID;
	QueuePacket()
	{
		memset(FileName, 0, 165);
		memset(FileExtention, 0, 205);
	}
};
struct FilePacket : public Packet
{
	int QueueId;
	int Read;
	char Buffer[SIZE_FileBuffer];
	FilePacket()
	{
		memset(Buffer, 0, SIZE_FileBuffer);
	}

};
struct MessagePacket : public Packet
{
	int size;
	char Buffer[SIZE_MessageBuffer];
	MessagePacket()
	{
		memset(Buffer, 0, SIZE_MessageBuffer);
	}
};
#endif // !PACKET_H
