#ifndef MYSERV
#define MYSERV

#ifdef _WIN32
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
// linux
#endif

#include<string>
#include"myCrypt.h"

class myServ
{
private:
#ifdef _WIN32
	WSADATA wsaData;
#endif
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr, clientAddr;
	int clientAddrSize = sizeof(clientAddr);

public:
#ifdef _WIN32
	void WSA_startup();
#endif
	void Socket_create(SOCKET& );
	void Socket_bind(SOCKET& , sockaddr_in& );
	void Socket_listen(SOCKET& );
	void Socket_accept();
	void Socket_close();

	void sendHash(const SOCKET& , const Hash& );
	void sendBool(const SOCKET& , const bool& );
	void sendInt(const SOCKET& , const int& );
	void sendStr(const SOCKET& , const std::string& );

	void readHash(const SOCKET& , Hash& );
	void readBool(const SOCKET& , bool& );
	void readInt(const SOCKET& , int& );
	void readStr(const SOCKET& , std::string& );
};

#endif // MYSERV