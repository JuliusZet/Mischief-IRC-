#include "pch.h"
#include "IrcSocket.h"

#define DEFAULT_BUFLEN 4096

byte IrcSocket::Connect(std::string host, std::string port)
{
	WSADATA wsaData{};

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		// ToDo: Output error message to the user.
		return 1;
	}

	struct addrinfo
		* result = NULL,
		* ptr = NULL,
		hints{};

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(PCSTR(host.c_str()), PCSTR(port.c_str()), &hints, &result))
	{
		// ToDo: Output error message to the user.
		WSACleanup();
		return 2;
	}

	ptr = result;

	_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (_socket == INVALID_SOCKET)
	{
		// ToDo: Output error message to the user.
		freeaddrinfo(result);
		WSACleanup();
		return 3;
	}

	if (connect(_socket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR)
	{
		closesocket(_socket);
		_socket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (_socket == INVALID_SOCKET)
	{
		// ToDo: Output error message to the user.
		WSACleanup();
		return 4;
	}

	_isConnected = true;

	// ToDo: Output success message to the user.
	return 0;
}

byte IrcSocket::Disconnect()
{
	_isConnected = false;

	if (shutdown(_socket, SD_SEND) == SOCKET_ERROR)
	{
		// ToDo: Output error message to the user.
		closesocket(_socket);
		WSACleanup();
		return 1;
	}

	closesocket(_socket);
	WSACleanup();

	// ToDo: Output success message to the user.
	return 0;
}

byte IrcSocket::SendData(std::string data)
{
	if (_isConnected)
	{
		if (send(_socket, data.c_str(), int(data.length()), 0) != SOCKET_ERROR)
		{
			return 0;
		}

		else
		{
			// ToDo: Output error message to the user.
			Disconnect();
			return 2;
		}
	}

	else
	{
		// ToDo: Output error message to the user.
		return 1;
	}
}

std::string IrcSocket::ReceiveData()
{
	char buffer[DEFAULT_BUFLEN]{};

	if (recv(_socket, buffer, DEFAULT_BUFLEN, 0) > 0)
	{
		return std::string(buffer);
	}

	else
	{
		Disconnect();
		return "";
	}
}
