#include <ymse/gl.h>
#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>

/* The box reshaper gives us a transformation matrix that makes sure that
 * the box we give it will always be fully present within the window.
 * So if we give it a box from (-2, -2) to (1, 5), any coordinates within
 * that box will always be on screen. box_reshaper will maintain the aspect
 * ratio, so coordinates outside the box may also be visible on screen.
 */
#include <ymse/box_reshaper.hpp>

// We will use homogenous coordinates in two dimensions. For this we need
// 3x3-matrices and 3-vectors.
#include <ymse/matrix2d_homogenous.hpp>
#include <ymse/vec.hpp>

class Game : public ymse::game {
	ymse::box_reshaper box;

public:
	Game() {
		// By default, the box_reshaper will have the box (-1, -1) to (1, 1)
		// to match OpenGL. We can set a new box like this:
		box.set_box(-1.5, -1.5, 1.5, 1.5);
	}

	void attach_to_core(ymse::sdl_core& core) {
		core.set_game_object(this);
		core.set_reshaper_object(&box);
	}

	void render() {
		using namespace ymse;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrix33f t = box.get_transformation();

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
};

int main(int argc, char** argv) {
	ymse::sdl_core core;
	core.init(argc, argv);

	Game game;
	game.attach_to_core(core);

	return core.run();
}
