#include <ymse/gl.h>
#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>
#include <ymse/box_reshaper.hpp>
#include <ymse/matrix2d_homogenous.hpp>
#include <ymse/vec.hpp>
#include <ymse/bindable_keyboard_handler.hpp>
#include <ymse/keycodes.hpp>
#include <ymse/key.hpp>
#include <ymse/opposite_keys.hpp>
#include <boost/bind.hpp>


class Game : public ymse::game {
	ymse::box_reshaper box;
	ymse::bindable_keyboard_handler kbd;

	ymse::key red;
	ymse::opposite_keys right;

	double ang;

public:
	Game() :
		red(kbd, ymse::KEY_SPACE),
		right(kbd, ymse::KEY_LEFT, ymse::KEY_RIGHT),
		ang(0)
	{
		box.set_box(-1.5, -1.5, 1.5, 1.5);
	}

	void attach_to_core(ymse::sdl_core& core) {
		kbd.bind_pressed(ymse::KEY_F, boost::bind(&ymse::sdl_core::toggle_fullscreen, &core));
		kbd.bind_pressed(ymse::KEY_Q, boost::bind(&ymse::sdl_core::stop, &core, 0));

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
