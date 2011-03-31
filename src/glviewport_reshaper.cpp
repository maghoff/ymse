#include "gl.h"
#include "glviewport_reshaper.hpp"

namespace ymse {

glViewport_reshaper::glViewport_reshaper(reshaper* next_reshaper) :
	next(next_reshaper)
{
}

glViewport_reshaper::~glViewport_reshaper() {
}

void glViewport_reshaper::reshape(int width, int height) {
	glViewport(0, 0, width, height);
	if (next) next->reshape(width, height);
}

} // namespace ymse
