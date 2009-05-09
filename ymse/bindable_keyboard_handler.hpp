#ifndef YMSE_BINDABLE_KEYBOARD_HANDLER_HPP
#define YMSE_BINDABLE_KEYBOARD_HANDLER_HPP

#include <map>
#include <boost/function.hpp>
#include "keyboard_handler.hpp"

namespace ymse {

class bindable_keyboard_handler : public keyboard_handler {
	typedef boost::function<void(bool)> callback;

private:
	std::map<int, callback> m;

public:
	bindable_keyboard_handler();
	~bindable_keyboard_handler();

	void key_event(int, bool) const;

	void bind(int, callback);
	void unbind(int);
};

}

#endif
