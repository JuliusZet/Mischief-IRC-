#include "pch.h"
#include "Core/IRC/IrcClient.h"

byte IrcClient::Connect(string host, string port, string pass, string nick, string user, string realname)
{
	if (_ircSocket.Connect(host, port) == 0)
	{
		if (Send("PASS :" + pass) == 0)
		{
			if (Send("NICK :" + nick) == 0)
			{
				_nick = nick;

				if (Send("USER " + user + " 0 * :" + realname) == 0)
				{
					_isConnected = true;

					_receiveThread = ReceiveAsync();
					_receiveThread.detach();
					
					return 0;
				}

				else
				{
					return 4;
				}
			}

			else
			{
				return 3;
			}
		}

		else
		{
			return 2;
		}

	}

	else
	{
		return 1;
	}
}

byte IrcClient::Disconnect(string quitMessage)
{
	if (_isConnected)
	{
		if (!quitMessage.empty())
		{
			Send("QUIT :" + quitMessage);
		}

		else
		{
			Send("QUIT");
		}

		if (_receiveThread.joinable())
		{
			_receiveThread.join();
		}

		_isConnected = false;
	}

	return _ircSocket.Disconnect();
}

byte IrcClient::Disconnect()
{
	return Disconnect("");
}

byte IrcClient::Reconnect(string quitMessage, string host, string port, string pass, string nick, string user, string realname)
{
	Disconnect(quitMessage);
	return Connect(host, port, pass, nick, user, realname);
}

byte IrcClient::Reconnect(string host, string port, string pass, string nick, string user, string realname)
{
	return Reconnect("", host, port, pass, nick, user, realname);
}

void IrcClient::AddChannel(IrcChannel ircChannel)
{
	Channels.push_back(ircChannel);
	OnNewChannel.InvokeFunctions(ircChannel);
}

byte IrcClient::Send(string data)
{
	if (data.length() < 511)
	{
		return _ircSocket.SendData(data + "\r\n");
	}

	else
	{
		return 3;
	}
}

byte IrcClient::SendPrivmsg(string receiver, string text)
{
	if (receiver.length() + text.length() < 501)
	{
		Process(IrcMessage(_nick, "PRIVMSG", vector<string>{receiver, text}));
		return Send("PRIVMSG " + receiver + " :" + text);
	}

	else
	{
		size_t maxTextLength{ 500 - receiver.length() };
		byte returnValue{};

		for (size_t currentPos{}; currentPos < text.length() && returnValue == 0; currentPos += maxTextLength)
		{
			Process(IrcMessage(_nick, "PRIVMSG", vector<string>{receiver, text.substr(currentPos, maxTextLength)}));
			returnValue = Send("PRIVMSG " + receiver + " :" + text.substr(currentPos, maxTextLength));
		}

		return returnValue;
	}
}

byte IrcClient::Receive()
{
	string buffer = _ircSocket.ReceiveData();

	string message{};
	istringstream iStringStream{ buffer };

	while (getline(iStringStream, message))
	{
		if (!message.empty())
		{
			if (message.ends_with('\r'))
			{
				message.pop_back();
			}

			Process(Parse(message));
		}
	}

	return 0;
}

IrcMessage IrcClient::Parse(string message)
{
	IrcMessage ircMessage{};
	ircMessage.Time = system_clock::now();

	size_t currentPosStart{};
	size_t currentPosEnd{};

	// If the message has a prefix
	if (message.starts_with(':'))
	{

		// Get prefix
		currentPosEnd = message.find(' ', currentPosStart);
		ircMessage.Prefix = message.substr(1, currentPosEnd - 1);
		currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);
	}

	// Get command
	currentPosEnd = message.find(' ', currentPosStart);
	ircMessage.Command = message.substr(currentPosStart, currentPosEnd - currentPosStart);
	currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);

	// Get parameter(s)
	for (; currentPosStart != message.size() && currentPosEnd != string::npos; currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1))
	{
		if (message.at(currentPosStart) != ':')
		{
			currentPosEnd = message.find(' ', currentPosStart);
			ircMessage.Parameters.push_back(message.substr(currentPosStart, currentPosEnd - currentPosStart));
		}

		else
		{
			++currentPosStart;
			ircMessage.Parameters.push_back(message.substr(currentPosStart));
			break;
		}
	}

	return ircMessage;
}

byte IrcClient::Process(IrcMessage ircMessage)
{
	if (ircMessage.Command == "PRIVMSG")
	{

		// 1 receiver
		if (ircMessage.Parameters.front().find(',') == string::npos)
		{

			// If it is a channel message or a direct message from us, add the message to a channel named after the receiver
			if (ircMessage.Parameters.front() != _nick)
			{
				AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
			}

			// If it is a direct message for us, add the message to a direct message channel, named after the sender
			else
			{
				AddMessageToChannel(ircMessage, ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')));
			}
		}

		// >= 2 receivers
		else
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != ircMessage.Parameters.front().size() && currentPosEnd != string::npos; currentPosStart = ircMessage.Parameters.front().find_first_not_of(',', currentPosEnd + 1))
			{
				currentPosEnd = ircMessage.Parameters.front().find(',', currentPosStart);

				// If it is a channel message or a direct message from us, add the message to a channel named after the receiver
				if (ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart) != _nick)
				{
					AddMessageToChannel(ircMessage, ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
				}

				// If it is a direct message for us, add the message to a direct message channel, named after the sender
				else
				{
					AddMessageToChannel(ircMessage, ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')));
				}
			}
		}
	}

	else if (ircMessage.Command == "JOIN")
	{

		// 1 channel
		if (ircMessage.Parameters.front().find(',') == string::npos)
		{
			AddUsersToChannel(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')), ircMessage.Parameters.front());
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// >= 2 channels
		else
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != ircMessage.Parameters.front().size() && currentPosEnd != string::npos; currentPosStart = ircMessage.Parameters.front().find_first_not_of(',', currentPosEnd + 1))
			{
				currentPosEnd = ircMessage.Parameters.front().find(',', currentPosStart);
				AddUsersToChannel(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')), ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
				AddMessageToChannel(ircMessage, ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
			}
		}
	}

	else if (ircMessage.Command == "PART")
	{

		// 1 channel
		if (ircMessage.Parameters.front().find(',') == string::npos)
		{
			RemoveUserFromChannel(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')), ircMessage.Parameters.front());
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// >= 2 channels
		else
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != ircMessage.Parameters.front().size() && currentPosEnd != string::npos; currentPosStart = ircMessage.Parameters.front().find_first_not_of(',', currentPosEnd + 1))
			{
				currentPosEnd = ircMessage.Parameters.front().find(',', currentPosStart);
				RemoveUserFromChannel(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')), ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
				AddMessageToChannel(ircMessage, ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
			}
		}
	}

	else if (ircMessage.Command == "QUIT")
	{
		for (IrcChannel& channel : Channels)
		{
			for (IrcChannelUser& user : channel.Users)
			{
				if (user.Nick == ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')))
				{
					RemoveUserFromChannel(user.Nick, channel.Name);
					AddMessageToChannel(ircMessage, channel.Name);
					break;
				}
			}
		}
	}

	else if (ircMessage.Command == "MODE")
	{

		// Channel mode
		if (ircMessage.Parameters.front().starts_with('#'))
		{
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// User mode
		else
		{
			AddMessageToChannel(ircMessage, "IRC");
		}
	}

	else if (ircMessage.Command == "PING")
	{
		return Send("PONG :" + ircMessage.Parameters.front());
	}

	// RPL_TOPIC
	else if (ircMessage.Command == "332")
	{
		SetTopicOfChannel(ircMessage.Parameters.at(2), ircMessage.Parameters.at(1));
	}

	// RPL_NAMREPLY
	else if (ircMessage.Command == "353")
	{
		AddUsersToChannel(ircMessage.Parameters.at(3), ircMessage.Parameters.at(2));
	}

	else
	{
		AddMessageToChannel(ircMessage, "IRC");
	}

	return 0;
}

byte IrcClient::AddMessageToChannel(IrcMessage ircMessage, string channelName)
{
	for (IrcChannel& channel : Channels)
	{
		if (channel.Name == channelName)
		{
			channel.AddMessage(ircMessage);
			return 0;
		}
	}

	AddChannel(IrcChannel(channelName));
	Channels.back().AddMessage(ircMessage);

	return 1;
}

byte IrcClient::SetTopicOfChannel(string topic, string channelName)
{
	for (IrcChannel& channel : Channels)
	{
		if (channel.Name == channelName)
		{
			channel.Topic = topic;
			return 0;
		}
	}

	AddChannel(IrcChannel(channelName));
	Channels.back().Topic = topic;

	return 1;
}

byte IrcClient::AddUsersToChannel(string users, string channelName)
{
	for (IrcChannel& channel : Channels)
	{
		if (channel.Name == channelName)
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != users.size() && currentPosEnd != string::npos; currentPosStart = users.find_first_not_of(' ', currentPosEnd + 1))
			{
				currentPosEnd = users.find(' ', currentPosStart);
				channel.Users.push_back(IrcChannelUser(users.substr(currentPosStart, currentPosEnd - currentPosStart)));
			}

			return 0;
		}
	}

	AddChannel(IrcChannel(channelName));
	for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != users.size() && currentPosEnd != string::npos; currentPosStart = users.find_first_not_of(' ', currentPosEnd + 1))
	{
		currentPosEnd = users.find(' ', currentPosStart);
		Channels.back().Users.push_back(IrcChannelUser(users.substr(currentPosStart, currentPosEnd - currentPosStart)));
	}

	return 1;
}

byte IrcClient::RemoveUserFromChannel(string user, string channelName)
{
	for (IrcChannel& channel : Channels)
	{
		if (channel.Name == channelName)
		{
			for (size_t i{}; i != channel.Users.size(); ++i)
			{
				if (channel.Users.at(i).Nick == user)
				{
					channel.Users.erase(channel.Users.begin() + i);
					return 0;
				}

				return 1;
			}
		}

		return 2;
	}
}

thread IrcClient::ReceiveAsync()
{
	return thread{ [this] {
		while (_isConnected)
		{
			Receive();
		}
	} };
}

bool IrcClient::IsConnected()
{
	return _isConnected;
}
