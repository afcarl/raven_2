/*
 * history.h
 *
 *  Created on: Oct 9, 2012
 *      Author: benk
 */

#ifndef HISTORY_H_
#define HISTORY_H_

#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>

template<class T>
struct CloningWrapper {
	typedef boost::shared_ptr<T> ValueType;
	ValueType value;

	CloningWrapper() : value() {}
	CloningWrapper(const ValueType& theValue) : value(theValue) {}
	CloningWrapper(const CloningWrapper& other) {
		other.value->cloneInto(value);
	}

	CloningWrapper& operator=(const CloningWrapper& other) {
		other.value->cloneInto(value);
		return *this;
	}

	ValueType clone() const {
		return value->clone();
	}

	void cloneInto(ValueType& other) const {
		value->cloneInto(other);
	}
};

template<class T>
struct History {
private:
	History() {}
public:
	typedef boost::circular_buffer<CloningWrapper<T> > Type;

	/*
	static Type clone(const Type& hist) {
		Type newHist(hist.size(),CloningWrapper<T>());
		typename Type::const_reverse_iterator itr;
		for (itr=hist.rbegin();itr!=hist.rend();itr++) {
			newHist.push_front(*itr);
		}
		return newHist;
	}
	*/
};

#endif /* HISTORY_H_ */
