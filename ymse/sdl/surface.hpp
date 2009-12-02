#ifndef YMSE_SDL_SURFACE_HPP
#define YMSE_SDL_SURFACE_HPP

struct SDL_Surface;

namespace ymse {
namespace sdl {

class surface {
	SDL_Surface* s;

public:
	surface();
	surface(SDL_Surface*);
	surface(const surface&);
	~surface();

	surface& operator = (const surface&);

	SDL_Surface& operator->() { return *s; }
	SDL_Surface* get() { return s; }
};

}}

#endif // YMSE_SDL_SURFACE_HPP
