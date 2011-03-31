#include <ymse/gl.h>
#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>
#include <ymse/box_reshaper.hpp>
#include <ymse/matrix2d_homogenous.hpp>
#include <ymse/vec.hpp>

// The bindable_keyboard_handler tries to make common
// keyboard use cases trivial to implement
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>

#include <ymse/key.hpp>
#include <ymse/opposite_keys.hpp>

// Luckily, boost::bind is a header only library.
#include <boost/bind.hpp>


class Game : public ymse::game {
	ymse::box_reshaper box;
	ymse::bindable_keyboard_handler kbd;

	// Use ymse::key to keep track of a key you need to know the state of
	ymse::key red;

	// Use ymse::opposite_keys to keep track of a pair of keys with opposing action
	ymse::opposite_keys right;

	double ang;

public:
	Game() :
		// Keys have to be initialized in the constructor:
		red(kbd, ymse::KEY_SPACE),
		right(kbd, ymse::KEY_LEFT, ymse::KEY_RIGHT),

		ang(0)
	{
		box.set_box(-1.5, -1.5, 1.5, 1.5);
	}

	void attach_to_core(ymse::sdl_core& core) {
		// Use bind_pressed to make an action happen when a key is pressed
		kbd.bind_pressed(ymse::KEY_F, boost::bind(&ymse::sdl_core::toggle_fullscreen, &core));

		// Call stop(0) on the core-object to quit. The argument to stop
		// is what will be returned from core.run() in main.
		kbd.bind_pressed(ymse::KEY_Q, boost::bind(&ymse::sdl_core::stop, &core, 0));

		// Use bind(...) to get both key press and release events

		core.set_game_object(this);
		core.set_reshaper_object(&box);
		core.set_keyboard_handler(&kbd);
	}

	void render() {
		using namespace ymse;
		using namespace ymse::matrix2d::homogenous;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrix33f t = box.get_transformation() * rotate(ang);

		vec3f pts[] = {
			vec3f( 0,  1, 0),
			vec3f( 1,  0, 0),
			vec3f( 0, -1, 0),
			vec3f(-1,  0, 0)
		};

		// Read key states with .val()
		if (red.val()) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 1);

		glBegin(GL_LINE_LOOP);

		for (unsigned i=0; i<sizeof(pts)/sizeof(*pts); ++i) {
			vec3f v = t * pts[i];
			glVertex2f(v[0], v[1]);
		}

		glEnd();
	}

	void tick_10ms() {
		// opposite_keys::val() will return -1, 0 or 1 depending on the states of the keys
		ang += 0.01 * right.val();
	}
};

int main(int argc, char** argv) {
	ymse::sdl_core core;
	core.init(argc, argv);

	Game game;
	game.attach_to_core(core);

	return core.run();
}
