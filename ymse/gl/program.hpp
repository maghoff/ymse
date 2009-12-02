#ifndef YMSE_GL_PROGRAM_HPP
#define YMSE_GL_PROGRAM_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace ymse {
namespace gl {

class shader;

class program : public boost::noncopyable {
	unsigned id;

public:
	program();
	~program();

	void attach(const shader&);

	void bind_attrib_location(unsigned index, const char* name);

	void link();

	template <typename T>
	void set_uniform(const std::string& name, T);

	unsigned get_id();
};

}}

#endif // YMSE_GL_PROGRAM_HPP
