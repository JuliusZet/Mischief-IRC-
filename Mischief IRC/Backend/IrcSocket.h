#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>

class IrcSocket
{
public:
	byte Connect(PCSTR host, PCSTR port);
	byte Disconnect();
	byte SendData(std::string data);
	std::string ReceiveData();

	bool IsConnected()
	{
		return _isConnected;
	};

private:
	SOCKET _socket{};
	bool _isConnected{};
};
