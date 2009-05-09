#ifndef YMSE_GLUT_CORE_HPP
#define YMSE_GLUT_CORE_HPP

#include "core.hpp"

namespace ymse {

class glut_core : public core {
public:
	glut_core();
	~glut_core();

	void init(int argc, const char *argv[]);
	void set_game_object(game*);
	void set_reshaper_object(reshaper*);
	int run();
};

}

#endif

