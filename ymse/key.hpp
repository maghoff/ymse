#ifndef YMSE_KEY_HPP
#define YMSE_KEY_HPP

#include <boost/noncopyable.hpp>

namespace ymse {

class bindable_keyboard_handler;

class key : public boost::noncopyable {
	bool state;

public:
	key(bindable_keyboard_handler&, int);
	~key();

	bool val() const;
};

}

#endif
