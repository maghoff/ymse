#include <GL/gl.h>
#include "gl/shader.hpp"
#include "gl/program.hpp"

namespace ymse {
namespace gl {

program::program() {
	id = glCreateProgram();
}

program::~program() {
	glDeleteProgram(id);
}

void program::attach(const shader& s) {
	glAttachShader(id, s.get_id());
}

void program::bind_attrib_location(unsigned index, const char* name) {
	glBindAttribLocation(id, index, name);
}

void program::link() {
	glLinkProgram(id);
}

template<>
void program::set_uniform(const std::string& name, int i) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), i);
}

unsigned program::get_id() {
	return id;
}

}}
