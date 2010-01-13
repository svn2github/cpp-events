#ifndef __CPP_EVENTS__BORROWABLE_DATA__HPP
#define __CPP_EVENTS__BORROWABLE_DATA__HPP

#include "AbstractConnection.hpp"
#include <cassert>
#include <vector>

namespace Cpp {
namespace Private {
namespace Events {
//------------------------------------------------------------------------------
typedef std::vector<AbstractConnection*> ConnectionsVector;
//------------------------------------------------------------------------------
class BorrowableData
{
	DISABLE_COPY(BorrowableData)
public:
	class Borrower;

	BorrowableData()
		: data_()
		, borrowed_()
	{}

	~BorrowableData()
	{
		assert(!borrowed_);
	}

	bool isBorrowed() const { return borrowed_ != 0; }

	ConnectionsVector const & constRef() const
	{
		if(borrowed_)
		{
			assert(data_.empty());
			return *borrowed_;
		}
		return data_;
	}

	ConnectionsVector & mutableRef()
	{
		detach();
		return data_;
	}

	void detach()
	{
		if(borrowed_)
		{
			assert(data_.empty());
			data_ = *borrowed_;
			borrowed_ = 0;
		}
	}
private:
	ConnectionsVector data_;
	ConnectionsVector * borrowed_;
};
//------------------------------------------------------------------------------
class BorrowableData::Borrower
{
	DISABLE_COPY(Borrower)
public:
	Borrower(BorrowableData const * src)
		: src_(const_cast<BorrowableData*>(src))
		, data_()
	{
		assert(!src_->borrowed_ && "Data can be borrowed only once");
		data_.swap(src_->data_);
		src_->borrowed_ = &data_;
	}

	~Borrower()
	{
		if(src_->borrowed_ == &data_)
		{
			assert(src_->data_.empty());
			data_.swap(src_->data_);
			src_->borrowed_ = 0;
		}
	}

	ConnectionsVector const & constData() const { return data_; }
private:
	BorrowableData * src_;
	ConnectionsVector data_;
};
//------------------------------------------------------------------------------
} //namespace Events
} //namespace Private
} //namespace Cpp

#endif //__CPP_EVENTS__BORROWABLE_DATA__HPP

