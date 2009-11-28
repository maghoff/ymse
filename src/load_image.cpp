#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL_image.h>
#include <string>
//#include "load_image.hpp"

namespace ymse {

GLuint load_texture(const std::string& file) {
	SDL_Surface* surface = IMG_Load(file.c_str());
	GLuint texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SDL_PixelFormat *format = surface->format;
	if (format->Amask) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}

	SDL_FreeSurface(surface);
	return texture;
}

}
