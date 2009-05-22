#include <cassert>
#include <stdexcept>
#include <SDL.h>
#include "game.hpp"
#include "reshaper.hpp"
#include "sdl_core.hpp"

namespace ymse {

class sdl_error : public std::runtime_error {
public:
	sdl_error(const std::string& w) : std::runtime_error(w) { }
};

void check(bool ok, const std::string& f) {
	if (!ok) throw sdl_error(f + ": " + SDL_GetError());
}

#define CHECK(f) check(f, #f);

sdl_core::sdl_core() :
	inited(false),
	game_p(0),
	reshaper_p(0),
	keyboard_handler_p(0),
	running(true)
{
}

sdl_core::~sdl_core() {
	if (inited) SDL_Quit();
}

void sdl_core::set_video_mode(int w, int h) {
	screen = SDL_SetVideoMode(
		w, h, 32,
		SDL_OPENGL |
		SDL_RESIZABLE |
		0
	);
	CHECK(screen);
}

void sdl_core::init(int argc, const char *argv[]) {
	CHECK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != -1);
	inited = true;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	set_video_mode(640, 480);
}

void sdl_core::set_game_object(game* game_p_) {
	game_p = game_p_;
}

void sdl_core::set_reshaper_object(reshaper* reshaper_p_) {
	reshaper_p = reshaper_p_;
}

void sdl_core::set_keyboard_handler(keyboard_handler* keyboard_handler_p_) {
	keyboard_handler_p = keyboard_handler_p_;
}

int sdl_core::run() {
	assert(inited);
	if (!inited) {
		throw std::runtime_error(
			"sdl_core::init must be run before std_core::run"
		);
	}

	assert(game_p);

	assert(reshaper_p);
	reshaper_p->reshape(640, 480);

	SDL_Event event;
	unsigned ticks = SDL_GetTicks();
	while (running) {
		while (ticks < SDL_GetTicks()) {
			++ticks;
			if (ticks % 10 == 0) game_p->tick();
			if (ticks % (1000/50) == 0) {
				game_p->render();
				SDL_GL_SwapBuffers();
			}
		}

		int got_event = SDL_PollEvent(&event);
		if (!got_event) {
			sleep(0);
			continue;
		}

		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_VIDEORESIZE:
			assert(reshaper_p);
			set_video_mode(event.resize.w, event.resize.h);
			reshaper_p->reshape(event.resize.w, event.resize.h);
			break;
		}
	}
}

}
