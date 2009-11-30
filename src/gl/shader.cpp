#include <GL/gl.h>
#include <fstream>
#include "fileutil.hpp"
#include "gl/shader.hpp"

namespace ymse {
namespace gl {

shader::shader(unsigned type) {
	id = glCreateShader(type);
}

shader::~shader() {
	glDeleteShader(id);
}

void shader::source_file(const std::string& filename) {
	std::vector<char> buffer;
	ymse::read_entire_file(buffer, filename);

	const char* string[] = { buffer.data() };
	const int length[] = { buffer.size() };

	glShaderSource(id, 1, string, length);
	//check_for_gl_error();

	glCompileShader(id);
	//check_for_gl_error();
}

unsigned shader::get_id() const {
	return id;
}

}}
