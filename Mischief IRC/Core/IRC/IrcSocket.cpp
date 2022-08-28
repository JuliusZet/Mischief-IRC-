#include "pch.h"
#include "Core/IRC/IrcSocket.h"

#define DEFAULT_BUFLEN 4096

byte IrcSocket::Connect(string host, string port)
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

byte IrcSocket::SendData(string data)
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

string IrcSocket::ReceiveData()
{
	char bufferCurrent[DEFAULT_BUFLEN]{};

	if (recv(_socket, bufferCurrent, DEFAULT_BUFLEN - 1, 0) > 0)
	{
		string buffer = _bufferRemainder + bufferCurrent;
		_bufferRemainder.clear();

		// If the last message in the buffer is not complete
		if (buffer.back() != '\n')
		{

			// Store the incomplete message for the next buffer and only return the complete message(s) for now
			size_t beginOfLastMessage = buffer.find_last_of('\n') + 1;
			_bufferRemainder = buffer.substr(beginOfLastMessage);
			buffer = buffer.substr(0, beginOfLastMessage);
		}

		return buffer;
	}

	else
	{
		Disconnect();
		return "";
	}
}

bool IrcSocket::IsConnected()
{
	return _isConnected;
}
