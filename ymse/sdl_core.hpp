#ifndef YMSE_SDL_CORE_HPP
#define YMSE_SDL_CORE_HPP

#include "core.hpp"

struct SDL_Surface;

namespace ymse {

class sdl_core : public core {
	bool inited;
	SDL_Surface* screen;

	game* game_p;
	reshaper* reshaper_p;
	keyboard_handler* keyboard_handler_p;

	bool running;

	void set_video_mode(int w, int h);

public:
	sdl_core();
	~sdl_core();

	void init(int argc, const char *argv[]);
	void set_game_object(game*);
	void set_reshaper_object(reshaper*);
	void set_keyboard_handler(keyboard_handler*);
	int run();
};

}

#endif
