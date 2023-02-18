#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class IrcChannelUser
{
public:
	IrcChannelUser() {}
	IrcChannelUser(string user)
	{
		if (user.starts_with('+') || user.starts_with('%') || user.starts_with('@') || user.starts_with('&') || user.starts_with('~'))
		{
			Mode = user.front();
			Nick = user.substr(1, user.size() - 1);
		}

		else
		{
			Nick = user;
		}
	}

	char Mode{};
	string Nick{};
};
