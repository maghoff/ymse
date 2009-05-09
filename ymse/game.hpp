#ifndef YMSE_GAME_HPP
#define YMSE_GAME_HPP

namespace ymse {

class game {
public:
	game();
	virtual ~game();

	virtual void render() = 0;
	virtual void tick() = 0;
};

}

#endif

