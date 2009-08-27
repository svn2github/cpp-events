#include "AbstractConnection.hpp"

void AbstractConnection::disconnect()
{
	for(ListenersList::const_iterator it = listeners_.begin(); it != listeners_.end(); ++it)
	{
		(*it)(this);
	}

	delete this;
}

void AbstractConnection::doAddDisconnectListener(DisconnectDelegate const & deleg)
{
	listeners_.push_back(deleg);
}

void AbstractConnection::doRemoveDisconnectListener(DisconnectDelegate const & deleg)
{
	for(ListenersList::iterator it = listeners_.begin(); it != listeners_.end(); ++it)
	{
		if(deleg == *it)
		{
			if(it + 1 < listeners_.end())
			{
				*it = listeners_.back();
			}
			listeners_.pop_back();
			break;
		}
	}
}