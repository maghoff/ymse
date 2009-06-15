#include <iostream>
#include <boost/bind.hpp>
#include "bindable_keyboard_handler.hpp"
#include "opposite_keys.hpp"

namespace ymse {

namespace {

void set(bool* s, bool pos) { *s = pos; }

}

opposite_keys::opposite_keys(
	bindable_keyboard_handler& kbd_,
	int neg_key_, int pos_key_
) :
	kbd(kbd_),
	neg_key(neg_key_), pos_key(pos_key_),
	neg(false), pos(false)
{
	kbd.bind(neg_key, boost::bind(&set, &neg, _1));
	kbd.bind(pos_key, boost::bind(&set, &pos, _1));
}

opposite_keys::~opposite_keys() {
	kbd.unbind(neg_key);
	kbd.unbind(pos_key);
}

int opposite_keys::val() const {
	return (neg ? -1 : 0) + (pos ? 1 : 0);
}

}
