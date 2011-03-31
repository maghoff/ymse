// Different platforms require different includes for OpenGL.
// ymse/gl.h smooths over this. It should be included early.
#include <ymse/gl.h>

#include <ymse/sdl_core.hpp>
#include <ymse/game.hpp>

// This class will be the center of attention:
class Game : public ymse::game {
public:
	void render() {
	}
};

int main(int argc, char** argv) {
	ymse::sdl_core core;
	core.init(argc, argv);

	Game game;
	core.set_game_object(&game);

	return core.run();
}
