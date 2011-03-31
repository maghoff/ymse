#include <ymse/gl.h>
#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>
#include <ymse/box_reshaper.hpp>
#include <ymse/matrix2d_homogenous.hpp>
#include <ymse/vec.hpp>

class Game : public ymse::game {
	ymse::box_reshaper box;

	// We will rotate the diamond by this angle:
	double ang;

public:
	Game() :
		ang(0)
	{
		box.set_box(-1.5, -1.5, 1.5, 1.5);
	}

	void attach_to_core(ymse::sdl_core& core) {
		core.set_game_object(this);
		core.set_reshaper_object(&box);
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

		glBegin(GL_LINE_LOOP);

		for (unsigned i=0; i<sizeof(pts)/sizeof(*pts); ++i) {
			vec3f v = t * pts[i];
			glVertex2f(v[0], v[1]);
		}

		glEnd();
	}

	// Implement tick(int msecs), tick_ms() or tick_10ms() to do
	// things in real time.
	void tick_10ms() {
		ang += 0.01;
	}
};

int main(int argc, char** argv) {
	ymse::sdl_core core;
	core.init(argc, argv);

	Game game;
	game.attach_to_core(core);

	return core.run();
}
