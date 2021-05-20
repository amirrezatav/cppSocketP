# Socket Programming in C/C++
## Introduction
Socket programming is a way of connecting two nodes on a network to communicate with each other. 

One socket(node) listens on a particular port at an IP, while other socket reaches out to the other to form a connection. 

Server forms the listener socket while client reaches out to the server.

We can communicate easily without losing any data

If we take a real-life example then the socket we see in reality is a medium to connect two devices or systems.

It can be either a phone charger plugging into the socket or a USB cable into our laptop. 

In the same way, Sockets let applications attach to the local network at different ports. 

Every time a socket is created, the program has to specify the socket type as well as the domain address.

Sockets are a mechanism for exchanging data between processes. These processes can either be on the same machine, or on different machines connected via a network. Once a socket 

connection is established, data can be sent in both directions until one of the endpoints closes the connection

The goal of this article is to teach you how to use the ClientSocket and ServerSocket classes in your own applications.

## Client-Server Definition

Client-server denotes a relationship between cooperating programs in an application, composed of clients initiating requests for services and servers providing that function or service. 

## IP address definition
An IP address is a unique address that identifies a device on the internet or a local network. 

IP stands for "Internet Protocol," which is the set of rules governing the format of data sent via the internet or local network.

In essence, IP addresses are the identifier that allows information to be sent between devices on a network: they contain location information and make devices accessible for communication. The internet needs a way to differentiate between different computers, routers, and websites. IP addresses provide a way of doing so and form an essential part of how the internet works.
## What is an IP?
An IP address is a string of numbers separated by periods. IP addresses are expressed as a set of four numbers — an example address might be 192.158.1.38. Each number in the set can range from 0 to 255.

So, the full IP addressing range goes from 0.0.0.0 to 255.255.255.255.

IP addresses are not random. They are mathematically produced and allocated by the Internet Assigned Numbers Authority (IANA), a division of the Internet Corporation for Assigned Names and Numbers (ICANN). ICANN is a non-profit organization that was established in the United States in 1998 to help maintain the security of the internet and allow it to be usable by all. Each time anyone registers a domain on the internet, they go through a domain name registrar, who pays a small fee to ICANN to register the domain.
## The IPv4 Address.

The common type of IP address (is known as IPv4, for “version 4”). Here’s an example of what an IP address might look like:

66.171.248.170

An IPv4 address consists of four numbers, each of which contains one to three digits, with a single dot (.) separating each number or set of digits. Each of the four numbers can range from 0 to 255.
## Localhost

"Localhost" refers to the local computer that a program is running on. For example, if you are running a Web browser on your computer, your computer is considered to be the "localhost." 

For example, a network administrator might use his local machine to start a Web server on one system and use a remote access program on another. These programs would run from computers other than the localhost.In the example above, the two non-local computers must be defined by their IP addresses. The local machine is defined as "localhost," which gives it an IP address of 127.0.0.1. This is considered a "loopback" address because the information sent to it is routed back to the local machine. Localhost is often used in Web scripting languages like PHP and ASP when defining what server the code should run from or where a database is located.
## The IPv6 Address.

It’s called IPv6 and it offers a maximum number of IP address for today and for the future.

Whereas IPv4 supports a maximum of approximately 4.3 billion unique IP addresses, IPv6 supports, in theory, a maximum number that will never run out.

A theoretical maximum of 340,282,366,920,938,463,463,374,607,431,768,211,456. To be exact. In other words, we will never run out of IP addresses again.

An IPv6 address consists of eight groups of four hexadecimal digits. If a group consists of four zeros, the notation can be shortened using a colon to replace the zeros. Here’s an example IPv6 address:

2001:0db8:85a3:0000:0000:8a2e:0370:7334
## Port 

In computer networking, a port is a communication endpoint

A port is a virtual point where network connections start and end.

Ports are software-based and managed by a computer's operating system.

Each port is associated with a specific process or service.

Ports allow computers to easily differentiate between different kinds of traffic: emails go to a different port than webpages, for instance, even though both reach a computer over the same Internet connection.

Ports are standardized across all network-connected devices, with each port assigned a number. Most ports are reserved for certain protocols — for example, all Hypertext Transfer Protocol (HTTP) messages go to port 80. While IP addresses enable messages to go to and from specific devices, port numbers allow targeting of specific services or applications within those devices.

Vastly different types of data flow to and from a computer over the same network connection. The use of ports helps computers understand what to do with the data they receive.

Suppose Amirreza transfers an MP3 audio recording to Ali using the File Transfer Protocol (FTP). If Alice's computer passed the MP3 file data to Alice's email application, the email application would not know how to interpret it. But because Amirreza’s file transfer uses the port designated for FTP (port 21), Alice's computer is able to receive and store the file.

Port Range Groups
* **0 to 1023**– Well known port numbers. Only special companies like Apple QuickTime, MSN, SQL Services, Gopher Services, and other prominent services have these port numbers.
* **1024 to 49151** – Registered ports; meaning they can be registered to specific protocols by software corporations.
* **49152 to 65536** – Dynamic or private ports; meaning that they can be used by just about anybody.

## DNS 
he process of DNS resolution involves converting a hostname (such as www.example.com) into a computer-friendly IP address (such as 192.168.1.1). An IP address is given to each device on the Internet, and that address is necessary to find the appropriate Internet device - like a street address is used to find a particular home. When a user wants to load a webpage, a translation must occur between what a user types into their web browser (example.com) and the machine-friendly address necessary to locate the example.com webpage.
## What is an IP packet?
IP packets are created by adding an IP header to each packet of data before it is sent on its way. An IP header is just a series of bits (ones and zeros), and it records several pieces of information about the packet, including the sending and receiving IP address. IP headers also report:
* Header length
* Packet length
* Which transport protocol is being used (TCP, UDP, etc.)

There are two prevailing types of data transfer protocol in the Internet Protocol (IP) suite:
. UDP – User Datagram Protocol
. TCP – Transmission Control Protocol
## What is TCP/IP?
(reliable, connection oriented)

The Transmission Control Protocol (TCP) is a transport protocol, meaning it dictates the way data is sent and received. A TCP header is included in the data portion of each packet that uses TCP/IP. Before transmitting data, TCP opens a connection with the recipient. TCP ensures that all packets arrive in order once transmission begins. Via TCP, the recipient will acknowledge receiving each packet that arrives. Missing packets will be sent again if receipt is not acknowledged.

TCP is designed for reliability, not speed. Because TCP has to make sure all packets arrive in order, loading data via TCP/IP can take longer if some packets are missing.
## What is UDP/IP?
(unreliable, connectionless)

The User Datagram Protocol, or UDP, is another widely used transport protocol. It's faster than TCP, but it is also less reliable. UDP does not make sure all packets are delivered and in order, and it does not establish a connection before beginning or receiving transmissions.
## What is HTTP?
The Hypertext Transfer Protocol (HTTP) is an application layer protocol for distributed.

HTTP is a protocol which allows the fetching of resources, such as HTML documents. It is the foundation of any data exchange on the Web and it is a client-server protocol, which means requests are initiated by the recipient, usually the Web browser. A complete document is reconstructed from the different sub-documents fetched, for instance text, layout description, images, videos, scripts, and more.

Clients and servers communicate by exchanging individual messages (as opposed to a stream of data). The messages sent by the client, usually a Web browser, are called requests and the messages sent by the server as an answer are called responses.

HTTP is a client-server protocol: requests are sent by one entity, the user-agent (or a proxy on behalf of it). Most of the time the user-agent is a Web browser, but it can be anything, for example a robot that crawls the Web to populate and maintain a search engine index.

Each individual request is sent to a server, which handles it and provides an answer, called the response. Between the client and the server there are numerous entities, collectively called proxies, which perform different operations and act as gateways or caches, for example.

HTTP headers

**Headers can also be grouped according to how proxies handle them:**

*	Connection:
* Keep-Alive
*	Proxy-Authenticate
*	Proxy-Authorization
*	TE
*	Trailer
*	Transfer-Encoding
*	Upgrade (see also Protocol upgrade mechanism).
	
**HTTP Methods**

*	GET
*	POST
*	PUT
*	HEAD
*	DELETE
*	PATCH
*	OPTIONS
 
## Procedure in Client-Server Communication:

o	Socket: Create a new communication
o	Bind: Attach a local address to a socket
o	Listen: Announce willingness to accept connections
o	Accept: Block caller until a connection request arrives
o	Connect: Actively attempt to establish a connection
o	Send: Send some data over a connection
o	Receive: Receive some data over a connection
o	Close: Release the connection
 
# Socket Creation 
## Stages for Server: 

    #include<iostream>
    #include<WS2tcpip.h>
    #include<thread>
    #include<sstream>
    #include<vector>
    #include<Windows.h>
    #pragma comment (lib, "Ws2_32.lib") // For Linker
    int main()
    {

    	//INITIALIZE Win Socket

    	WSADATA Windows_Socket_info;
    	WORD VerionOfWindows_Socket = MAKEWORD(2,2);
    	int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
    	if (res != 0)
	    {
	    	std::cerr << "INITIALIZE WinSock Error : " << res;
	    	return 0;
    	}
     }
## WSAStartup
    int WSAStartup (
      WORD wVersionRequested,  
      LPWSADATA lpWSAData  
    );
**Parameters**
*	`wVersionRequested`
	[in] The highest version of Windows Sockets support that the caller can use. The high order byte specifies the minor version (revision) number; the low-order byte specifies the major version number.
*	`lpWSAData`
	[out] A pointer to the WSADATA data structure that is to receive details of the Windows Sockets implementation.
  
**Remarks**

Firstly, it allows you to specify what version of WinSock you want to use. In the WSADATA that it populates, it will tell you what version it is offering you based on your request. It also fills in some other information which you are not required to look at if you aren't interested. You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.

The second thing it does, is to set-up all the "behind the scenes stuff" that your app needs to use sockets. 

The WinSock DLL file is loaded into your process, and it has a whole lot of internal structures that need to be set-up for each process. These structures are hidden from you, but they are visible to each of the WinSock calls that you make.

Because these structures need to be set-up for each process that uses WinSock, each process must call WSAStartup to initialise the structures within its own memory space, and WSACleanup to tear them down again, when it is finished using sockets.

The WSAStartup function must be the first Windows Sockets function called by an application or DLL

It allows an application or DLL to specify the version of Windows Sockets required and to retrieve details of the specific Windows Sockets implementation. 

The application or DLL can only issue further Windows Sockets functions after a successfully calling WSAStartup.

**Return Values**

The WSAStartup function returns zero if successful. Otherwise, it returns one of the error codes .

## MAKEWORD

    WORD MAKEWORD(
       BYTE bLow,
       BYTE bHigh);
**Parameters**
*	`bLow`
The low-order byte of the new value.
*	`bHigh`
The high-order byte of the new value.

     #define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
     
It basically builds a 16 bits words from two 1 bytes word (and doesn't look very portable)
The binary representation of the number 2 with 1 byte (a WORD) is : 
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
If we take the concatenate two of those bytes as in MAKEWORD(2,2) , we get:
| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
Which is 512 + 2 = 514 : live demo.
The only real life example of this particular macro is in the Initialization of Winsock, to generate the versioning word expected by WSAStartup.

## Big Endian and Little Endian
A load word or store word instruction uses only one memory address. The lowest address of the four bytes is used for the address of a block of four contiguous bytes.

How is a 32-bit pattern held in the four bytes of memory? There are 32 bits in the four bytes and 32 bits in the pattern, but a choice has to be made about which byte of memory gets what part of the pattern. There are two ways that computers commonly do this:

Big Endian Byte Order: The most significant byte (the "big end") of the data is placed at the byte with the lowest address. The rest of the data is placed in order in the next three bytes in memory.

Little Endian Byte Order: The least significant byte (the "little end") of the data is placed at the byte with the lowest address. The rest of the data is placed in order in the next three bytes in memory.

In these definitions, the data, a 32-bit pattern, is regarded as a 32-bit unsigned integer. The "most significant" byte is the one for the largest powers of two: 231, ..., 224. The "least significant" byte is the one for the smallest powers of two: 27, ..., 20.

For example, say that the 32-bit pattern 0x12345678 is stored at address 0x00400000. The most significant byte is 0x12; the least significant is 0x78.

Within a byte the order of the bits is the same for all computers (no matter how the bytes themselves are arranged).


      int main()
      {

      	//INITIALIZE Win Socket

	      WSADATA Windows_Socket_info;
      	WORD VerionOfWindows_Socket = MAKEWORD(2,2);
      	int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
      	if (res != 0)
      	{
	      	std::cerr << "INITIALIZE WinSock Error : " << res;
	      	return 0;
      	}

      	//CREATE LISTENING SOCKET
      	sockaddr_in server_address;
	      server_address.sin_family = AF_INET;
	      server_address.sin_port = htons(6969);
      	server_address.sin_addr.S_un.S_addr = INADDR_ANY;
      }
      
      
## SOCKADDR_IN
The SOCKADDR_IN structure specifies a transport address and port for the AF_INET address family.
**Syntax**

     struct sockaddr_in {
         short            sin_family;   /* Protocol family (always AF_INET) */
         unsigned short   sin_port;     /* Port number in network byte order */
         struct in_addr   sin_addr;     /* IP address in network byte order */
         unsigned char    sin_zero[8];  /* Pad to sizeof(struct sockaddr) */
     };

There are multiple protocol families. Each family has its own address structure.

Example: AF_INET uses sockaddr_in, AF_INET6 uses sockaddr_in6, AF_UNIX uses sockaddr_un, etc. But sockaddr is the base structure. All these structures must be type-cast to sockaddr while binding/connecting a socket.
     
   o IPv4 protocol  : AF_INET 
   o IPv6 protocol : AF_INET6 

Look at the sizes of the elements in the two structures sockaddr_in and sockaddr.

The first element in both structures is the same and occupies the same memory.

     sin_port --> 2 bytes
     sin_addr --> 4 bytes
     sin_zero[8] --> 8 bytes
 Total = 14 bytes (equal to size of sa_data[14])
     
     
     sockaddr_in listen_address;
     listen_address.sin_family = AF_INET;
     listen_address.sin_port = htons(666);
     listen_address.sin_addr.S_un.S_addr = INADDR_ANY;
     //ServerInfo.sin_addr.S_un.S_addr = inet_addr("192.168.1.50");


For a server, you typically want to bind to all interfaces - not just "localhost".
If you wish to bind your socket to localhost only, the syntax would be my_sockaddress.sin_addr.s_addr = inet_addr("127.0.0.1");

The inet_addr() function shall convert the string pointed to by cp, in the standard IPv4 dotted decimal notation, to an integer value suitable for use as an Internet address.

The inet_ntoa() function shall convert the Internet host address specified by in to a string in the Internet standard dot notation.

The inet_ntoa() function need not be reentrant. A function that is not required to be reentrant is not required to be thread-safe.

## htons function (winsock.h)
The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.

The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).

     u_short htons(
       u_short hostshort
     );
**Parameters**
* hostshort :
   A 16-bit number in host byte order.
   
**Return value**

The htons function returns the value in TCP/IP network byte order.

**Remarks**

The htons function takes a 16-bit number in host byte order and returns a 16-bit number in network byte order used in TCP/IP networks (the AF_INET or AF_INET6 address family).

The htons function can be used to convert an IP port number in host byte order to the IP port number in network byte order.

The htonsfunction does not require that the Winsock DLL has previously been loaded with a successful call to the WSAStartup function.

htonl, htons, ntohl, ntohs - convert values between host and network byte order

**Synopsis**

     #include <arpa/inet.h>
     uint32_t htonl(uint32_t hostlong);
     uint16_t htons(uint16_t hostshort);
     uint32_t ntohl(uint32_t netlong);
     uint16_t ntohs(uint16_t netshort);
     
**Description**

* The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
* The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
* The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.
* The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.

 #include<iostream>
      #include<WS2tcpip.h>
      #include<thread>
      #include<sstream>
      #include<vector>
      #include<Windows.h>
      #pragma comment (lib, "Ws2_32.lib")


```cpp
      int main()
      {

      	//INITIALIZE Win Socket

      	WSADATA Windows_Socket_info;
      	WORD VerionOfWindows_Socket = MAKEWORD(2,2);
      	int res = WSAStartup(VerionOfWindows_Socket, &Windows_Socket_info);
      	if (res != 0)
      	{
      		std::cerr << "INITIALIZE WinSock Error : " << res;
      		return 0;
      	}

      	//CREATE LISTENING SOCKET
	      sockaddr_in server_address;
      	server_address.sin_family = AF_INET;
	      server_address.sin_port = htons(6969);
      	server_address.sin_addr.S_un.S_addr = INADDR_ANY;

      	SOCKET Server_sock = socket(AF_INET, SOCK_STREAM, 0);

      	int status =  bind(Server_sock, (sockaddr*)&server_address, sizeof(server_address));

	      if (status == SOCKET_ERROR) {
      		std::cout << "ABORT\n";
	      	closesocket(Server_sock); //clean up
	      	WSACleanup(); //clean up
	      	return 0;
      	}
      	status = listen(Server_sock, SOMAXCONN);

      	if (status == SOCKET_ERROR) {
      		std::cout << "ABORT\n";
      		closesocket(Server_sock); //clean up
	      	WSACleanup(); //clean up
	      	return 0;
	      }
      	std::cout << "Waiting for listening . . ." << std::endl;
      }

```
## Socket creation:
   1. socketcr: socket descriptor, an integer (like a file-handle)
   
    SOCKET Server_sock  = socket(domain, type, protocol)

  * domain: integer, communication domain 
     +	IPv4 protocol  : AF_INET 
     +	IPv6 protocol : AF_INET6 
  * communication type:
     +	SOCK_STREAM: TCP
     +	SOCK_DGRAM: UDP
     +	protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet

**RETURN VALUE**

On success, zero is returned.  On error, -1 is returned, anderrno is set to indicate the error.
 2. Bind:
 
        int res = bind(int sockfd, const struct sockaddr *addr,  socklen_t addrlen);
        
After creation of the socket, bind function binds the socket to the address and port number specified in addr(custom data structure). In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.

**RETURN VALUE**

On success, zero is returned.  On error, -1 is returned, anderrno is set to indicate the error.

 3. Listen:

        int res = listen(int sockfd, int backlog); 
     
It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED.

**RETURN VALUE**

On success, zero is returned.  On error, -1 is returned, anderrno is set to indicate the error.

     
