#include "bindable_keyboard_handler.hpp"

namespace ymse {

bindable_keyboard_handler::bindable_keyboard_handler() {
}

bindable_keyboard_handler::~bindable_keyboard_handler() {
}

void bindable_keyboard_handler::key_event(int key, bool state) const {
	std::map<int, callback>::const_iterator i = m.find(key);
	if (i == m.end()) return;
	i->second(state);
}

void bindable_keyboard_handler::bind(int key, callback cb) {
	m.insert(std::make_pair(key, cb));
}

void bindable_keyboard_handler::unbind(int key) {
	m.erase(key);
}

}
