#include <SDL.h>
#include "sdl/surface.hpp"

namespace ymse {
namespace sdl {

surface::surface() : s(0) { }
surface::surface(SDL_Surface* s_) : s(s_) { }
surface::surface(const surface& rhs) { operator = (rhs); }

surface::~surface() {
	// SDL_FreeSurface decrements refcount
	SDL_FreeSurface(s);
}

surface& surface::operator = (const surface& rhs) {
	s = rhs.s;
	s->refcount++;
	return *this;
}

}}
