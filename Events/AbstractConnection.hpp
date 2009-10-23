#ifndef ABSTRACT_CONNECTION__HPP
#define ABSTRACT_CONNECTION__HPP

#include "AtomicReferenceCounter.hpp"
#include "AbstractDelegate.hpp"
#include "Threading.hpp"
#include <vector>

class AbstractEvent;
class AbstractEventRef;

class ConnectionList;

//! Root class for all template connection classes.
class AbstractConnection
{
	friend class ConnectionList;
private:
	//Connections cannot be copied.
	AbstractConnection(AbstractConnection const &);
	AbstractConnection & operator=(AbstractConnection const &);
public:
	// Typeless event reference
	inline AbstractEventRef senderEventRef() const;
	// Typeless delegate of the receiver object that can be used for comparison, but cannot be invoked.
	AbstractDelegate recieverDelegate() const { return targetDelegate_; }

	void disconnect();
protected:
	AbstractConnection(AbstractEvent * ev, AbstractDelegate const & targetDelegate)
		: refCounter_()
		, outerLock_(ThreadDataRef::null())
		, innerLock_(ThreadDataRef::null())
		, event_(ev)
		, targetDelegate_(targetDelegate)
		, sourceList_(), sourceIndex_(npos)
		, targetList_(), targetIndex_(npos)
	{}

	virtual ~AbstractConnection()
	{
		assert(!sourceList_ && !targetList_);
		assert(sourceIndex_ == npos && targetIndex_ == npos);
	}
private:
	static const size_t npos = (size_t)-1;

	AtomicReferenceCounter refCounter_;
	ThreadDataRef outerLock_;
	ThreadDataRef innerLock_;
	AbstractEvent * event_;
	AbstractDelegate targetDelegate_;
	ConnectionList * sourceList_;
	size_t sourceIndex_;
	ConnectionList * targetList_;
	size_t targetIndex_;

	void retain() { refCounter_.retain(); }
	void release() { if(refCounter_.release()) delete this; }

	bool tryDisconnectWithLock(ThreadDataRef const & lock);

	void doDisconnect();
};

#endif //ABSTRACT_CONNECTION__HPP