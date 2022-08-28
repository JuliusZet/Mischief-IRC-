#pragma once

#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>

using std::string;

class IrcSocket
{
public:
	byte Connect(string host, string port);
	byte Disconnect();
	byte SendData(string data);
	string ReceiveData();
	bool IsConnected();

private:
	SOCKET _socket{};
	bool _isConnected{};
	string _bufferRemainder{};
};
