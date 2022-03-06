#include "pch.h"
#include "IrcSocket.h"

int IrcSocket::Init()
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

	if (getaddrinfo("bouncer.lan", "6667", &hints, &result))
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
}
