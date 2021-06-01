#pragma once
#ifndef PACKET_H
#define PACKET_H
#define SIZE_BUFFER 8 * 1024 //8192
#define SIZE_StartQueuePacket sizeof(StartQueuePacket) //380
#define SIZE_FilePacket SIZE_BUFFER-4*sizeof(int)-1 //8192
#define SIZE_MeasgePacket (SIZE_BUFFER-2*sizeof(int)-1)//8192

enum Header : char
{
	queue,
	Start,
	Stop,
	Chunck,
	Message,
	HeartBit
}; // 
struct PACKET 
{
	Header head;
};
struct StartQueuePacket  : public PACKET // Queue
{
	char FileName[165];
	char FileExtention[205];
	long Size;
	int QueueID;
};
struct FilePacket  : public PACKET // Chunck
{
	int QueueID;
	int Index;
	int Read;
	char *Buffer; // 8180
};
struct MeasgePacket  : public PACKET // Message
{
	int size;
	char Buffer[SIZE_MeasgePacket];
};
#endif // !PACKET_H

