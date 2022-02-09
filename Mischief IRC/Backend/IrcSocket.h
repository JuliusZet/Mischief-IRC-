#pragma once

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
	int _socket;
	bool _isConnected;
};
