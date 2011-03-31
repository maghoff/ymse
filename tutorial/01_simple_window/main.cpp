/* This program will draw a diamond.
 *
 * It supports resizing the window, and will close normally if the
 * window is closed by clicking the close-button on the window chrome.
 *
 * The diamond will be squished to fit the window, OpenGL-style.
 * The coordinates inside the window always span from (-1, -1) to (1, 1).
 */

// Different platforms require different includes for OpenGL.
// ymse/gl.h smooths over this. It should be included early.
#include <ymse/gl.h>

#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>

// This class will be the center of attention:
class Game : public ymse::game {
public:
	void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// I know, I know. Old style OpenGL...
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 1);
		glVertex2f(1, 0);
		glVertex2f(0, -1);
		glVertex2f(-1, 0);
		glEnd();
	}
};

int main(int argc, char** argv) {
	ymse::sdl_core core;
	core.init(argc, argv);

	Game game;
	core.set_game_object(&game);

	return core.run();
}
