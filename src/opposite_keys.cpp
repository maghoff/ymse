#include <iostream>
#include <boost/bind.hpp>
#include "bindable_keyboard_handler.hpp"
#include "opposite_keys.hpp"

namespace ymse {

namespace {

void set(bool* s, bool pos) { *s = pos; }

}

opposite_keys::opposite_keys(
	bindable_keyboard_handler& kbd,
	int neg_key, int pos_key
) :
	neg(false), pos(false)
{
	kbd.bind(neg_key, boost::bind(&set, &neg, _1));
	kbd.bind(pos_key, boost::bind(&set, &pos, _1));
}

opposite_keys::~opposite_keys() {
}

int opposite_keys::val() const {
	return (neg ? -1 : 0) + (pos ? 1 : 0);
}

}
