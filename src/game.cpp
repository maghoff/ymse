#include "game.hpp"

namespace ymse {

game::game() :
	ticks(0)
{
}

game::~game() {
}

void game::tick(unsigned msecs) {
	for (unsigned i=0; i<msecs; ++i) {
		tick_ms();
		if ((ticks + i) % 10 == 0) tick_10ms();
	}
	ticks += msecs;
}

void game::tick_ms() { }
void game::tick_10ms() { tick(); }
void game::tick() { }

}

