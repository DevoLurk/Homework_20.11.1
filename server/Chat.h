#ifndef CHAT
#define CHAT

#ifdef _WIN32
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
#include<conio.h>
#else
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif

#include<fstream>
#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<unordered_map>
#include<vector>
#include<deque>

#include"User.h"
#include"myCrypt.h"

#ifdef max // std::numeric_limits<std::streamsize>::max()
#undef max
#endif

#define PORT 50306

class Chat
{
private:
	int current_user;
	std::string save_path{ "ChatData.data" };
	std::vector<User> users_array;
	std::deque<std::string> public_msgArr;
	std::unordered_map<std::string, Hash> pass_table;

#ifdef _WIN32
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr, clientAddr;
	int clientAddrSize = sizeof(clientAddr);
#else
	int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
#endif

	// screens
	void scr_load();
	void scr_exit();
	void scr_work();

	// common commands
	void clear_screen();
	void clearLine();
	void myCinClear();
	void rememberMail(std::string str);
	void mySleep(int time = 120);
	bool findUser(const std::string& name, int& pos);

	// save to file functions
	bool save();
	bool load();
	void saveStr(std::string& str, std::ofstream& fout);
	void loadStr(std::string& str, std::ifstream& fin);
	void saveHash(Hash& hash, std::ofstream& fout);
	void loadHash(Hash& hash, std::ifstream& fin);

	// server functions
	void sv_timeout();
	void sv_create();
	void sv_closeConnection();
	void sv_gettask(const int& connection_descriptor, std::string& name, std::string& task);

	void sv_sendHash(const int& connection_descriptor, const Hash& hash);
	void sv_sendBool(const int& connection_descriptor , const bool& flag);
	void sv_sendInt(const int& connection_descriptor, const int& integer);
	void sv_sendStr(const int& connection_descriptor, const std::string& str);

	void sv_readHash(const int& connection_descriptor, Hash& hash);
	void sv_readBool(const int& connection_descriptor, bool& flag);
	void sv_readInt(const int& connection_descriptor, int& integer);
	void sv_readStr(const int& connection_descriptor, std::string& str);

public:
	Chat();
	Chat(std::string path);
	Chat(Chat& other) = delete;
	Chat& operator=(Chat& other) = delete;

	void start();
};

#endif // CHAT