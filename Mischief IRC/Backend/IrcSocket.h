#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>

class IrcSocket
{
public:
	int Init();
	int Connect(std::string host, int port);
	void Disconnect();
	int SendData(std::string data);
	std::string ReceiveData();

	bool IsConnected()
	{
		return _isConnected;
	};

private:
	SOCKET _socket{};
	bool _isConnected{};
};
