// Add nlohmann json from Nuget 

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Clinet.hpp"

int main()
{
	TCPServer server(6969);
	Clinets clinte (&server);
}
