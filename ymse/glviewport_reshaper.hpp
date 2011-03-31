#ifndef GLVIEWPORT_RESHAPER_HPP
#define GLVIEWPORT_RESHAPER_HPP

#include "reshaper.hpp"

namespace ymse {

class glViewport_reshaper : public reshaper {
public:
	glViewport_reshaper(reshaper* next_reshaper = 0);
	~glViewport_reshaper();

	void reshape(int width, int height);

	reshaper* next;
};

} // namespace ymse

#endif // GLVIEWPORT_RESHAPER_HPP
