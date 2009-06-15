#include <boost/bind.hpp>
#include "bindable_keyboard_handler.hpp"
#include "key.hpp"

namespace ymse {

namespace {

void set(bool* s, bool pos) { *s = pos; }

}

key::key(bindable_keyboard_handler& kbd, int key) :
	state(false)
{
	kbd.bind(key, boost::bind(&set, &state, _1));
}


key::~key() {
}

bool key::val() const {
	return state;
}

}
