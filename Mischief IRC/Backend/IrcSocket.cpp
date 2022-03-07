#include "pch.h"
#include "IrcSocket.h"

byte IrcSocket::Connect(PCSTR host, PCSTR port)
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

	if (getaddrinfo(host, port, &hints, &result))
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

	// ToDo: Output success message to the user.
	return 0;
}

byte IrcSocket::Disconnect()
{

	if (shutdown(_socket, SD_SEND) == SOCKET_ERROR)
	{
		// ToDo: Output error message to the user.
		closesocket(_socket);
		WSACleanup();
		return 1;
	}

	closesocket(_socket);
	WSACleanup();
	return 0;
}
