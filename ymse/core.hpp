#ifndef CORE_HPP
#define CORE_HPP

namespace ymse {

class game;
class reshaper;

class core {
public:
	core();
	virtual ~core();

	virtual void init(int argc, const char *argv[]) = 0;

	virtual void set_game_object(game*) = 0;
	virtual void set_reshaper_object(reshaper*) = 0;

	virtual int run() = 0;
};

}

#endif

