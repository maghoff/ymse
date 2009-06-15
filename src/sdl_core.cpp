#include <cassert>
#include <map>
#include <stdexcept>
#include <boost/assign.hpp>
#include <SDL.h>
#include "game.hpp"
#include "keyboard_handler.hpp"
#include "keycodes.hpp"
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

	SDL_EnableKeyRepeat(0, 0); //< Just disable it.

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

std::map<int, int> key_map = boost::assign::map_list_of<int, int>
	(SDLK_UP, ymse::KEY_UP)
	(SDLK_DOWN, ymse::KEY_DOWN)
	(SDLK_LEFT, ymse::KEY_LEFT)
	(SDLK_RIGHT, ymse::KEY_RIGHT)
	(SDLK_SPACE, ymse::KEY_SPACE)
	(SDLK_q, ymse::KEY_Q)
	(SDLK_w, ymse::KEY_W)
	(SDLK_e, ymse::KEY_E)
	(SDLK_a, ymse::KEY_A)
	(SDLK_s, ymse::KEY_S)
	(SDLK_d, ymse::KEY_D)
	(SDLK_z, ymse::KEY_Z)
	(SDLK_x, ymse::KEY_X)
	(SDLK_c, ymse::KEY_C)
	(SDLK_LALT, ymse::KEY_LALT)
	(SDLK_RALT, ymse::KEY_RALT)
;

int sdl_core::run() {
	assert(inited);
	if (!inited) {
		throw std::runtime_error(
			"sdl_core::init must be run before std_core::run"
		);
	}

	assert(game_p);

	if (reshaper_p) reshaper_p->reshape(640, 480);

	SDL_Event event;
	const unsigned frame_interval = 1000/50;
	unsigned ticks = SDL_GetTicks();
	unsigned next_frame = ticks + frame_interval;
	while (running) {
		while (ticks < SDL_GetTicks()) {
			++ticks;
			if (ticks % 10 == 0) game_p->tick();
			if (ticks >= next_frame) {
				game_p->render();
				SDL_GL_SwapBuffers();
				next_frame = ticks + frame_interval;
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
			set_video_mode(event.resize.w, event.resize.h);
			if (reshaper_p) reshaper_p->reshape(event.resize.w, event.resize.h);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (keyboard_handler_p) {
				std::map<int, int>::const_iterator i = key_map.find(event.key.keysym.sym);
				if (i == key_map.end()) break;
				keyboard_handler_p->key_event(
					i->second,
					event.key.state == SDL_PRESSED
				);
			}
		}
	}
}

}
