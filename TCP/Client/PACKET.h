#pragma once
#ifndef PACKET_H
#define PACKET_H
#define BUFFER_SIZE 8 * 1024
#define StartQueuePacket_SIZE BUFFER_SIZE - 165 - 205 - sizeof(long) - 4 
#define FilePacket_SIZE BUFFER_SIZE - 3 * sizeof(int)
#define MeasgePacket_SIZE BUFFER_SIZE - 4
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
	char Buffer[MeasgePacket_SIZE];
};
#endif // !PACKET_H

