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

const int YSDL_RENDERFRAME = SDL_USEREVENT;

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

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

//	set_video_mode(1280, 720);
	set_video_mode(1920, 1080);

	SDL_ShowCursor(SDL_DISABLE);
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
	(SDLK_0, ymse::KEY_0)
	(SDLK_1, ymse::KEY_1)
	(SDLK_2, ymse::KEY_2)
	(SDLK_3, ymse::KEY_3)
	(SDLK_4, ymse::KEY_4)
	(SDLK_5, ymse::KEY_5)
	(SDLK_6, ymse::KEY_6)
	(SDLK_7, ymse::KEY_7)
	(SDLK_8, ymse::KEY_8)
	(SDLK_9, ymse::KEY_9)
	(SDLK_LALT, ymse::KEY_LALT)
	(SDLK_RALT, ymse::KEY_RALT)
;

class sdl_timer {
	SDL_TimerID id;

	static Uint32 callback_helper(Uint32 interval, void *th) {
		return reinterpret_cast<sdl_timer*>(th)->callback(interval);
	}

public:
	sdl_timer(int interval) {
		id = SDL_AddTimer(interval, &sdl_timer::callback_helper, this);
		CHECK(id);
	}
	virtual ~sdl_timer() {
		CHECK(SDL_RemoveTimer(id));
	}

	virtual Uint32 callback(Uint32 interval) = 0;
};

class sdl_frame_timer : public sdl_timer {
public:
	sdl_frame_timer(int interval) : sdl_timer(interval) { }

	Uint32 callback(Uint32 interval) {
		SDL_Event event;
		SDL_UserEvent userevent;

		userevent.type = YSDL_RENDERFRAME;
		userevent.code = 0;
		userevent.data1 = NULL;
		userevent.data2 = NULL;
		event.type = YSDL_RENDERFRAME;
		event.user = userevent;
		SDL_PushEvent(&event);

		return interval;
	}
};

int sdl_core::run() {
	assert(inited);
	if (!inited) {
		throw std::logic_error(
			"sdl_core::init must be run before std_core::run"
		);
	}

	assert(game_p);

//	if (reshaper_p) reshaper_p->reshape(1280, 720);
	if (reshaper_p) reshaper_p->reshape(1920, 1080);

	const unsigned frame_interval = 1000/50;
	sdl_frame_timer sft(frame_interval);

	SDL_Event event;
	unsigned ticks = SDL_GetTicks();
	//unsigned next_frame = ticks + frame_interval;
	while (running) {
		CHECK(SDL_WaitEvent(&event));

		while (ticks < SDL_GetTicks()) {
			++ticks;
			if (ticks % 10 == 0) game_p->tick();
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
			break;

		case YSDL_RENDERFRAME:
			game_p->render();
			SDL_GL_SwapBuffers();
			break;
		}
	}

	return 0;
}

}
