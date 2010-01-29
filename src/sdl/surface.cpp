#include "gl.h"
#include "glu.h"
#include <SDL.h>
#include "gl/texture.hpp"
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

void surface::copy_to(gl::texture& t) const {
	SDL_PixelFormat *format = s->format;

	int bpp = format->Amask ? 4 : 3;
	int gl_format = format->Amask ? GL_RGBA : GL_RGB;

	glBindTexture(GL_TEXTURE_2D, t.get_id());
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, s->w, s->h, gl_format, GL_UNSIGNED_BYTE, s->pixels);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

}}
