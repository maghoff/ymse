#ifndef YMSE_OPPOSITE_KEYS_HPP
#define YMSE_OPPOSITE_KEYS_HPP

#include <boost/noncopyable.hpp>

namespace ymse {

class bindable_keyboard_handler;

class opposite_keys : public boost::noncopyable {
	bool neg, pos;

public:
	opposite_keys(bindable_keyboard_handler&, int neg, int pos);
	~opposite_keys();

	int val() const;
};

}

#endif
