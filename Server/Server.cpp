#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "New folder/Clinet.hpp"

int main()
{
	TCPServer server(6969);
	Clinets clinte (&server);
}